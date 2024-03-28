/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<string.h>
#include	<stdint.h>
#include	<signal.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/wait.h>
#include	<sys/stat.h>
#include	<mntent.h>
#include	<errno.h>

#include	"../include/benchmark_demo_platform.h"
#include	"../include/benchmark_demo_fileio.h"


	/** A command used to get display informaiton */
#define		GET_DISP_INFO		"modetest -M rcar-du -p"
	/** A string to be searched */
#define		STR_SEARCHED_FOR_DISP	"driver"
	/** Maximum length of a line */
#define		LINE_LENGTH		(256)

static int stop_child_proc = 0;
static pid_t child_proc_id = 0;

/**  Wait for the child process is stopped/terminated
 *
 */
static void wait_chld_proc_stop(int sig)
{
	if (sig != SIGCHLD)
		return;
	stop_child_proc = 1;
}

/** Set up interrupt for the child process
 *
 */
static int32_t setup_interrupt(void)
{
	int ret;
	struct sigaction sa;

	ret = sigemptyset(&sa.sa_mask);
	if (ret < 0) {
		fprintf(stderr, "ERROR!! sigemptyset() failed.\n");
		return -1;
	}

	stop_child_proc = 0;
	sa.sa_handler = wait_chld_proc_stop;
	sa.sa_flags = SA_NOCLDSTOP;

	ret = sigaction(SIGCHLD, &sa, NULL);
	if (ret < 0) {
		fprintf(stderr, "ERROR!! sigaction() failed.\n");
		return -1;
	}
	return 0;
}

/** Launch a benchmark tool in etup interrupt for the child process
 *
 * A child process is created, and the process executes the benchmark tool.
 *
 */
static int32_t launch_tool(lb_benchmark_screen_t *bench_scr)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "ERROR!! fork() failed.\n");
		return -1;
	}
	else if (pid == 0) {	/* Child process for benchmark tool */
		fd = open(bench_scr->benchmark->result, O_RDWR|O_CREAT, 0666);
		if (fd < 0) {
			fprintf(stderr, "ERROR!! open() for a temporary result file failed.\n");
			exit(-1);
		}
		dup2(fd, 1);
		dup2(fd, 2);
		close(fd);

		execvp(bench_scr->benchmark->path, bench_scr->tool_argv);

		exit(0);
	}
	child_proc_id = pid;
	return 0;
}

/** Start benchmark tool
 *
 * @param bench_scr
 * @return 0 on success, -1 on failure
 */
int32_t lb_demo_platform_start_benchmark(lb_benchmark_screen_t *bench_scr)
{
	int32_t ret;

	ret = lb_demo_fileio_create_tmp(bench_scr->benchmark);
	if (ret == -1)
		return ret;

	ret = setup_interrupt();
	if (ret == -1)
		return ret;

	ret = launch_tool(bench_scr);
	if (ret == -1)
		return ret;

	return 0;
}

/** Cancel benchmark tool
 *
 * @return 0 on success, -1 on failure
 */
int32_t lb_demo_platform_cancel_benchmark(void)
{
	int32_t ret;

	ret = kill(child_proc_id, SIGKILL);
	if (ret < 0) {
		return -1;
	}
	child_proc_id = 0;
	return 0;
}

/** Check competion of benchmark tool
 *
 * @return 0 when tool has not stopped yet, 1 when tool has stopped
 */
int32_t lb_demo_platform_check_benchmark_stop(void)
{
	if (!stop_child_proc)
		return 0;	/* Not stopped yet */

	wait(NULL);
	stop_child_proc = 0;

	return 1;
}

/** Get display resolution
 *
 * @param width
 * @param height
 * @return 0 on success, -1 on failure
 */
int32_t lb_demo_platform_get_resolution(int32_t *width, int32_t *height)
{
	FILE	*fp;
	char	buffer[LINE_LENGTH];
	char	*find;
	int	w, h, num;
	int32_t	ret = -1;

	if((width == NULL) || (height == NULL)){
		fprintf(stderr, "ERROR! Null is specified @ "
				"lb_demo_platform_get_resolution\n");
		return ret;
	}

	fp = popen(GET_DISP_INFO, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! popen() failed.\n");
		return ret;
	}
	while(fgets(buffer, sizeof buffer, fp) != NULL) {
		find = strstr(buffer, STR_SEARCHED_FOR_DISP);
		if (find == NULL)
			continue;
		num = sscanf(buffer, "  #0 %dx%d ", &w, &h);
		if (num == 2) {
			ret = 0;
			*width = (int32_t)w;
			*height = (int32_t)h;
			break;
		}
	}
	pclose(fp);

	return ret;
}

