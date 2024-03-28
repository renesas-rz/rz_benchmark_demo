/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	BENCHMARK_DEMO_FILEIO_H
#define	BENCHMARK_DEMO_FILEIO_H

#include        <stdint.h>

#include        "toml.h"
#include        "./benchmark_demo_gui.h"

/**
 * Character strings in the configuration file
 */
#define         CFG_STR_VERSION         	"version"
#define         CFG_STR_LOG_PATH        	"log_path"
/* Benchmark table */
#define		CFG_STR_BENCHMARKS		"benchmarks"
#define		CFG_STR_BENCH_NAME		"name"
#define		CFG_STR_BENCH_SUMMARY		"summary"
#define		CFG_STR_BENCH_PATH		"path"
#define		CFG_STR_BENCH_FEATURES		"features"
#define		CFG_STR_BENCH_TIME		"time"
#define		CFG_STR_BENCH_PERIPHERAL	"peripheral"
#define		CFG_STR_BENCH_FILTER		"filter"
/* Option table */
#define		CFG_STR_OPTIONS			"options"
#define		CFG_STR_OPT_NAME		"name"
#define		CFG_STR_OPT_OPTION_STR		"option_str"
#define		CFG_STR_OPT_USE			"use"
#define		CFG_STR_OPT_TYPE		"type"
#define		CFG_STR_OPT_OPTION_TEXT		"option_text"
#define		CFG_STR_OPT_VALUES_LIST		"values_list"
#define		CFG_STR_OPT_CURRENT_VALUE	"current_value"

/* Required peripheral devices for benchmark tools */
#define		CFG_STR_PERI_SD_CARD		"SD card"
#define		CFG_STR_PERI_USB_FLASH		"USB flash"
#define		CFG_STR_PERI_EMMC		"eMMC"
#define		CFG_STR_PERI_ETHERNET		"Ethernet"

/* Option type */
#define		CFG_STR_OPTTYPE_NONE		"none"
#define		CFG_STR_OPTTYPE_LABEL		"label"
#define		CFG_STR_OPTTYPE_DROPDL		"dropdown"
#define		CFG_STR_OPTTYPE_NUMKEY		"numerickey"
#define		CFG_STR_OPTTYPE_IPADDR		"ipaddress"


int32_t lb_demo_fileio_read_cfgfile(lb_gui_demo_t *gui);
void lb_demo_fileio_release_cfg_memory(lb_gui_demo_t *gui);

void lb_demo_fileio_save_result(lb_gui_demo_t *gui,
		lb_cfg_benchmark_t *benchmark, const char *cmd);
int32_t lb_demo_fileio_create_tmp(lb_cfg_benchmark_t *benchmark);
int32_t lb_demo_fileio_delete_tmp(lb_cfg_benchmark_t *benchmark);

void lb_demo_fileio_save_cfgfile(lb_gui_demo_t *gui);

#endif	/* BENCHMARK_DEMO_FILEIO_H */
