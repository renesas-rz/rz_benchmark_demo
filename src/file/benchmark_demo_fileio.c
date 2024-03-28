/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<stdint.h>
#include	<unistd.h>
#include	<time.h>
#include	<ctype.h>

#include	"toml.h"

#include	"../include/benchmark_demo_gui.h"
#include	"../include/benchmark_demo_fileio.h"


/** Release allocated memory for benchmark options in the configuration file
 *
 */
static void release_opt_memory(lb_cfg_benchmark_option_t *opt)
{
	lb_cfg_benchmark_option_t *next;
	int i;
	char *str;

	while (opt) {
		next = opt->next;

		if (opt->option_text)
			free(opt->option_text);

		for (i = 0; i < MAX_NUM_VALUES; i++) {
			str = opt->values_list[i];
			if (str)
				free(str);
			else
				break;
		}
		free(opt);
		opt = next;
	}
}

/** Release allocated memory for cofiguration file
 *
 */
static void release_cfg_memory(lb_demo_configuration_t *cfg)
{
	lb_cfg_benchmark_t *benchmarks;
	lb_cfg_benchmark_t *next;

	if (cfg->log_path) {
		free(cfg->log_path);
		cfg->log_path = NULL;
	}

	benchmarks = cfg->benchmarks;
	while(benchmarks) {
		next = benchmarks->next;

		if (benchmarks->path)
			free(benchmarks->path);
		if (benchmarks->features)
			free(benchmarks->features);
		if (benchmarks->filter)
			free(benchmarks->filter);
		if (benchmarks->result)
			free(benchmarks->result);
		if (benchmarks->command)
			free(benchmarks->command);

		release_opt_memory(benchmarks->options);

		free(benchmarks);
		benchmarks = next;
	}
	cfg->benchmarks = NULL;

	return;
}

/*
 * Utilities for retrieving parameters in the configration file
 */
/** Copy a string into configuration data structure
 *
 * Note: the memory of the string retrieved by tomlc99 library shall be freed
 * after the copy.
 *
 */
static int32_t copy_str(toml_table_t *tomlconf, const char *str,
			 char *dst, size_t min, size_t max, bool required)
{
	toml_datum_t param;
	size_t length;

	param = toml_string_in(tomlconf, str);
	if (!param.ok) {
		if (required) {
			fprintf(stderr, "ERROR!! failed to read %s.\n", str);
			return 1;
		}
		else {	/* optional parameter */
			return 0;
		}
	}
	length = strlen(param.u.s);
	if((length < min) || (length > max)) {
		fprintf(stderr, "ERROR!! detected illegal length in %s.\n", str);
		free(param.u.s);
		return 1;
	}
	memcpy(dst, param.u.s, length + 1);
	free(param.u.s);

	return 0;
}

/** Set a string into configuration data structure
 *
 * Note: the memory of the string retrieved by tomlc99 library is NOT freed
 * after the setting. It shall be freed when the data structure is freed.
 *
 */
static int32_t set_str(toml_table_t *tomlconf, const char *str,
			 char **dst, size_t min, size_t max, bool required)
{
	toml_datum_t param;
	size_t length;

	param = toml_string_in(tomlconf, str);
	if (!param.ok) {
		if (required) {
			fprintf(stderr, "ERROR!! failed to read %s.\n", str);
			return 1;
		}
		else {	/* optional parameter */
			return 0;
		}
	}
	length = strlen(param.u.s);
	if((length < min) || (length > max)) {
		fprintf(stderr, "ERROR!! detected illegal length in %s.\n", str);
		free(param.u.s);
		return 1;
	}
	*dst = param.u.s;	

	return 0;
}

/** Set a boolean value into configuration data structure
 *
 */
static int32_t check_bool(toml_table_t *tomlconf, const char *str,
			 int *result, bool required)
{
	toml_datum_t param;
	size_t length;

	param = toml_bool_in(tomlconf, str);
	if (!param.ok) {
		if (required) {
			fprintf(stderr, "ERROR!! failed to read %s.\n", str);
			return 1;
		}
		else {	/* optional parameter */
			return 0;
		}
	}
	*result = param.u.b;

	return 0;
}


/*
 * Read configration file to retrieve option parameters
 */
typedef struct {
	char *name;
	lb_cfg_opt_param_t type;
} option_type_t;

/** Check and get option type
 *
 * A string for the option type is retrieved and is converted into
 * enumeration type.
 *
 */