/*
 * Check necessary periperals
 */
#define		DEMO_PLATFORM_BLOCK_DEV		"/sys/block/mmcblk%d/device/type"

/** Check whether the mmc block device is available
 *
 * This function checks only mmcblk0 ~ mmcblk9.
 * It would be enough on RZ/G2L EVK.
 *
 * @param dev
 * @return 0 when the device is not detected, 1 when the device is detected
 */
static int32_t lb_demo_platform_check_block(const char *dev)
{
	int i, ret;
	char path[32];
	int32_t result = 0;
	FILE *fp;
	char device_type[16];
	int cmp = 1;

	for (i = 0; i < 9; i++) {
		snprintf(path, sizeof path, DEMO_PLATFORM_BLOCK_DEV, i);
		ret = access(path, F_OK);
		if (ret != 0)
			break;
		fp = fopen(path, "r");
		if (fp == NULL) {
			fprintf(stderr, "ERROR!! fopen() for checking SD card failed.\n");
			break;
		}
		if (fgets(device_type, sizeof device_type, fp) != NULL)
			cmp = strncmp(device_type, dev, strlen(dev));
		fclose(fp);

		if (cmp == 0) {
			result = 1;
			break;
		}
	}
	return result;
}

#define		DEMO_PLATFORM_LSBLK_CMD		"lsblk -d -o NAME,TRAN"
#define		DEMO_PLATFORM_USB		"usb"
#define		DEMO_PLATFORM_USB_PART_NUM	"1"
#define		DEMO_PLATFORM_USB_MNT_POINT	"/mnt/usb_flash"
#define		DEMO_PLATFORM_MOUNTED_FS	"/etc/mtab"

/** Get device name of usb flash drive
 *
 * @param dev_name
 * @param size
 * @return 0 on success, -1 on failure
 */
static int32_t get_usb_dev_name(char *dev_name, size_t size)
{
	FILE *fp;
	char buff[80];
	char *cmp = NULL;
	char *dev;

	fp = popen(DEMO_PLATFORM_LSBLK_CMD, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! popen() failed.\n");
		return -1;
	}

	while (fgets(buff, sizeof buff, fp) != NULL) {
		cmp = strstr(buff, DEMO_PLATFORM_USB);
		if (cmp)
			break;
	}
	pclose(fp);

	if (!cmp) {	/* USB flash drive was not detected. */
		return -1;
	}

	dev = strtok(buff, " ");
	if (!dev) {
		fprintf(stderr, "ERROR!! strtok() failed.\n");
		return -1;
	}
	snprintf(dev_name, size, "/dev/%s%s", dev, DEMO_PLATFORM_USB_PART_NUM);

	return 0;
}

/** Prepare a mount point directory for usb flash drive
 *
 * @return 0 on success, -1 on failure
 */
static int32_t prep_mnt_point_dir_usb_drive(void)
{
	struct stat st;
	int ret;
	char command[80];

	ret = stat(DEMO_PLATFORM_USB_MNT_POINT, &st);
	if (ret == 0) {
		if (!S_ISDIR(st.st_mode)) {
			fprintf(stderr, "ERROR!! %s is not a directory.\n",
						DEMO_PLATFORM_USB_MNT_POINT);
			return -1;
		}
		/* A mount point directory was detected. */
	}
	else {
		if (errno != ENOENT) {
			fprintf(stderr, "ERROR!! stat() failed.\n");
			return -1;
		}
		/* Create a mount point directory. */
		snprintf(command, sizeof command, "mkdir -p %s",
						DEMO_PLATFORM_USB_MNT_POINT);
		ret = system(command);
		if (ret) {
			fprintf(stderr, "ERROR!! %s failed.\n", command);
			return -1;
		}
	}
	return 0;
}

