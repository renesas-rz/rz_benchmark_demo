/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"../include/benchmark_demo_gui.h"
#include	"../include/benchmark_demo_fileio.h"
#include	"./material/benchmark_material.h"


/** Allocate memory and fill with zero
 *
 */
void *lb_allocate_memory(size_t size)
{
	void *mem;

	mem = malloc(size);
	if (mem == NULL) {
		fprintf(stderr, "ERROR!! malloc() failed.\n");
		return NULL;
	}
	memset(mem, 0, size);

	return mem;
}

/** Replace string
 *
 * Note: this function does not check buffer size and length of string
 * @param output  otput string
 * @param input   input string that has oldstr
 * @param oldstr  character string which will be replaced
 * @param newstr  character string
 * @return 0 on success, -1 on failure
 */
int32_t lb_substitute_str(char *output, char *input, const char *oldstr,
						const char *newstr)
{
	char *find;
	char *next;

	find = strstr(input, oldstr);
	if (find == NULL)	/* oldstr was not detected. */
		return -1;

	next = &find[strlen(oldstr)];

	strcpy(output, input);
	find = strstr(output, oldstr);
	*find = '\0';

	strcat(output, newstr);
	strcat(output, next);

	return 0;
}

/** Create a label
 *
 * This is a utility function for creating a label.
 *
 */