static int32_t check_type(toml_table_t *tomlopt, lb_cfg_benchmark_option_t *cfg_opt)
{
	int32_t ret;
	int i, result;
	char param[80];
	const option_type_t types[CFG_OPT_PARAM_NUM] = {
		{CFG_STR_OPTTYPE_NONE, CFG_OPT_PARAM_NONE},
		{CFG_STR_OPTTYPE_LABEL, CFG_OPT_PARAM_LABEL},
		{CFG_STR_OPTTYPE_DROPDL, CFG_OPT_PARAM_DROPDL},
		{CFG_STR_OPTTYPE_NUMKEY, CFG_OPT_PARAM_NUMERIC},
		{CFG_STR_OPTTYPE_IPADDR, CFG_OPT_PARAM_IPADDR}
	};
	const option_type_t *tp; 
	int cmp;

	ret = copy_str(tomlopt, CFG_STR_OPT_TYPE, param, 1,
			(sizeof param) - 1, true);
	if (ret)
		return ret;

	ret = 1;
	for (i = 0, tp = &types[0]; i < CFG_OPT_PARAM_NUM; i++, tp++) {
		cmp = strcmp(param, tp->name);
		if (cmp == 0) {
			cfg_opt->type = tp->type;
			ret = 0;
			break;
		}
	}
	if (ret)
		fprintf(stderr, "ERROR!! unexpected value '%s' was detected.\n",
			param);

	return ret;
}
/** Check and get strings for option values
 *
 */
static int32_t check_values_list(toml_table_t *tomlopt, lb_cfg_benchmark_option_t *cfg_opt)
{
	toml_array_t *tomlvalues;
	int num, i;
	toml_datum_t param;
	size_t length;

	tomlvalues = toml_array_in(tomlopt, CFG_STR_OPT_VALUES_LIST);
	if (!tomlvalues) {
		/* This is a mandatory key. */
		fprintf(stderr, "ERROR!! a list of values was not detected.\n");
		return 1;
	}

	num = toml_array_nelem(tomlvalues);
	if (num > MAX_NUM_VALUES) {
		fprintf(stderr, "ERROR!! detected illegal number of values were detected.\n");
		return 1;
	}

	for (i = 0; i < num; i++) {
		param = toml_string_at(tomlvalues, i);
		if (!param.ok) {
			continue;
		}
		length = strlen(param.u.s);
		if (length > MAX_STRLEN_OPT_PARA) {
			fprintf(stderr, "ERROR!! detected illegal length "
					"at %s.\n", param.u.s);
			free(param.u.s);
			return 1;
		}
		cfg_opt->values_list[i] = param.u.s;
	}
	return 0;
}

/** Retrieve parameters for a benchmark option
 *
 */
static int32_t read_option_config(toml_table_t *tomlopt, lb_cfg_benchmark_option_t *cfg_opt)
{
	int32_t ret;
	int i;
	int result = 0;
	int cmp;

	/* Name */
	ret = copy_str(tomlopt, CFG_STR_OPT_NAME, cfg_opt->name,
			1, MAX_STRLEN_OPT_NAME, true);
	if (ret)
		return ret;
	/* Optin string */
	ret = copy_str(tomlopt, CFG_STR_OPT_OPTION_STR, cfg_opt->option_str,
			1, MAX_STRLEN_OPT_STR, false);
	if (ret)
		return ret;
	/* Use */
	ret = check_bool(tomlopt, CFG_STR_OPT_USE, &result, true);
	if (ret)
		return ret;
	cfg_opt->use = (result == 0) ? false: true;

	/* Type */
	ret = check_type(tomlopt, cfg_opt);
	if (ret)
		return ret;

	/* Option text */
	ret = set_str(tomlopt, CFG_STR_OPT_OPTION_TEXT, &cfg_opt->option_text,
			1, MAX_STRLEN_OPT_TEXT, false);
	if (ret)
		return ret;

	/* Values list */
	if (cfg_opt->type == CFG_OPT_PARAM_DROPDL) {
		ret = check_values_list(tomlopt, cfg_opt);
		if (ret)
			return ret;
	}

	/* Current value */
	if (cfg_opt->type != CFG_OPT_PARAM_NONE) {
		ret = copy_str(tomlopt, CFG_STR_OPT_CURRENT_VALUE,
				cfg_opt->current_value,
				1, MAX_STRLEN_OPT_PARA, true);
		if (ret)
			return ret;

		if (cfg_opt->type == CFG_OPT_PARAM_DROPDL) {
			/* Confirm whether the current value exists in the list */
			cmp = 1;
			for (i = 0;i < MAX_NUM_VALUES; i++) {
				if (cfg_opt->values_list[i] == NULL)
					break;
				cmp = strcmp(cfg_opt->values_list[i],
						cfg_opt->current_value);
				if (cmp == 0) {
					break;
				}
			}
			if (cmp != 0) {
				fprintf(stderr, "ERROR!! the current value"
					" does not exist in the list.\n");
				return 1;
			}
		}
	}
	return 0;
}

