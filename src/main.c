/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */


#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<fcntl.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<limits.h>
#include	<errno.h>
#include	<poll.h>
#include	<stdbool.h>
#include	<getopt.h>

#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/wayland/wayland.h"

#include	"include/benchmark_demo_gui.h"
#include        "include/benchmark_demo_platform.h"

static int32_t check_options(int argc, char *argv[], char **cfg)
{
	int option;
	int index;
	int32_t ret = 0;
	const char *optstring = "c:vh";
	const struct option longopts[] = {
		{"config", required_argument, NULL, 'c'},
		{"version", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	while (1) {
		option = getopt_long(argc, argv, optstring, longopts, &index);
		if (option == -1)
			break;
		switch(option){
		case 'c':
			if (cfg != NULL)
				*cfg = optarg;
			break;
		case 'v':
			printf("RZ Linux Benchmark Demo, "
				"Ver. %d.%02d\n" \
				"Copyright (C) 2024 Renesas Electronics Corp. "
				"All rights reserved.\n",
				LB_MAJOR_VERSION, LB_MINOR_VERSION);
			ret = 1;
			break;
		case 'h':
			printf("Usage: rz_benchmark_demo [OPTION]\n\n"
				"Options are:\n"
				"\t-c, --config\tspecify configuration file\n"
				"\t\t\tunless specified, %s is used\n"
				"\t-v, --version"
				"\toutput version information and exit\n"
				"\t-h, --help"
				"\tdisplay this help message and exit\n",
				LB_DEFAULT_CFGFILE);
			ret = 1;
			break;
		default:
			ret = -1;
			break;
		}
	}
	return ret;
}

int main(int argc, char *argv[])
{
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	int32_t width, height;
	int32_t ret;
	char *cfg_path = LB_DEFAULT_CFGFILE;
	lb_gui_shutdown_type_t shutdown_type;
	int ret_val = 0;

	ret = check_options(argc, argv, &cfg_path);
	if (ret < 0) {
		return 1;
	}
	else if (ret > 0) {
		return 0;
	}

	/*LittlevGL init*/
	lv_init();

	lv_wayland_init();

	ret = lb_demo_platform_get_resolution(&width, &height);
	if (ret < 0) {
		printf("ERROR!! lb_demo_platform_get_resolution() failed.\n");
		lv_wayland_deinit();
		return 1;
	}

	lv_disp_t * disp = lv_wayland_create_window((lv_coord_t)width,
						    (lv_coord_t)height,
						    "Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		lv_wayland_deinit();
		return 1;
	}


	lv_wayland_window_set_fullscreen(disp, true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

	ret = lb_demo_gui(width, height, disp, cfg_path);
	if (ret < 0) {
		printf("ERROR!! lb_demo_gui() failed.\n");
		lv_wayland_deinit();
		return 1;
	}

	while(1) {
		/* Handle any Wayland/LVGL timers/events */
		time_till_next = lv_wayland_timer_handler();

		/* Run until the last window closes */
		if (!lv_wayland_window_is_open(NULL)) {
			break;
		}

		/* Wait for something interesting to happen */
		if (time_till_next == LV_NO_TIMER_READY) {
			sleep = -1;
		} else if (time_till_next > INT_MAX) {
			sleep = INT_MAX;
		} else {
			sleep = time_till_next;
		}
		while ((poll(&pfd, 1, sleep) < 0) && (errno == EINTR));
	}
	shutdown_type = lb_demo_get_shutdown_type();

	lb_demo_quit();

	lv_wayland_deinit();

	if (shutdown_type == GUI_SHUTDOWN_TYPE_POWEROFF) {
		ret_val = system("shutdown -h now");
	}
	else if (shutdown_type == GUI_SHUTDOWN_TYPE_REBOOT) {
		ret_val = system("reboot");
	}
	if (ret_val == -1)
		fprintf(stderr, "ERROR!! system() failed.\n");

	return 0;
}

/**
 * Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`
 */
uint32_t custom_tick_get(void)
{
	static uint64_t start_ms = 0;
	struct timeval tv_start;
	struct timeval tv_now;
	uint64_t now_ms;

	if(start_ms == 0) {
		gettimeofday(&tv_start, NULL);
		start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
	}
	gettimeofday(&tv_now, NULL);
	now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

	return (uint32_t)(now_ms - start_ms);
}