lv_obj_t *lb_create_label(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text)
{
	lv_coord_t x, y, w, h;
	lv_obj_t *label;

	if ((gui == NULL) || (obj == NULL) || (rect == NULL))
		return NULL;

	label = lv_label_create(obj);
	if (!label)
		return NULL;

	x = (lv_coord_t)((rect->x * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((rect->y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);

	w = (lv_coord_t)((rect->w * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((rect->h * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(label, w, h);

	lv_label_set_text_static(label,
				(text) ? text: DEFAULT_EMPTY_STRING);

	return label;
}

/** Create a label by concatenating two strings
 *
 * This is a utility function for creating a label.
 *
 * @param gui
 * @param obj  parent object
 * @param rect  coordinate
 * @param text1  the first text string
 * @param text1  the second text string
 * @param space  concatenate text strings with a space or not
 *
 * @return  label object
 */
lv_obj_t *lb_create_label_with_concat(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect,
			const char *text1, const char *text2, bool space)
{
	lv_coord_t x, y, w, h;
	lv_obj_t *label;

	if ((gui == NULL) || (obj == NULL) || (rect == NULL))
		return NULL;

	label = lv_label_create(obj);
	if (!label)
		return NULL;

	x = (lv_coord_t)((rect->x * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((rect->y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);

	w = (lv_coord_t)((rect->w * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((rect->h * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(label, w, h);

	if (text1) {
		if (space)
			lv_label_set_text_fmt(label, "%s %s", text1, text2);
		else
			lv_label_set_text_fmt(label, "%s%s", text1, text2);
	}
	else {
		lv_label_set_text_static(label,
					(text2) ? text2: DEFAULT_EMPTY_STRING);
	}
	return label;
}

/** Create a label with a background object
 *
 * This is a utility function for creating a label.
 *
 */
lv_obj_t *lb_create_label_with_bg(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text,
			uint32_t bg_color)
{
	lv_coord_t x, y, w, h;
	lv_obj_t *background;
	lv_obj_t *label;

	if ((gui == NULL) || (obj == NULL) || (rect == NULL))
		return NULL;

	background = lv_obj_create(obj);
	if (!background)
		return NULL;

	x = (lv_coord_t)((rect->x * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((rect->y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(background, LV_ALIGN_TOP_LEFT, x, y);

	w = (lv_coord_t)((rect->w * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((rect->h * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(background, w, h);

	lv_obj_set_style_bg_color(background, lv_color_hex(bg_color), 0);

	label = lv_label_create(background);
	if (!label)
		return NULL;

	lv_label_set_text_static(label,
				(text) ? text: DEFAULT_EMPTY_STRING);

	return label;
}

/** Create a button
 *
 * This is a utility function for creating a button.
 *
 */
lv_obj_t *lb_create_button(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text)
{
	lv_obj_t *button;
	lv_obj_t *label;
	lv_coord_t x, y, w, h;

	if ((gui == NULL) || (obj == NULL) || (rect == NULL) || (text == NULL))
		return NULL;

	button = lv_btn_create(obj);
	if (!button)
		return NULL;

	x = (lv_coord_t)((rect->x * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((rect->y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(button, LV_ALIGN_TOP_LEFT, x, y);

	w = (lv_coord_t)((rect->w * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((rect->h * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(button, w, h);

	label = lv_label_create(button);
	if (!label)
		return NULL;
	lv_label_set_text_static(label, text);
	lv_obj_center(label);

	lv_obj_set_style_bg_color(button, lv_color_hex(BUTTON_BG_COLOR), 0);
	lv_obj_add_style(button, &gui->screen_info.button_style,
							LV_STATE_DISABLED);

	return button;
}

/** Buttons callback on modal window for shutdown
 *
 */
static void msgbox_event_cb(lv_event_t *e)
{
	lv_obj_t *msgbox;
	uint16_t index;
	lb_gui_demo_t *gui;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	msgbox = lv_event_get_current_target(e);
	index = lv_msgbox_get_active_btn(msgbox);

	lv_msgbox_close(msgbox);

	if (index == SHUTDOWN_BTN_ID_CANCEL)
		return;

	switch (index) {
	case SHUTDOWN_BTN_ID_QUIT:
		gui->shutdown_type = GUI_SHUTDOWN_TYPE_QUIT;
		break;
	case SHUTDOWN_BTN_ID_POWOFF:
		gui->shutdown_type = GUI_SHUTDOWN_TYPE_POWEROFF;
		break;
	case SHUTDOWN_BTN_ID_REBOOT:
		gui->shutdown_type = GUI_SHUTDOWN_TYPE_REBOOT;
		break;
	default:
		break;
	}
	lv_wayland_close_window(gui->disp);
}

/** Create a modal window for shutdown
 *
 */
static void create_shutdown(lb_gui_demo_t *gui)
{
	lv_obj_t *msgbox;
	lv_obj_t *label;
	lv_obj_t *btns;
	lv_coord_t w, h;
	static const char *btn_txts[SHUTDOWN_BTN_ID_NUM + 1] = {
		SHUTDOWN_DLG_BTNTXT_QUIT, SHUTDOWN_DLG_BTNTXT_POWOFF,
		SHUTDOWN_DLG_BTNTXT_REBOOT, SHUTDOWN_DLG_BTNTXT_CANCEL,
		NULL};
	const char *txt = SHUTDOWN_DLG_GUIDE_TXT;
	lv_style_selector_t selector;

	msgbox = lv_msgbox_create(NULL, NULL, txt, btn_txts, false);

	label = lv_msgbox_get_text(msgbox);
	lv_label_set_recolor(label, true);

	lv_obj_add_style(msgbox, &gui->screen_info.base_style, 0);

	w = (lv_coord_t)((SHUTDOWN_DLG_WIDTH * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((SHUTDOWN_DLG_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(msgbox, w, h);
	lv_obj_align(msgbox, LV_ALIGN_CENTER, 0, 0);

	selector = LV_PART_MAIN | LV_STATE_DEFAULT;
	lv_obj_set_style_bg_color(msgbox,
			lv_color_hex(SHUTDOWN_DLG_BG_COLOR), selector);
	lv_obj_set_style_text_color(msgbox,
			lv_color_hex(SHUTDOWN_DLG_TXT_COLOR), selector);

	btns = lv_msgbox_get_btns(msgbox);
	h = (lv_coord_t)((SHUTDOWN_DLG_BTN_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(btns, w, h);

	selector = LV_PART_ITEMS | LV_STATE_DEFAULT;
	lv_obj_set_style_bg_color(btns,
			lv_color_hex(SHUTDOWN_DLG_BTN_BG_COLOR), selector);
	lv_obj_set_style_text_color(btns,
			lv_color_hex(SHUTDOWN_DLG_BTN_TXT_COLOR), selector);

	lv_obj_add_event_cb(msgbox, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, gui);
}

/** Quit button callback
 *
 * This function is called when quit button is clicked.
 *
 */
static void quit_button_clicked_cb(lv_event_t *e)
{
	lb_gui_demo_t *gui;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);

	create_shutdown(gui);
}

/** Create a quit button
 *
 * The button is used in list screen and benchmark screen.
 *
 */
lv_obj_t *lb_create_quit_button(lb_gui_demo_t *gui, lv_obj_t *obj)
{
	lv_obj_t *button;
	const lb_rect_t quit = {
		QUIT_BUTTON_POS_X, QUIT_BUTTON_POS_Y,
		QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT};

	button = lb_create_button(gui, obj, &quit, "Quit");
	if (button)
		lv_obj_add_event_cb(button, quit_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
	return button;
}

/** Set text to status bar
 *
 * @param label  status bar label object
 * @param text  Text to be displayed. The text can be displayed with recoloring.
 * @return none
 */
void lb_set_text_to_status_bar(lv_obj_t *label, const char *text)
{
	if (label == NULL)
		return;

	if (text)
		lv_label_set_text_fmt(label, "%s%s", STATUS_BAR_DEFAULT_LABEL, text);
	else
		lv_label_set_text(label, STATUS_BAR_DEFAULT_LABEL);
}

/** Create a status bar
 *
 * The status bar is used in list screen and benchmark screen.
 *
 */
void lb_create_status_bar(lb_gui_demo_t *gui, lv_obj_t *obj, lv_obj_t **status_label)
{
	lv_obj_t *status_bar;
	lv_obj_t *label;
	lv_coord_t x, y;
	lv_coord_t w, h;

	status_bar = lv_obj_create(obj);

	x = (lv_coord_t)((STATUS_BAR_POS_X * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((STATUS_BAR_POS_Y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(status_bar, LV_ALIGN_BOTTOM_LEFT, x, y);
	w = (lv_coord_t)((STATUS_BAR_WIDTH * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((STATUS_BAR_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(status_bar, w, h);

	lv_obj_set_style_bg_color(status_bar, lv_color_hex(STATUS_BAR_BG_COLOR), 0);

	label = lv_label_create(status_bar);

	x = (lv_coord_t)((STATUS_BAR_TXT_POS_X * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((STATUS_BAR_TXT_POS_Y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);
	w = (lv_coord_t)((STATUS_BAR_TXT_WIDTH * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((STATUS_BAR_TXT_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(label, w, h);

	lv_label_set_recolor(label, true);

	lb_set_text_to_status_bar(label, NULL);
	*status_label = label;
}

/** Set default style
 *
 * The size of font is decided based on display resolution.
 *
 */
static void set_default_style(lb_gui_demo_t *gui)
{

	lv_style_t *style = &gui->screen_info.base_style;
	lb_list_screen_t *list_scr;
	lb_benchmark_screen_t *bench_scr;
	int font_size;
	struct font_table_t {
		int size;
		const lv_font_t *data;
	} font_table[] = {
		{16, &FiraCode_Regular_16},
		{20, &FiraCode_Regular_20},
		{24, &FiraCode_Regular_24},
		{28, &FiraCode_Regular_28},
		{0, NULL}
	};
	struct font_table_t *font;

	lv_style_init(style);

	font_size = ((STANDARD_FONT_SIZE * gui->width) / STANDARD_SCREEN_WIDTH + 3)/4;
	font_size *= 4;

	if (font_size >= 32) {
		lv_style_set_text_font(style, &FiraCode_Regular_32);
	}
	else {
		font = &font_table[0];
		while (font->data) {
			if (font_size <= font->size)
				break;
			font++;
		}
		lv_style_set_text_font(style, font->data);
	}
	list_scr = GET_SCREEN_DATA(lb_list_screen_t, SCREEN_ID_LIST);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	lv_obj_add_style(list_scr->screen, style, 0);
	lv_obj_add_style(bench_scr->screen, style, 0);

	/* Initialize common style for button */
	style = &gui->screen_info.button_style;
	lv_style_init(style);
	lv_style_set_bg_color(style, lv_color_hex(BUTTON_BG_DISABLED_COLOR));
}

static lb_gui_demo_t *gui_obj = NULL;	/* Linux Benchmark GUI demo base object */

/** Create demo
 *
 * Basic objects for each screen are created, and data structures are allocated.
 */
int32_t lb_demo_gui(int32_t width, int32_t height, lv_disp_t *disp, char *cfg_path)
{
	int32_t ret;

	gui_obj = lb_allocate_memory(sizeof (lb_gui_demo_t));
	if (gui_obj == NULL) {
		return -1;
	}

	gui_obj->width = (lv_coord_t)width;
	gui_obj->height = (lv_coord_t)height;
	gui_obj->disp = disp;
	gui_obj->config_path = cfg_path;

	ret = lb_create_splash_screen(gui_obj);
	if (ret)
		return ret;
	ret = lb_create_benchmark_list_screen(gui_obj);
	if (ret)
		return ret;
	ret = lb_create_benchmark_screen(gui_obj);
	if (ret)
		return ret;

	set_default_style(gui_obj);

	return 0;
}

/** Release memories for tabs
 *
 */
static void release_tab_data(void *scr_data)
{
	int i;
	lb_benchmark_screen_t *bench;

	bench = (lb_benchmark_screen_t *)scr_data;
	for (i = 0; i < BENCHMARK_TAB_ID_NUM; i++) {
		if (bench->tab_data[i])
			free(bench->tab_data[i]);
	}
}

/** Get shutdown type
 *
 * This function shall be called before GUI demo base object is released
 * by lb_demo_quit().
 */
lb_gui_shutdown_type_t lb_demo_get_shutdown_type(void)
{
	if (!gui_obj)
		return GUI_SHUTDOWN_TYPE_QUIT;
	return gui_obj->shutdown_type;
}

/** Quit demo
 *
 * All objects and data structures are released.
 */
void lb_demo_quit(void)
{
	int i;
	void *scr_data;
	lb_gui_demo_t *gui;
	lb_splash_screen_t *splash_scr;
	lb_list_screen_t *list_scr;
	lb_benchmark_screen_t *bench_scr;

	if (!gui_obj)
		return;

	gui = gui_obj;

	/* Save configuration file */
	lb_demo_fileio_save_cfgfile(gui);

	splash_scr = GET_SCREEN_DATA(lb_splash_screen_t, SCREEN_ID_SPLASH);
	list_scr = GET_SCREEN_DATA(lb_list_screen_t, SCREEN_ID_LIST);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	lv_obj_del(splash_scr->screen);
	lv_obj_del(list_scr->screen);
	lv_obj_del(bench_scr->screen);

	/* Release memory for configuration file */
	lb_demo_fileio_release_cfg_memory(gui_obj);

	/* Release memory for GUI screen */
	for (i = 0; i < SCREEN_ID_NUM; i++) {
		scr_data = gui_obj->screen_info.screen_data[i];
		if (scr_data) {
			if (i == SCREEN_ID_BENCHMARK) {
				release_tab_data(scr_data);
			}
			free(scr_data);
		}
	}
	free(gui_obj);
}