/*
 * Read configration file to retrieve benchmark parameters
 */
typedef struct {
	char *name;
	uint64_t flag;
} peripheral_dev_t;

/** Check and get required peripheral
 *
 * Strings for the required peripherals are retrieved and are converted into
 * flags.
 *
 */
static int32_t check_peripheral(toml_table_t *tomlbench, uint64_t *flag_data)
{
	toml_array_t *tomlperi;
	int num, i;
	toml_datum_t param;
	const peripheral_dev_t peripherals[5] = {
		{CFG_STR_PERI_SD_CARD, CFG_BENCH_PERI_SD_CARD},
		{CFG_STR_PERI_USB_FLASH, CFG_BENCH_PERI_USB_FLASH},
		{CFG_STR_PERI_EMMC, CFG_BENCH_PERI_EMMC},
		{CFG_STR_PERI_ETHERNET, CFG_BENCH_PERI_ETHERNET},
		{NULL, 0}
	};
	const peripheral_dev_t *peri;
	int cmp;

	*flag_data = 0;

	tomlperi = toml_array_in(tomlbench, CFG_STR_BENCH_PERIPHERAL);
	if (!tomlperi) {
		/* This is an optional key. */
		return 0;
	}

	num = toml_array_nelem(tomlperi);
	for (i = 0; i < num; i++) {
		param = toml_string_at(tomlperi, i);
		if (!param.ok) {
			continue;
		}
		peri = &peripherals[0];
		while (peri->name) {
			cmp = strcmp(param.u.s, peri->name);
			if (cmp == 0)
				*flag_data |= peri->flag;
			peri++;
		}
		free(param.u.s);
	}
	return 0;
}

/** Retrieve parameters for a benchmark tool
 *
 */
static int32_t read_benchmark_config(toml_table_t *tomlbench, lb_cfg_benchmark_t *cfg_bench)
{
	int32_t ret;
	int num, i;
	toml_array_t *options;
	toml_table_t *option;
	lb_cfg_benchmark_option_t *cfg_opt;
	lb_cfg_benchmark_option_t *last_option = NULL;

	/* Name */
	ret = copy_str(tomlbench, CFG_STR_BENCH_NAME, cfg_bench->name,
			1, MAX_STRLEN_BENCH_NAME, true);
	if (ret)
		return ret;
	/* Summary */
	ret = copy_str(tomlbench, CFG_STR_BENCH_SUMMARY, cfg_bench->summary,
			1, MAX_STRLEN_BENCH_SUMMARY, false);
	if (ret)
		return ret;
	/* Path: path to the benchmark tool binary */
	ret = set_str(tomlbench, CFG_STR_BENCH_PATH, &cfg_bench->path,
			1, MAX_STRLEN_BENCH_PATH, true);
	if (ret)
		return ret;
	/* Features: text that explains the benchmark features */
	ret = set_str(tomlbench, CFG_STR_BENCH_FEATURES, &cfg_bench->features,
			1, MAX_STRLEN_BENCH_FEATURES, false);
	if (ret)
		return ret;
	/* Time */
	ret = copy_str(tomlbench, CFG_STR_BENCH_TIME, cfg_bench->time,
			1, MAX_STRLEN_BENCH_TIME, false);
	if (ret)
		return ret;
	/* Peripheral */
	ret = check_peripheral(tomlbench, &cfg_bench->peripheral);
	if (ret)
		return ret;
	/* Filter */
	ret = set_str(tomlbench, CFG_STR_BENCH_FILTER, &cfg_bench->filter,
			1, MAX_STRLEN_BENCH_FILTERS, false);
	if (ret)
		return ret;

	/* Array of options */
	options = toml_array_in(tomlbench, CFG_STR_OPTIONS);
	if (!options) {
		/* This is an optional key. */
		return 0;
	}
	num = toml_array_nelem(options);
	if (num > MAX_NUM_OPTIONS) {
		fprintf(stderr, "ERROR!! detected illegal number of options were detected.\n");
		return 1;
	}
	for (i = 0; i < num; i++) {
		option = toml_table_at(options, i);
		if (!option) {
			fprintf(stderr, "ERROR!! toml_table_at() failed.\n");
			return 1;
		}
		cfg_opt = lb_allocate_memory(sizeof(lb_cfg_benchmark_option_t));
		if (cfg_opt == NULL) {
			fprintf(stderr, "ERROR!! malloc() failed.\n");
			return -1;
		}
		cfg_opt->benchmark = cfg_bench;

		if (last_option) {
			last_option->next = cfg_opt;
		}
		else {	/* top of the array */
			cfg_bench->options = cfg_opt;
		}
		last_option = cfg_opt;

		ret = read_option_config(option, cfg_opt);
		if (ret)
			return ret;
	}
	return 0;
}

