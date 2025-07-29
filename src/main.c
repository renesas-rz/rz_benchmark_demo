/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024, 2025 Renesas Electronics Corp. All rights reserved.
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

static void show_usage(void)
{
	printf("Usage: rz_benchmark_demo [OPTION]\n\n"
		"Options are:\n"
		"\t-c, --config\tspecify configuration file\n"
		"\t\t\tUnless specified, %s is used\n"
		"\t-i, --input\tset input evdev device\n"
		"\t\t\tUnless specified, device set to EVDEV_NAME "
			"in lv_drv_conf.h is used.\n"
		"\t\t\tThis option is ineffective when rz_benchmark_demo "
			"runs on weston.\n"
		"\t-v, --version\toutput version information and exit\n"
		"\t-h, --help"
		"\tdisplay this help message and exit\n",
		LB_DEFAULT_CFGFILE);
}

static void check_options(int argc, char *argv[], char **cfg, char **input)
{
	int option;
	int index;
	const char *optstring = "c:i:vh";
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
		case 'i':
			if (input != NULL)
				*input = optarg;
			break;
		case 'v':
			printf("RZ Linux Benchmark Demo, "
				"Ver. %d.%02d\n" \
				"Copyright (C) 2024, 2025 "
				"Renesas Electronics Corp. "
				"All rights reserved.\n",
				LB_MAJOR_VERSION, LB_MINOR_VERSION);
			exit(EXIT_SUCCESS);
			break;
		case 'h':
			show_usage();
			exit(EXIT_SUCCESS);
			break;
		default:
			show_usage();
			exit(EXIT_FAILURE);
			break;
		}
	}
	return;
}

#ifndef RUNS_ON_WAYLAND	/* Runs with FBDEV and EVDEV */

/**
 * Create fbdev window with evdev
 */
static lb_disp_fbevdev_t *create_fbdev_window(char *inputdev)
{
	uint32_t width, height;
	lb_disp_fbevdev_t *dispinf;
	lv_disp_drv_t *disp_drv;
	lv_obj_t *cursor_obj;
	bool ret;

	/* Init Linux frame buffer device for LVGL */
	fbdev_init();
	fbdev_get_sizes(&width, &height, NULL);

	dispinf = lv_mem_alloc(sizeof (lb_disp_fbevdev_t));
	if (!dispinf) {
		printf("ERROR!! memory allocation failed at lv_mem_alloc()\n");
		return NULL;
	}

	dispinf->buff = lv_mem_alloc(width * height * sizeof(lv_color_t));
	if (!dispinf->buff) {
		printf("ERROR!! memory allocation failed at lv_mem_alloc()\n");
		lv_mem_free(dispinf);
		return NULL;
	}
	lv_disp_draw_buf_init(&dispinf->draw_buf, dispinf->buff, NULL,
							width * height);

	disp_drv = &dispinf->drv;
	/* Initialize and register a display driver */
	lv_disp_drv_init(disp_drv);

	disp_drv->draw_buf		= &dispinf->draw_buf;
	disp_drv->flush_cb		= fbdev_flush;
	disp_drv->hor_res		= (lv_coord_t)width;
	disp_drv->ver_res		= (lv_coord_t)height;
	disp_drv->physical_hor_res	= (lv_coord_t)width;
	disp_drv->physical_ver_res	= (lv_coord_t)height;

	dispinf->disp = lv_disp_drv_register(disp_drv);

	dispinf->width = (lv_coord_t)width;
	dispinf->height = (lv_coord_t)height;

	/* Init evdev for LVGL */
	evdev_init();

	if (inputdev) {
		ret = evdev_set_file(inputdev);
		if (!ret) {
			printf("ERROR!! the specified device file does not exist\n");
		}
	}

	lv_indev_drv_init(&dispinf->indev_drv);

	dispinf->indev_drv.type = LV_INDEV_TYPE_POINTER;
	/* This function will be called periodically (by the library)
	   to get the mouse position and state */
	dispinf->indev_drv.read_cb = evdev_read;

	dispinf->mouse_indev = lv_indev_drv_register(&dispinf->indev_drv);

	/* Set a cursor for the mouse */
	LV_IMG_DECLARE(mouse_cursor);
	/* Create an image object for the cursor */
	cursor_obj = lv_img_create(lv_scr_act());
	lv_img_set_src(cursor_obj, &mouse_cursor);
	/* Connect the image  object to the driver */
	lv_indev_set_cursor(dispinf->mouse_indev, cursor_obj);

	return dispinf;
}

static void close_fbdev_window(lb_disp_fbevdev_t *dispinf)
{
	if (!dispinf) {
		printf("ERROR!! no object to be freed.\n");
		return;
	}

	if (dispinf->mouse_indev)
		lv_indev_delete(dispinf->mouse_indev);

	if (dispinf->disp)
		lv_disp_remove(dispinf->disp);

	if (dispinf->buff)
		lv_mem_free(dispinf->buff);

	lv_mem_free(dispinf);

	fbdev_exit();
}
#endif

int main(int argc, char *argv[])
{
#ifdef RUNS_ON_WAYLAND
	struct pollfd pfd;
	uint32_t time_till_next;
	int sleep;
	lv_disp_t * disp;
#else /* FBDEV and EVDEV  */
	lb_disp_fbevdev_t *disp;
#endif
	int32_t width, height;
	int32_t ret;
	char *cfg_path = LB_DEFAULT_CFGFILE;
	lb_gui_shutdown_type_t shutdown_type = GUI_SHUTDOWN_TYPE_QUIT;
	int ret_val = 0;
	char *inputdev = NULL;

	check_options(argc, argv, &cfg_path, &inputdev);

	/* LittlevGL init */
	lv_init();

#ifdef RUNS_ON_WAYLAND
	lv_wayland_init();

	ret = lb_demo_platform_get_resolution(&width, &height);
	if (ret < 0) {
		printf("ERROR!! lb_demo_platform_get_resolution() failed.\n");
		goto APP_EXIT;
	}

	disp = lv_wayland_create_window((lv_coord_t)width, (lv_coord_t)height,
							"Window Demo", NULL);
	if (disp == NULL) {
		printf("ERROR!! lv_wayland_create_window\n");
		goto APP_EXIT;
	}

	lv_wayland_window_set_fullscreen(disp, true);

	pfd.fd = lv_wayland_get_fd();
	pfd.events = POLLIN;

#else /* FBDEV and EVDEV  */
	disp = create_fbdev_window(inputdev);
	if (disp == NULL) {
		printf("ERROR!! create_fbdev_window\n");
		goto APP_EXIT;
	}
	/* Clear end flag */
	disp->end = false;
	width = disp->width;
	height = disp->height;
#endif
	ret = lb_demo_gui(width, height, (void *)disp, cfg_path);
	if (ret < 0) {
		printf("ERROR!! lb_demo_gui() failed.\n");
		goto APP_EXIT;
	}

	while(1) {
#ifdef RUNS_ON_WAYLAND
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
#else /* FBDEV and EVDEV  */
		lv_timer_handler();
		usleep(5000);
		if (disp->end)
			break;
#endif
	}
	shutdown_type = lb_demo_get_shutdown_type();

	lb_demo_quit();
APP_EXIT:

#ifdef RUNS_ON_WAYLAND
	lv_wayland_deinit();

#else /* FBDEV and EVDEV  */
	close_fbdev_window(disp);
#endif

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

