/**
 * RZ Linux Benchmark Demo, Splash Screen
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"../include/benchmark_demo_gui.h"
#include	"../include/benchmark_demo_fileio.h"
#include	"./material/benchmark_material.h"


#define		SPLASH_TIMER_PERIOD	((uint32_t)1000)
#define		SPLASH_TIMER_INIT_COUNT	((uint32_t)1)

/** Timer event callback for splash screen
 *
 * This timer is used for waiting completion of displaying splash screen.
 * The configuration file is read in this function, and after that, the screen
 * is changed to benchmark list screen.
 *
 */
static void timer_cb(lv_timer_t *timer)
{
	static uint32_t count = 0;
	lb_gui_demo_t *gui;
	int32_t ret;
	lb_list_screen_t *list_scr;

	if (count == SPLASH_TIMER_INIT_COUNT) {
		gui = (lb_gui_demo_t *)timer->user_data;

		lv_timer_del(timer);
		/*
		 * initialization
		 */
		ret = lb_demo_fileio_read_cfgfile(gui);
		if (ret != 0) {
			fprintf(stderr,
			"ERROR!! lb_demo_fileio_read_cfgfile() failed.\n");
			gui->config.configration_error = true;
		}
		list_scr = GET_SCREEN_DATA(lb_list_screen_t, SCREEN_ID_LIST);
		lv_scr_load(list_scr->screen);
	}
	count++;
}

/** Create splash screen
 *
 * The background is setup, a timer handler is setup, and an image object
 * for a logo is created.
 *
 */
int32_t lb_create_splash_screen(lb_gui_demo_t *gui)
{
	lv_obj_t *screen;
	lv_obj_t *logo;
	uint16_t zoom;
	lv_timer_t *timer;
	lb_splash_screen_t *splash_scr;

	splash_scr = lb_allocate_memory(sizeof (lb_splash_screen_t));
	if (splash_scr == NULL) {
		return -1;
	}
	gui->screen_info.screen_data[SCREEN_ID_SPLASH] = (void *)splash_scr;

	screen = lv_scr_act();
	lv_obj_set_style_bg_color(screen, lv_color_hex(STANDARD_BG_COLOR), 0);
	splash_scr->screen = screen;

	LV_IMG_DECLARE(renesas_logomark);
	logo = lv_img_create(screen);
	lv_img_set_src(logo, &renesas_logomark);

	lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);
	zoom = (uint16_t)(DEFAULT_MAGNIFICATION * gui->width / STANDARD_LOGO_RATIO);
	lv_img_set_zoom(logo, zoom);

	timer = lv_timer_create(timer_cb, SPLASH_TIMER_PERIOD, (void *)gui);

	return 0;
}