/** Check version number
 *
 * @param version  version defined in the configuration file
 * @return 0 on success, -1 on failure
 */
static int32_t check_version_num(const char *version)
{
	int ret;
	char demo_ver[MAX_STRLEN_VERSION + 1];
	char *result;

	/* Check form of version number */
	ret = 0;
	if ((version[0] == 'v') || (version[0] == 'V')) {
		ret = isdigit((int)version[1]);
	}
	if (ret == 0) {
		fprintf(stderr, "ERROR!! detected illegal version number.\n");
		return -1;
	}
	snprintf(demo_ver, sizeof (demo_ver), "%d.%02d", LB_MAJOR_VERSION,
							LB_MINOR_VERSION);
	result = strstr(version, demo_ver);
	if (result == NULL) {
		fprintf(stderr, "ERROR!! version number in the configuration "
				"file is different from the demo version.\n");
		return -1;
	}
	return 0;
}

/** Read configuration file and setup data structure
 *
 * @param tomlconf
 * @param cfg
 * @return 0 on success, -1 on failure with fatal error, 1 on failure in reading
 */
static int32_t read_configuration(toml_table_t *tomlconf, lb_demo_configuration_t *cfg)
{
	int32_t ret;
	int num, i;
	toml_array_t *benchmarks;
	toml_table_t *bench;
	lb_cfg_benchmark_t *cfg_bench;
	lb_cfg_benchmark_t *last_benchmark = NULL;

	/* Version */
	ret = copy_str(tomlconf, CFG_STR_VERSION, cfg->version,
			MIN_STRLEN_VERSION, MAX_STRLEN_VERSION, true);
	if (ret)
		return ret;
	ret = check_version_num(cfg->version);
	if (ret)
		return ret;

	/* Path to a directory where log files are stored */
	ret = set_str(tomlconf, CFG_STR_LOG_PATH, &cfg->log_path,
			1, MAX_STRLEN_LOG_PATH, true);
	if (ret)
		return ret;

	/* Array of benchmarks */
	benchmarks = toml_array_in(tomlconf, CFG_STR_BENCHMARKS);
	if (!benchmarks) {
		fprintf(stderr, "ERROR!! [[%s]] was not detected.\n", CFG_STR_BENCHMARKS);
		return 1;
	}
	num = toml_array_nelem(benchmarks);
	if (num > MAX_NUM_BENCHMARKS) {
		fprintf(stderr, "ERROR!! detected illegal number of tools were detected.\n");
		return 1;
	}
	for (i = 0; i < num; i++) {
		bench = toml_table_at(benchmarks, i);
		if (!bench) {
			fprintf(stderr, "ERROR!! toml_table_at() failed.\n");
			return 1;
		}

		cfg_bench = lb_allocate_memory(sizeof(lb_cfg_benchmark_t));
		if (cfg_bench == NULL) {
			fprintf(stderr, "ERROR!! malloc() failed.\n");
			return -1;
		}

		if (last_benchmark) {
			last_benchmark->next = cfg_bench;
		}
		else {	/* top of the array */
			cfg->benchmarks = cfg_bench;
		}
		last_benchmark = cfg_bench;

		ret = read_benchmark_config(bench, cfg_bench);
		if (ret)
			return ret;
	}
	return 0;
}

/** Read configuration file
 *
 * @param gui
 * @return 0 on success, -1 on failure with fatal error, 1 on failure in reading
 */
