/**
 * RZ Linux Benchmark Demo, Benchmark List Screen
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"../include/benchmark_demo_gui.h"
#include	"./material/benchmark_material.h"


/** Get information about selectd benchmark tool
 *
 */
static lb_cfg_benchmark_t *get_benchmark_inf(lb_gui_demo_t *gui,  uint32_t index)
{
	lb_cfg_benchmark_t *bench;
	uint32_t count = 1;

	bench = gui->config.benchmarks;
	while (bench) {
	        if (count == index)
			break;
		count++;
		bench = bench->next;
	}
	if (!bench) {
		fprintf(stderr, "ERROR!! Benchmark information cannot be found.\n");
	}
	return bench;
}

/** List button callback
 *
 * This function is called when a button on the benchmark list is clicked.
 *
 */
static void list_button_event_cb(lv_event_t *e)
{
	lv_event_code_t code;
	lv_obj_t *btn;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	uint32_t index;

	code = lv_event_get_code(e);
	if(code == LV_EVENT_CLICKED) {
		gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
		btn = lv_event_get_target(e);

		bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
		index = lv_obj_get_child_id(btn);

		bench_scr->benchmark = get_benchmark_inf(gui, index);
		lb_setup_benchmark_cfg_tab(gui, bench_scr->benchmark);

		/* Screen transition */
		lv_scr_load(bench_scr->screen);
	}
}

/** Create a list of benchmark tools
 *
 */
static void create_list(lv_obj_t *list, lb_gui_demo_t *gui)
{
	lb_cfg_benchmark_t *benchmark;
	lv_obj_t *title_obj;
	lv_coord_t h;
	lv_obj_t *btn;
	char string[MAX_STRLEN_BENCH_NAME + MAX_STRLEN_BENCH_SUMMARY + 3];

	title_obj = lv_list_add_text(list, "Benchmark Tools");

	lv_obj_set_style_bg_color(title_obj, lv_color_hex(LIST_TITLE_BG_COLOR), 0);
	lv_obj_set_style_text_color(title_obj, lv_color_hex(LIST_COMMON_TXT_COLOR), 0);

	h = (lv_coord_t)((LIST_TITLE_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_height(title_obj, h);

	/* When an error was detected in the configuration file, 
	   the benchmark list is not created. */
	if (gui->config.configration_error)
		return;

	h = (lv_coord_t)((LIST_BUTTON_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);

	benchmark = gui->config.benchmarks;
	while (benchmark) {
		snprintf(string, sizeof string, "%s: %s",
			benchmark->name, benchmark->summary);

		btn = lv_list_add_btn(list, &list_icon, string);
		lv_obj_set_height(btn, h);

		lv_obj_set_style_bg_color(btn, lv_color_hex(LIST_COMMON_BG_COLOR), 0);
		lv_obj_set_style_text_color(btn, lv_color_hex(LIST_COMMON_TXT_COLOR), 0);

		lv_obj_add_event_cb(btn, list_button_event_cb, LV_EVENT_CLICKED, gui);

		benchmark->updated = false;	/* Initialize updated info */
		benchmark = benchmark->next;
	}
}

/** Benchmark list screen callback
 *
 * This function is called once when screen is moved from splash screen.
 * A list of benchmark tools is created based on configuration file.
 *
 */
static void create_list_cb(lv_event_t *e)
{
	lb_gui_demo_t *gui;
	lv_obj_t *target;
	lv_obj_t *list;
	lv_coord_t y, w, h;
	lb_list_screen_t *list_scr;

	target = lv_event_get_target(e);
	lv_obj_remove_event_cb(target, create_list_cb);

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);

	/* Benchmark list */
	list = lv_list_create(target);

	y = (lv_coord_t)((LIST_POS_Y * gui->height) / STANDARD_SCREEN_HEIGHT);
	w = gui->width;
	h = (lv_coord_t)((LIST_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);

	lv_obj_set_size(list, w, h);
	lv_obj_align(list, LV_ALIGN_TOP_LEFT, 0, y);

	lv_obj_set_style_bg_color(list, lv_color_hex(LIST_COMMON_BG_COLOR), 0);
	lv_obj_set_style_text_color(list, lv_color_hex(LIST_COMMON_TXT_COLOR), 0);

	w = (lv_coord_t)((LIST_SCROLLBAR_WIDTH * gui->width) / STANDARD_SCREEN_WIDTH);
	lv_obj_set_style_width(list, w, LV_PART_SCROLLBAR);

	create_list(list, gui);

	if (gui->config.configration_error) {
		/* update status bar */
		list_scr = GET_SCREEN_DATA(lb_list_screen_t, SCREEN_ID_LIST);
		lb_set_text_to_status_bar(list_scr->status_label, LIST_CONFIG_ERR_TXT);
	}
}

/** Create benchmark list screen
 *
 * Create basic parts for benchmark screen when the demo is initialized.
 *
 * @param gui
 * @return 0 on success, -1 on failure
 */
int32_t lb_create_benchmark_list_screen(lb_gui_demo_t *gui)
{
	lv_obj_t *screen;
	lv_obj_t *label;
	lv_obj_t *button;
	lv_coord_t x, y;
	lb_list_screen_t *list_scr;

	list_scr = lb_allocate_memory(sizeof (lb_list_screen_t));
	if (list_scr == NULL) {
		return -1;
	}
	gui->screen_info.screen_data[SCREEN_ID_LIST] = (void *)list_scr;

	screen = lv_obj_create(NULL);
	lv_obj_set_style_bg_color(screen, lv_color_hex(LIST_COMMON_BG_COLOR), 0);
	list_scr->screen = screen;

	lv_obj_add_event_cb(screen, create_list_cb, LV_EVENT_SCREEN_LOAD_START, gui);

	/* Operation guide */
	label = lv_label_create(screen);
	lv_label_set_text_static(label, LIST_OPERATION_GUIDE_TXT);
	lv_obj_set_style_text_color(label, lv_color_hex(GUIDE_TEXT_COLOR), 0);

	x = (lv_coord_t)((LIST_OPERATION_GUIDE_POS_X * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((LIST_OPERATION_GUIDE_POS_Y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);

	/* Quit button */
	button = lb_create_quit_button(gui, screen);

	/* Status bar */
	lb_create_status_bar(gui, screen, &list_scr->status_label);

	return 0;
}