/** Check whether USB flash drive is mounted or not
 *
 * Mount USB flash drive if necessary.
 *
 * @param dev_name
 * @return 0 on success, -1 on failure
 */
static int32_t mnt_usb_drive(char *dev_name)
{
	FILE *fp;
	struct mntent *me;
	int ret;
	bool mounted = false;
	char command[160];

	fp = setmntent(DEMO_PLATFORM_MOUNTED_FS, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! setmntent() failed.\n");
		return -1;
	}
	while ((me = getmntent(fp)) != NULL) {
		ret = strcmp(me->mnt_fsname, dev_name);
		if (ret != 0)
			continue;
		ret = strcmp(me->mnt_dir, DEMO_PLATFORM_USB_MNT_POINT);
		if (ret == 0) {
			mounted = true;
			break;
		}
	}
	endmntent(fp);

	if (mounted)	/* Already mounted */
		return 0;

	/* Mount USB flash drive */
	snprintf(command, sizeof command, "mount %s %s", dev_name,
						DEMO_PLATFORM_USB_MNT_POINT);
	ret = system(command);
	if (ret) {
		fprintf(stderr, "ERROR!! failed to mount USB flash drive.\n");
		return -1;
	}
	return 0;
}

/** Check whether USB flash driver is available
 *
 * @return 0 when the device is not detected, 1 when the device is detected
 */
static int32_t lb_demo_platform_check_usb_flash(void)
{
	int32_t ret;
	char dev_name[80];

	/* Get device name of USB flash drive */
	ret = get_usb_dev_name(dev_name, sizeof dev_name);
	if (ret)
		return 0;	/* USB flash drive was not detected. */

	/* Prepare a mount point directory */
	ret = prep_mnt_point_dir_usb_drive();
	if (ret)
		return 0;

	/* Mount USB flash drive if necessary */
	ret = mnt_usb_drive(dev_name);
	if (ret)
		return 0;

	return 1;
}

#define		DEMO_PLATFORM_ETHERNET		"ethtool eth0"
#define		DEMO_PLATFORM_ETHTOOL_CHK	"Link detected:"

/** Check whether ethernet cable is connected
 *
 * @return 0 when the device is not detected, 1 when the device is detected
 */
static int32_t lb_demo_platform_check_ethernet(void)
{
	int32_t result = 0;
	FILE *fp;
	char buff[80];
	char *cmp;

	fp = popen(DEMO_PLATFORM_ETHERNET, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! popen() for checking ethernet failed.\n");
	}
	while(fgets(buff, sizeof buff, fp) != NULL) {
		cmp = strstr(buff, DEMO_PLATFORM_ETHTOOL_CHK);
		if (cmp != NULL) {
			cmp = strstr(buff, "yes");
			result = (cmp == NULL) ? 0: 1;
			break;
		}
	}
	pclose(fp);

	return result;
}

/** Check whether necessary peripherals exist
 *
 * @param bench
 * @return 0 on success, -1 on failure
 */
int32_t lb_demo_platform_check_peripheral(lb_cfg_benchmark_t *bench)
{
	uint64_t check = 0;
	int32_t ret;

	if (!bench->peripheral)
		return 0;	/* There is no necessary peripheral. */

	if (bench->peripheral & CFG_BENCH_PERI_SD_CARD) {
		ret = lb_demo_platform_check_block("SD");
		if (ret)
			check |= CFG_BENCH_PERI_SD_CARD;
	}
	if (bench->peripheral & CFG_BENCH_PERI_USB_FLASH) {
		ret = lb_demo_platform_check_usb_flash();
		if (ret)
			check |= CFG_BENCH_PERI_USB_FLASH;
	}
	if (bench->peripheral & CFG_BENCH_PERI_EMMC) {
		ret = lb_demo_platform_check_block("MMC");
		if (ret)
			check |= CFG_BENCH_PERI_EMMC;
	}
	if (bench->peripheral & CFG_BENCH_PERI_ETHERNET) {
		ret = lb_demo_platform_check_ethernet();
		if (ret)
			check |= CFG_BENCH_PERI_ETHERNET;
	}
	return (check == bench->peripheral) ? 0: -1;
}