int32_t lb_demo_fileio_read_cfgfile(lb_gui_demo_t *gui)
{
	FILE *fp;
	toml_table_t* tomlconf;
	char errbuf[200];
	int32_t ret = 0;

	if (gui->config_path == NULL)
		return 1;

	fp = fopen(gui->config_path, "r");
	if (!fp) {
		fprintf(stderr, "ERROR!! fopen() failed.\n");
		return -1;
	}
	tomlconf = toml_parse_file(fp, errbuf, sizeof(errbuf));
	if (tomlconf == NULL) {
		fprintf(stderr, "ERROR!! toml_parse_file() failed.\n"
			"\t%s\n", errbuf);
		ret = 1;
	}
	else {
		ret = read_configuration(tomlconf, &gui->config);
		toml_free(tomlconf);
	}
	fclose(fp);

	if (ret)	/* When an issue is detected, allocated memory is freed. */
		release_cfg_memory(&gui->config);

	return ret;
}

/** Release allocated memory for configuraiton file
 *
 * @param gui
 * @return none
 */
void lb_demo_fileio_release_cfg_memory(lb_gui_demo_t *gui)
{
	int32_t ret;

	if (gui == NULL)
		return;	/* Ignored */

	release_cfg_memory(&gui->config);

	return;
}

/* Save benchmark result
 *
 * Benchmark result in a temporary file is modified by sed command to add
 * an executed command for the benchmark tool, and it is output in to a log file
 * in a directory defined by the configuration file.
 *
 * @param gui
 * @param benchmark
 * @param cmd  command stirng that was executed for the bnechmark tool
 * @return none
 */
void lb_demo_fileio_save_result(lb_gui_demo_t *gui,
			lb_cfg_benchmark_t *benchmark, const char *cmd)
{
	size_t size;
	time_t t;
	struct tm *local;
	char time_str[22];	/* _dd-mm-yyyy_hh-mm.log */
	char *log;
	int ret;

	/* time stamp in log file name */
	t = time(NULL);
	local = localtime(&t);
	strftime(time_str, sizeof (time_str), "_%d-%m-%Y_%H-%M.log", local);

	/* sed command: sed '1i dmesg\n\n' "intput file" > "output file"
		lenght of sed command =
			length of sed command, space, and so on (20) +
			lenght of executed benchmark command +
			length of the path to temporary result file +
			max length of the path to directory +
			max lenght of tool manme +
			length of time string "_dd-mm-yyyy_hh-mm.log" */
	size = 20 + strlen(cmd) + strlen(benchmark->result);
	size += MAX_STRLEN_LOG_PATH + MAX_STRLEN_BENCH_NAME;
	size += sizeof (time_str);

	log = malloc(size);
	if (!log) {
		fprintf(stderr, "ERROR!! malloc() failed.\n");
		return;
	}
	snprintf(log, size, "sed '1i %s\\n\\n' %s >  %s/%s%s", cmd,
					benchmark->result,
					gui->config.log_path,
					benchmark->name, time_str);
	ret = system(log);
	if (ret == -1) {
		fprintf(stderr, "ERROR!! system() for copying benchmark result failed.\n");
	}
	free(log);
}

/** Create a temporary file for benchmark result
 *
 * @param benchmark
 * @return 0 on success, -1 on failure with fatal error
 */
int32_t lb_demo_fileio_create_tmp(lb_cfg_benchmark_t *benchmark)
{
	int ret, fd;
	char *path;

	if (benchmark->result) {
		ret = remove(benchmark->result);
		if (ret) {
			fprintf(stderr, "ERROR!! remove() %s failed.\n",
							benchmark->result);
			return -1;
		}
		free(benchmark->result);
		benchmark->result = NULL;
	}

	path = malloc(strlen(LB_BENCHMARK_TMPRESULT_PATH) + 1);
	if (ret) {
		fprintf(stderr, "ERROR!! malloc() for result file path failed.\n");
		return -1;
	}
	strcpy(path, LB_BENCHMARK_TMPRESULT_PATH);

	fd = mkstemp(path);
	if (fd == -1) {
		fprintf(stderr, "ERROR!! mkstemp() failed.\n");
		return -1;
	}
	close(fd);
	benchmark->result = path;

	return 0;
}

/** Delete a temporary file for benchmark result
 *
 * @param benchmark
 * @return 0 on success, -1 on failure with fatal error
 */
int32_t lb_demo_fileio_delete_tmp(lb_cfg_benchmark_t *benchmark)
{
	int ret;

	if (!benchmark->result)
		return 0;	/* Do nothing */

	ret = remove(benchmark->result);
	if (ret) {
		fprintf(stderr, "ERROR!! remove() %s failed.\n",
							benchmark->result);
		return -1;
	}
	free(benchmark->result);
	benchmark->result = NULL;

	return 0;
}

/*
 * Edit configuration file when demo program is terminated
 */

#define	TEMPORARY_CONFIG_FILE		"config_tmp_XXXXXX"
#define	STR_IN_CFG_BENHCHMARKS		"[[benchmarks]]"
#define	STR_IN_CFG_BENHCHMARKS_OPTIONS	"[[benchmarks.options]]"

#define	STR_IN_CFG_OPTION_USE_TRUE	"true"
#define	STR_IN_CFG_OPTION_USE_FALSE	"false"

typedef struct {
	FILE *in;
	FILE *out;

	char *linebuff;
	char *procbuff;
	size_t buff_len;
} lb_cfg_edit_t;

/** Get the number of longest line in the configuration file
 *
 */
static size_t check_max_linelength(char *configfile)
{
	size_t maxlen = 0;
	size_t len;
	FILE *fp;
	int c;

	fp = fopen(configfile, "r");
	if (!fp) {
		fprintf(stderr, "ERROR!! fopen() failed.\n");
		return 0;
	}

	len = 0;
	while (1) {
		c = fgetc(fp);
		if (c == EOF)
			break;
		len++;
		if (c == '\n') {
			if (maxlen < len)
				maxlen = len;
			len = 0;
		}
	}
	fclose(fp);

	if (maxlen < len)
		maxlen = len;
	maxlen++;

	return maxlen;
}

/** Pick up updated benchmark tools
 *
 */
static void pickup_updated_benchmarks(lb_cfg_benchmark_t *bench,
					lb_cfg_benchmark_t **updated)
{
	while (bench) {
		if (bench->updated)
			*updated++ = bench;
		bench = bench->next;
	}
	*updated = NULL;
}

/** Remove spaces and tabs at the beginning of the line, and copy
 *
 */
static void remove_whitespace(char *output, char *input)
{
	char *ptr;
	int len, i;

	*output = '\0';
	ptr = input;

	len = strlen(input);
	for (i = 0; i < len; i++) {
		if ((*ptr != ' ') && (*ptr != '\t')){
			strcpy(output, ptr);
			return;
		}
		ptr++;
	}
}

/** Replace a value of 'current value' in cfg file with a value in memory
 *
 * @param option
 * @param edit
 * @return true on success in replacement, false on failure
 */
static bool replace_option_current_value(lb_cfg_benchmark_option_t *option, lb_cfg_edit_t *edit)
{
	char value[MAX_STRLEN_OPT_PARA + 1];
	char *src;
	char *dst;
	int32_t check;

	/* Retrieve current value in configuration file */
	src = edit->procbuff;
	while (*src++ != '"');
	dst = value;
	while (*src != '"') {
		*dst++ = *src++;
	}
	*dst = '\0';

	/* Replace f with true */
	check = lb_substitute_str(edit->procbuff, edit->linebuff,
						value, option->current_value);

	return (check == 0) ? true: false;
}

/** Replace a value of 'use' in cfg file with a value in memory
 *
 * When the value of 'use' in cfg file is equal to the value in memory,
 * there is no need to update.
 *
 * @param option
 * @param edit
 * @return true on success in replacement, false on failure or cancellation
 */
static bool replace_option_use(lb_cfg_benchmark_option_t *option, lb_cfg_edit_t *edit)
{
	char *res;
	int ret = 0;
	int32_t check;
	bool replaced = false;

	if (option->use == true) {
		res = strstr(edit->procbuff, STR_IN_CFG_OPTION_USE_TRUE);
		if (res == NULL) {	/* Replace false with true */
			check = lb_substitute_str(edit->procbuff,
						edit->linebuff,
						STR_IN_CFG_OPTION_USE_FALSE,
						STR_IN_CFG_OPTION_USE_TRUE);
			if (check == 0)
				replaced = true;
		}
	}
	else {
		res = strstr(edit->procbuff, STR_IN_CFG_OPTION_USE_FALSE);
		if (res == NULL) {	/* Replace true with false */
			check = lb_substitute_str(edit->procbuff,
						edit->linebuff,
						STR_IN_CFG_OPTION_USE_TRUE,
						STR_IN_CFG_OPTION_USE_FALSE);
			if (check == 0)
				replaced = true;
		}
	}
	return replaced;
}
/** Search for option data to be updated
 *
 * When the data is found, the value in the cfg file is replaced with the value
 * in memory, and the changed line data is wrtten to output file. Otherwise
 * the line data read from input file is written to output file as is.
 *
 * @param bench
 * @param edit
 * @return 0 on success, -1 on failure
 */
static int32_t search_option_to_be_updated(lb_cfg_benchmark_option_t *option, lb_cfg_edit_t *edit)
{
	char *res;
	int ret;
	int count = 0;
	bool replaced;

	while (1) {
		/* Search array of table for benchmark options */
		while (1){
			res = fgets(edit->linebuff, edit->buff_len, edit->in);
			if (res == NULL)
				return -1;
			fputs(edit->linebuff, edit->out);
			remove_whitespace(edit->procbuff, edit->linebuff);
			ret = strncmp(edit->procbuff, STR_IN_CFG_BENHCHMARKS_OPTIONS,
					strlen(STR_IN_CFG_BENHCHMARKS_OPTIONS));
			if (ret == 0)
				break;
		}
		/* Search a key for option name */
		while (1) {
			res = fgets(edit->linebuff, edit->buff_len, edit->in);
			if (res == NULL)
				return -1;
			fputs(edit->linebuff, edit->out);
			remove_whitespace(edit->procbuff, edit->linebuff);
			ret = strncmp(edit->procbuff, CFG_STR_OPT_NAME,
					strlen(CFG_STR_OPT_NAME));
			if (ret == 0)
				break;
		}
		res = strstr(edit->procbuff, option->name);
		if (res != NULL) {	/* target option is found. */
			break;
		}
	}

	if (option->update & CFG_OPT_UPDATED_USE)
		count++;
	if (option->update & CFG_OPT_UPDATED_CURRENT_VALUE)
		count++;

	/* Search a key for option use and current value */
	while (count) {
		res = fgets(edit->linebuff, edit->buff_len, edit->in);
		if (res == NULL)
			return -1;
		remove_whitespace(edit->procbuff, edit->linebuff);

		replaced = false;
		if (option->update & CFG_OPT_UPDATED_USE) {
			ret = strncmp(edit->procbuff, CFG_STR_OPT_USE,
					strlen(CFG_STR_OPT_USE));
			if (ret == 0) {
				count--;
				replaced = replace_option_use(option, edit);
			}
		}
		if (option->update & CFG_OPT_UPDATED_CURRENT_VALUE) {
			ret = strncmp(edit->procbuff, CFG_STR_OPT_CURRENT_VALUE,
					strlen(CFG_STR_OPT_CURRENT_VALUE));
			if (ret == 0) {
				count--;
				replaced = replace_option_current_value(option, edit);
			}
		}
		if (replaced)
			fputs(edit->procbuff, edit->out);
		else
			fputs(edit->linebuff, edit->out);
	}
	return 0;
}

/** Search for benchmark data to be updated
 *
 * The line data read from input file is written to output file as is.
 *
 * @param bench
 * @param edit
 * @return 0 on success, -1 on failure
 */
static int32_t search_benchmark_to_be_updated(lb_cfg_benchmark_t *bench,
							lb_cfg_edit_t *edit)
{
	char *res;
	int ret;

	while (1) {
		/* Search array of table for benchmark */
		while (1){
			res = fgets(edit->linebuff, edit->buff_len, edit->in);
			if (res == NULL)
				return -1;
			fputs(edit->linebuff, edit->out);
			remove_whitespace(edit->procbuff, edit->linebuff);
			ret = strncmp(edit->procbuff, STR_IN_CFG_BENHCHMARKS,
					strlen(STR_IN_CFG_BENHCHMARKS));
			if (ret == 0)
				break;
		}
		/* Search a key for benchmark name */
		while (1) {
			res = fgets(edit->linebuff, edit->buff_len, edit->in);
			if (res == NULL)
				return -1;
			fputs(edit->linebuff, edit->out);
			remove_whitespace(edit->procbuff, edit->linebuff);
			ret = strncmp(edit->procbuff, CFG_STR_BENCH_NAME,
					strlen(CFG_STR_BENCH_NAME));
			if (ret == 0)
				break;
		}
		res = strstr(edit->procbuff, bench->name);
		if (res != NULL) {	/* target benchmark is found. */
			break;
		}
	}
	return 0;
}

/** Create an updated temporary configuration file
 *
 */
static int32_t create_save_cfgfile(lb_cfg_benchmark_t **updated, char *output,
						char *input, size_t maxlen)
{
	lb_cfg_benchmark_t *bench;
	lb_cfg_benchmark_option_t *option;
	lb_cfg_edit_t edit_info = {0};
	int32_t ret = 0;

	edit_info.in = fopen(input, "r");
	edit_info.out = fopen(output, "w");
	if ((!edit_info.in)  || (!edit_info.out)) {
		fprintf(stderr, "ERROR!! fopen() failed.\n");
		ret = -1;
		goto END;
	}
	edit_info.linebuff = malloc(maxlen);
	edit_info.procbuff = malloc(maxlen);
	if ((!edit_info.linebuff) || (!edit_info.procbuff)) {
		fprintf(stderr, "ERROR!! fopen() failed.\n");
		ret = -1;
		goto END;
	}
	edit_info.buff_len = maxlen;

	while (*updated != NULL) {
		bench = *updated++;

		ret = search_benchmark_to_be_updated(bench, &edit_info);
		if (ret == -1)
			goto END;

		for (option = bench->options; option != NULL; option = option->next) {
			if (!option->update) {
				continue;
			}
			ret = search_option_to_be_updated(option, &edit_info);
			if (ret == -1)
				goto END;
		}

	}
	/* Copy remaining lines */
	while (fgets(edit_info.linebuff, edit_info.buff_len, edit_info.in) != NULL) {
		fputs(edit_info.linebuff, edit_info.out);
	}
END:
	if (edit_info.linebuff)
		free(edit_info.linebuff);
	if (edit_info.procbuff)
		free(edit_info.procbuff);
	if (edit_info.in)
		fclose(edit_info.in);
	if (edit_info.out)
		fclose(edit_info.out);
	return ret;
}

/** Replace the cfg file with the temporary file by using 'mv' command
 *
 */
static int replace_config_file(char *config, char *temporary)
{
	size_t len;
	char *command;
	int ret = 0;

	len = strlen(config) + strlen(temporary);
	len += 5;	/* 'mv' command, 2 spaces, and '\0' */

	command = malloc(len);
	if (command == NULL) {
		fprintf(stderr, "ERROR!! malloc() failed.\n");
		return -1;
	}
	snprintf(command, len, "mv %s %s", temporary, config);
	ret = system(command);
	if (ret == -1) {
		fprintf(stderr, "ERROR!! system() failed.\n");
	}
	free(command);
	return ret;
}

/** Save configuration file if necessary
 *
 */
void lb_demo_fileio_save_cfgfile(lb_gui_demo_t *gui)
{
	size_t line_length;
	char file[20] = {0};	/* name of temporary configration file */
	int fd;
	lb_cfg_benchmark_t *updated_bench[MAX_NUM_BENCHMARKS + 1] = {NULL};
	int32_t ret;

	if ((!gui) || (!gui->config_path))
		return;

	line_length = check_max_linelength(gui->config_path);
	if (!line_length)
		return;
	/* The required line length may increase due to replacement. */
	line_length += MAX_STRLEN_OPT_PARA;

	strncpy(file, TEMPORARY_CONFIG_FILE, sizeof (file));
	fd = mkstemp(file);
	if (fd == -1) {
		fprintf(stderr, "ERROR!! mkstemp() failed.\n");
		return;
	}
	close(fd);

	pickup_updated_benchmarks(gui->config.benchmarks, updated_bench);
	if (updated_bench[0] != NULL) {	/* There are updated benchmark tools. */
		ret = create_save_cfgfile(updated_bench, file, gui->config_path, line_length);
		if (ret == 0) {	/* Succeeded */
			/* Copy the temporary file to configuration file */
			ret = replace_config_file(gui->config_path, file);
			if (ret == 0)	/* Succeeded */
				return;
		}
	}
	/* There is no updated benchmark tool, or edit prcess failed. */
	/* Remove the temporary file */
	ret = remove(file);
	if (ret) {
		fprintf(stderr, "ERROR!! remove() failed.\n");
	}
}

