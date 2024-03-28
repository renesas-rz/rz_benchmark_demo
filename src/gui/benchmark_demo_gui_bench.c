/**
 * RZ Linux Benchmark Demo,
 * 		Benchmark Configuration/Measurement Screen
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/stat.h>

#include	"../include/benchmark_demo_gui.h"
#include	"../include/benchmark_demo_fileio.h"
#include	"../include/benchmark_demo_platform.h"


#define		BENCHMARK_TIMER_PERIOD		((uint32_t)100)
#define		PERI_CHECK_TIMER_PERIOD		((uint32_t)1000)

static void setup_benchmark_result(lb_benchmark_screen_t *bench_scr, lb_cfg_benchmark_t *bench);
static void unlock_meas_tab(lb_benchmark_screen_t *bench_scr);

/** Back button callback
 *
 * This function is called when back button is clicked.
 *
 * @param e
 * @return none
 */
static void back_button_clicked_cb(lv_event_t *e)
{
	lv_event_code_t code;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	lb_list_screen_t *list_scr;

	code = lv_event_get_code(e);
	if(code == LV_EVENT_CLICKED) {
		gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
		bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t,
							SCREEN_ID_BENCHMARK);
		if (bench_scr->opt_obj)
			lv_obj_del(bench_scr->opt_obj);
		if (bench_scr->peri_timer)
			unlock_meas_tab(bench_scr);

		list_scr = GET_SCREEN_DATA(lb_list_screen_t, SCREEN_ID_LIST);
		/* Screen transition */
		lv_scr_load(list_scr->screen);
	}
}

/** Create back button
 *
 * @param gui
 * @param obj  screen object
 * @return none
 */
static void create_back_button(lb_gui_demo_t *gui, lv_obj_t *obj)
{
	lb_benchmark_screen_t *bench_scr;
	lv_obj_t *button;
	const lb_rect_t back = {
		BENCH_BACK_BUTTON_POS_X, BENCH_BACK_BUTTON_POS_Y,
		BENCH_BACK_BUTTON_WIDTH, BENCH_BACK_BUTTON_HEIGHT};

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	button = lb_create_button(gui, obj, &back, "Back");
	if (!button)
		return;
	lv_obj_add_event_cb(button, back_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
	bench_scr->back_btn = button;
}

/** Save button callback on configuration tab
 *
 * This function is called when save button on configuration tab is clicked.
 *
 * @param e
 * @return none
 */
static void cfg_save_button_clicked_cb(lv_event_t *e)
{
	lv_event_code_t code;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	lb_cfg_benchmark_t *bench;
	lb_cfg_benchmark_option_t *option;

	code = lv_event_get_code(e);
	if(code != LV_EVENT_CLICKED)
			return;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	bench = bench_scr->benchmark;
	option = bench->options;
	while (option) {
		if (option->update) {
			bench->updated = true;
			break;
		}
		option = option->next;
	}
}

/** Create save button on configuration tab
 *
 * @param gui
 * @param obj  configuration tab object
 * @return none
 */
static void create_cfg_save_button(lb_gui_demo_t *gui, lv_obj_t *obj)
{
	lv_obj_t *button;
	const lb_rect_t save = {
		BENCH_CFG_SAVE_BTN_POS_X, BENCH_CFG_SAVE_BTN_POS_Y,
		BENCH_CFG_SAVE_BTN_WIDTH, BENCH_CFG_SAVE_BTN_HEIGHT};

	button = lb_create_button(gui, obj, &save, "Save");
	if (button)
		lv_obj_add_event_cb(button, cfg_save_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
}

/** Update state of buttons on measurement tab
 *
 * When benchmark tool is not running, cancel button is disabled.
 * While benchmark tool is running, buttons except for cancel button are
 * disabled and cannot be clicked.
 *
 * @param bench_scr
 * @return none
 */
static void update_meas_buttons(lb_benchmark_screen_t *bench_scr)
{
	lb_benchtab_measure_t *measure_tab;
	lv_obj_t * tab_btns;

	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];
	tab_btns = lv_tabview_get_tab_btns(bench_scr->tabview);

	if (bench_scr->status == BENCHMARK_MEAS_STATE_STOP) {
		/* Benchmark tool has not started yet. */
		lv_obj_clear_state(bench_scr->back_btn, LV_STATE_DISABLED);
		lv_obj_clear_state(bench_scr->quit_btn, LV_STATE_DISABLED);
		lv_obj_clear_state(measure_tab->start_btn, LV_STATE_DISABLED);
		lv_obj_add_state(measure_tab->cancel_btn, LV_STATE_DISABLED);

		if (bench_scr->benchmark->result) {
			/* There is a result file. */
			lv_obj_clear_state(measure_tab->save_btn,
							LV_STATE_DISABLED);
		}
		else {
			lv_obj_add_state(measure_tab->save_btn,
							LV_STATE_DISABLED);
		}

		lv_btnmatrix_clear_btn_ctrl(tab_btns,
					(uint16_t)BENCHMARK_TAB_ID_CONFIG,
					LV_BTNMATRIX_CTRL_DISABLED);

		lb_set_text_to_status_bar(bench_scr->status_label,
						BENCH_MEAS_TOOL_STATUS_STOP);
	}
	else {
		/* Benchmark tool is running. */
		lv_obj_add_state(bench_scr->back_btn, LV_STATE_DISABLED);
		lv_obj_add_state(bench_scr->quit_btn, LV_STATE_DISABLED);
		lv_obj_add_state(measure_tab->start_btn, LV_STATE_DISABLED);
		lv_obj_clear_state(measure_tab->cancel_btn, LV_STATE_DISABLED);
		lv_obj_add_state(measure_tab->save_btn, LV_STATE_DISABLED);

		lv_btnmatrix_set_btn_ctrl(tab_btns,
					(uint16_t)BENCHMARK_TAB_ID_CONFIG,
					LV_BTNMATRIX_CTRL_DISABLED);

		lb_set_text_to_status_bar(bench_scr->status_label,
						BENCH_MEAS_TOOL_STATUS_RUN);
	}
}

/** Timer event callback for benchmark tool
 *
 * This timer event is set when a benchmark tool starts. This call back is used
 * to check whether the tool is cmpleted or not.
 *
 */
static void bench_timer_cb(lv_timer_t *timer)
{
	int32_t ret;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;

	ret = lb_demo_platform_check_benchmark_stop();
	if (!ret)
		return;
	gui = (lb_gui_demo_t *)timer->user_data;

	lv_timer_del(timer);

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	bench_scr->status = BENCHMARK_MEAS_STATE_STOP;
	update_meas_buttons(bench_scr);

	/* Display result */
	setup_benchmark_result(bench_scr, bench_scr->benchmark);
}

/** Start button callback on measurement tab
 *
 */
static void meas_start_button_clicked_cb(lv_event_t *e)
{
	lv_event_code_t code;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	lv_timer_t *timer;

	code = lv_event_get_code(e);
	if(code != LV_EVENT_CLICKED)
		return;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	bench_scr->status = BENCHMARK_MEAS_STATE_RUN;
	update_meas_buttons(bench_scr);

	/* Start a timer used for checking status of benchmark tool */
	timer = lv_timer_create(bench_timer_cb, BENCHMARK_TIMER_PERIOD, (void *)gui);
	/* Start a benchmark tool */
	lb_demo_platform_start_benchmark(bench_scr);
}

/** Cancell button callback on measurement tab
 *
 */
static void meas_cancel_button_clicked_cb(lv_event_t *e)
{
	lv_event_code_t code;

	code = lv_event_get_code(e);
	if(code != LV_EVENT_CLICKED)
		return;
	/* Cancel running benchmark tool */
	lb_demo_platform_cancel_benchmark();
}

/** Save button callback on measurement tab
 *
 */
static void meas_save_button_clicked_cb(lv_event_t *e)
{
	lv_event_code_t code;
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_measure_t *measure_tab;
	char *command;

	code = lv_event_get_code(e);
	if(code != LV_EVENT_CLICKED)
		return;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	command = lv_label_get_text(measure_tab->command_label);
	/* Save result */
	lb_demo_fileio_save_result(gui, bench_scr->benchmark, command);
}

/** Create buttons on measurement tab
 * 
 *  Start/Cancell/Save buttos on measurement tab are created in initialization.
 * 
 */
static void create_meas_buttons(lb_gui_demo_t *gui, lv_obj_t *obj)
{
	lv_obj_t *button;
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_measure_t *measure_tab;

	const lb_rect_t start = {
		BENCH_MEAS_START_BTN_POS_X, BENCH_MEAS_START_BTN_POS_Y,
		BENCH_MEAS_START_BTN_WIDTH, BENCH_MEAS_START_BTN_HEIGHT};
	const lb_rect_t cancel = {
		BENCH_MEAS_CANCEL_BTN_POS_X, BENCH_MEAS_CANCEL_BTN_POS_Y,
		BENCH_MEAS_CANCEL_BTN_WIDTH, BENCH_MEAS_CANCEL_BTN_HEIGHT};
	const lb_rect_t save = {
		BENCH_MEAS_SAVE_BTN_POS_X, BENCH_MEAS_SAVE_BTN_POS_Y,
		BENCH_MEAS_SAVE_BTN_WIDTH, BENCH_MEAS_SAVE_BTN_HEIGHT};

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	button = lb_create_button(gui, obj, &start, "Start");
	if (button)
		lv_obj_add_event_cb(button, meas_start_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
	measure_tab->start_btn  = button;

	button = lb_create_button(gui, obj, &cancel, "Cancel");
	if (button)
		lv_obj_add_event_cb(button, meas_cancel_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
	measure_tab->cancel_btn  = button;

	button = lb_create_button(gui, obj, &save, "Save");
	if (button)
		lv_obj_add_event_cb(button, meas_save_button_clicked_cb,
					LV_EVENT_CLICKED, gui);
	measure_tab->save_btn  = button;
}

/** Create text labels on configuration tab
 *
 */
static void create_cfg_description_field(lb_gui_demo_t *gui, lv_obj_t *tab)
{
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_config_t *config_tab;

	const lb_rect_t guide = {
		BENCH_OPERATION_GUIDE_POS_X, BENCH_OPERATION_GUIDE_POS_Y,
		BENCH_OPERATION_GUIDE_WIDTH, BENCH_OPERATION_GUIDE_HEIGHT };
	const lb_rect_t name_smmary = {
		BENCH_CFG_NAME_POS_X, BENCH_CFG_NAME_POS_Y,
		BENCH_CFG_NAME_WIDTH, BENCH_CFG_NAME_HEIGHT};
	const lb_rect_t features = {
		BENCH_CFG_FEATUREs_POS_X, BENCH_CFG_FEATURES_POS_Y,
		BENCH_CFG_FEATURES_WIDTH, BENCH_CFG_FEATURES_HEIGHT };
	const lb_rect_t time = {
		BENCH_CFG_TIME_POS_X, BENCH_CFG_TIME_POS_Y,
		BENCH_CFG_TIME_WIDTH, BENCH_CFG_TIME_HEIGHT};

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	config_tab = (lb_benchtab_config_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_CONFIG];

	/* Operation guide */
	config_tab->guide_label = lb_create_label(gui, tab, &guide, NULL);
	lv_label_set_text_static(config_tab->guide_label, BENCH_CFG_OPERATION_GUIDE_TXT);
	lv_obj_set_style_text_color(config_tab->guide_label, lv_color_hex(GUIDE_TEXT_COLOR), 0);
	/* Name and summary */
	config_tab->name_label = lb_create_label(gui, tab, &name_smmary, NULL);
	/* Features */
	config_tab->features_label = lb_create_label(gui, tab, &features, NULL);
	/* Time */
	config_tab->time_label = lb_create_label(gui, tab, &time, NULL);
}

/** Create text labels on measurement tab
 * 
 */
static void create_meas_result_field(lb_gui_demo_t *gui, lv_obj_t *tab)
{
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_measure_t *measure_tab;

	const lb_rect_t guide = {
		BENCH_OPERATION_GUIDE_POS_X, BENCH_OPERATION_GUIDE_POS_Y,
		BENCH_OPERATION_GUIDE_WIDTH, BENCH_OPERATION_GUIDE_HEIGHT };
	const lb_rect_t command = {
		BENCH_MEAS_CMD_POS_X, BENCH_MEAS_CMD_POS_Y,
		BENCH_MEAS_CMD_WIDTH, BENCH_MEAS_CMD_HEIGHT};
	const lb_rect_t result = {
		BENCH_MEAS_RESULT_POS_X, BENCH_MEAS_RESULT_POS_Y,
		BENCH_MEAS_RESULT_WIDTH, BENCH_MEAS_RESULT_HEIGHT};

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	/* Operation guide */
	measure_tab->guide_label = lb_create_label(gui, tab, &guide, NULL);
	lv_label_set_text_static(measure_tab->guide_label, BENCH_MEAS_OPERATION_GUIDE_TXT);
	lv_obj_set_style_text_color(measure_tab->guide_label, lv_color_hex(GUIDE_TEXT_COLOR), 0);
	/* Command */
	measure_tab->command_label = lb_create_label_with_bg(gui, tab,
						&command, NULL,
						BENCH_MEAS_CMD_BG_COLOR);
	lv_obj_set_style_text_color(measure_tab->command_label,
				lv_color_hex(BENCH_MEAS_CMD_TXT_COLOR), 0);
	/* Result */
	measure_tab->result_label = lb_create_label_with_bg(gui, tab,
						&result, NULL,
						BENCH_MEAS_RESULT_BG_COLOR);
	lv_obj_set_style_text_color(measure_tab->result_label,
				lv_color_hex(BENCH_MEAS_RESULT_TXT_COLOR), 0);
}

/** Create configuration field for benchmark options on configuration tab
 *
 */
static void create_cfg_configuration_field(lb_gui_demo_t *gui, lv_obj_t *tab)
{
	lv_obj_t *label;
	const lb_rect_t opt = {
		BENCH_CFG_OPT_HEADER_POS_X, BENCH_CFG_OPT_HEADER_POS_Y,
		BENCH_CFG_OPT_HEADER_WIDTH, BENCH_CFG_OPT_HEADER_HEIGHT};

	label = lb_create_label_with_bg(gui, tab, &opt, BENCH_CFG_OPT_HEADER,
					BENCH_CFG_OPT_HEADER_BG_COLOR);
	lv_obj_set_style_text_color(label,
				lv_color_hex(BENCH_COMMON_TXT_COLOR), 0);
}

/** Create configuration tab
 *
 * Some parts/objects on configuration tab are created in initializaiton.
 */
static void create_configuration_tab(lv_obj_t *tab, lb_gui_demo_t *gui)
{
	/* Save button */
	create_cfg_save_button(gui, tab);

	/* Operation guide and Description field */
	create_cfg_description_field(gui, tab);

	/* Configuration field */
	create_cfg_configuration_field(gui, tab);
}

/** Create measurement tab
 *
 * Some parts/objects on meausrement tab are created in initializaiton.
 */
static void create_measurement_tab(lv_obj_t *tab, lb_gui_demo_t *gui)
{
	/* Start , Cancel, and Save buttons */
	create_meas_buttons(gui, tab);

	/* Operation guide and Result field */
	create_meas_result_field(gui, tab);
}

/*
 * Set up configuration tab
 */
/** Use switch callback
 *
 * This function is called when use switch is changed.
 *
 */
static void switch_event_cb(lv_event_t *e)
{
	lb_cfg_benchmark_option_t *option;
	lv_event_code_t code;
	lv_obj_t *sw;

	code = lv_event_get_code(e);
	if (code != LV_EVENT_VALUE_CHANGED)
		return;

	option = (lb_cfg_benchmark_option_t *)lv_event_get_user_data(e);
	sw = lv_event_get_target(e);
	/* Save the status of use */
	option->use = lv_obj_has_state(sw, LV_STATE_CHECKED);
	option->update |= CFG_OPT_UPDATED_USE;

	/* Delete a temporary result file when the option is changed. */
	lb_demo_fileio_delete_tmp((lb_cfg_benchmark_t *)option->benchmark);
}

/** Set up a name label and an use switch for an option
 *
 */
static lv_coord_t setup_option_name_sw(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lv_obj_t *sw;
	lb_rect_t rect;
	lv_coord_t ofs_y = 0;

	/* Option name */
	rect.x = x + BENCH_CFG_OPT_NAME_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_NAME_HEIGHT;
	label = lb_create_label(gui, base, &rect, option->name);
	ofs_y += rect.h;

	/* Use switch */
	rect.x = x + BENCH_CFG_OPT_USE_OFS_X;
	rect.y = y + ofs_y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_USE_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_USE_TEXT);
	ofs_y += rect.h;

	sw = lv_switch_create(base);
	rect.x = (lv_coord_t)(((x + BENCH_CFG_OPT_USESW_OFS_X) * gui->width)
						/ STANDARD_SCREEN_WIDTH);
	rect.y = (lv_coord_t)((rect.y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(sw, LV_ALIGN_TOP_LEFT, rect.x, rect.y);
	lv_obj_add_event_cb(sw, switch_event_cb, LV_EVENT_ALL, option);
	if (option->use) {
		lv_obj_add_state(sw, LV_STATE_CHECKED);
	}
	else {
		lv_obj_clear_state(sw, LV_STATE_CHECKED);
	}
	return ofs_y;
}

/** Set up a text and a separator labels for an option
 *
 */
static lv_coord_t setup_option_text_sep(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lb_rect_t rect;
	lv_coord_t ofs_y = 0;
	lv_coord_t line_num;

	/* Option text */
	if (option->option_text) {
		line_num = (lv_coord_t)strlen(option->option_text);
		line_num += BENCH_CFG_OPT_TEXT_CHAR_LINE - 1;
		line_num /= BENCH_CFG_OPT_TEXT_CHAR_LINE;

		rect.x = x + BENCH_CFG_OPT_TEXT_OFS_X;
		rect.y = y + ofs_y;
		rect.w = BENCH_CFG_OPT_WIDTH - BENCH_CFG_OPT_TEXT_OFS_X -
						BENCH_CFG_OPT_MARGIN_WIDTH;
		rect.h = BENCH_CFG_OPT_TEXT_HEIGHT * line_num;
		label = lb_create_label(gui, base, &rect, option->option_text);
		ofs_y += rect.h;
	}
	/* Separator */
	rect.x = x + BENCH_CFG_OPT_SEP_OFS_X;
	rect.y = y + ofs_y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_SEP_HEIGHT;

	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_SEP_TEXT);
	ofs_y += rect.h;

	return ofs_y;
}

/** Set up a title and a current value labels for an option that has no argument
 *
 */
static lv_coord_t setup_option_param_none(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lb_rect_t rect;

	/* Title */
	rect.x = x + BENCH_CFG_OPT_PAR_VAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_VAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_PAR_VAL_TEXT);

	/* Current value */
	rect.x = x + BENCH_CFG_OPT_PAR_CRVAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_CRVAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, option->option_str);

	return rect.h;
}

/** Set up a title and a static current value labels
 *
 */
static lv_coord_t setup_option_param_label(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lb_rect_t rect;
	size_t len;
	bool space;

	/* Title */
	rect.x = x + BENCH_CFG_OPT_PAR_VAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_VAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_PAR_VAL_TEXT);

	/* When the option string ends without '=', insert a space. */
	len = strlen(option->option_str);
	space = (option->option_str[len - 1] != '=') ? true: false;

	/* Current value */
	rect.x = x + BENCH_CFG_OPT_PAR_CRVAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_CRVAL_HEIGHT;
	label = lb_create_label_with_concat(gui, base, &rect,
						option->option_str,
						option->current_value,
						space);

	return rect.h;
}

/** Dropdown list callback
 *
 * This function is called when dropdown list is changed.
 *
 */
static void dropdownlist_event_cb(lv_event_t *e)
{
	lb_cfg_benchmark_option_t *option;
	lv_event_code_t code;
	lv_obj_t *droplist;
	size_t length;
	char dropdown_list_item[MAX_STRLEN_OPT_PARA + 2];

	code = lv_event_get_code(e);
	if (code != LV_EVENT_VALUE_CHANGED)
		return;

	option = (lb_cfg_benchmark_option_t *)lv_event_get_user_data(e);

	droplist = lv_event_get_target(e);
	lv_dropdown_get_selected_str(droplist, dropdown_list_item, sizeof (dropdown_list_item));
	/* Parameter check */
	length = strlen(dropdown_list_item);
	if ((length < 1) || (length > MAX_STRLEN_OPT_PARA)) {
		/* Basically, this error cannot occur since the length is
		   checked when the configuration file is read. */
		fprintf(stderr, "ERROR!! detected illegal length at %s.\n",
								option->name);
		return;
	}
	/* Save the current value */
	memcpy(option->current_value, dropdown_list_item, length + 1);
	option->update |= CFG_OPT_UPDATED_CURRENT_VALUE;

	/* Delete a temporary result file when the option is changed. */
	lb_demo_fileio_delete_tmp((lb_cfg_benchmark_t *)option->benchmark);
}

/** Set up a title label and a changeable value dropdown list
 *
 * The value can be changed and be selected from the dropdown list.
 *
 */
static lv_coord_t setup_option_param_dropdl(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lv_obj_t *droplist;
	lb_rect_t rect;
	lv_coord_t pos_x, pos_y, w, h;
	size_t len;
	lv_coord_t ofs_y = 0;
	uint32_t i, current;
	char *values;
	char dropdown_list_item[MAX_STRLEN_OPT_PARA + 2];
	size_t length;

	/* Title */
	rect.x = x + BENCH_CFG_OPT_PAR_VAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_VAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_PAR_VAL_TEXT);

	/* x,y coordinates for the next parameter */
	rect.x = x + BENCH_CFG_OPT_PAR_CRVAL_OFS_X;
	rect.y = y;
	/* Current value */
	if (option->option_str[0] != '\0') {
		len = (lv_coord_t)strlen(option->option_str);

		rect.w = len * STANDARD_FONT_SIZE;
		rect.h = BENCH_CFG_OPT_PAR_CRVAL_HEIGHT;
		label = lb_create_label(gui, base, &rect, option->option_str);
		/* x coordinate for the next parameter */
		rect.x += rect.w;
		/* When the option string ends without '=', insert a space. */
		if (option->option_str[len - 1] != '=')
			rect.x += STANDARD_FONT_SIZE;
	}
	/* Drop-down list */
	droplist = lv_dropdown_create(base);
	lv_dropdown_clear_options(droplist);
	/* Remove symbol icon */
	lv_dropdown_set_symbol(droplist, NULL);

	for (i = 0, current = 0, len = 0; ; i++) {
		values = option->values_list[i];
		if (!values)
			break;

		strncpy(dropdown_list_item, values, MAX_STRLEN_OPT_PARA);
		length = strlen(dropdown_list_item);
		dropdown_list_item[length + 1] = '\n';
		dropdown_list_item[length + 2] = '\0';
		lv_dropdown_add_option(droplist, dropdown_list_item, i);

		if (len < length)
			len = length;	/* Get max length */

		if (strcmp(values, option->current_value) == 0)
			current = i;
	}
	lv_dropdown_set_selected(droplist, (uint16_t)current);

	pos_x = (lv_coord_t)((rect.x * gui->width) / STANDARD_SCREEN_WIDTH);
	pos_y = (lv_coord_t)(((y + BENCH_CFG_OPT_PAR_DRPDWN_OFS_Y) * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(droplist, LV_ALIGN_TOP_LEFT, pos_x, pos_y);

	w = (lv_coord_t)((((len + 4) * STANDARD_FONT_SIZE / 2) * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((STANDARD_FONT_SIZE * 2 * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(droplist, w, h);

	lv_obj_add_event_cb(droplist, dropdownlist_event_cb, LV_EVENT_ALL, option);
	ofs_y += BENCH_CFG_OPT_PAR_DRPDWN_HEIGHT;

	return ofs_y;
}

/** Button matrix callback
 *
 * This function is called when a value of a button is changed.
 * When 'return' button is pressed, send a 'ready' event to the textarea.
 *
 */
static void btnmtx_event_cb(lv_event_t *e)
{
	lv_obj_t *txtarea;
	lv_obj_t *btns;
	const char *btn_txt;

	btns = lv_event_get_target(e);
	btn_txt = lv_btnmatrix_get_btn_text(btns,
					lv_btnmatrix_get_selected_btn(btns));
	txtarea = (lv_obj_t *)lv_event_get_user_data(e);

	if (strcmp(btn_txt, BENCH_CFG_OPT_PAR_BACKSP_TEXT) == 0) {
		lv_textarea_del_char(txtarea);
	}
	else if (strcmp(btn_txt, BENCH_CFG_OPT_PAR_ENTER_TEXT) == 0) {
		lv_event_send(txtarea, LV_EVENT_READY, NULL);
	}
	else {	/* Numeric buttons*/
		lv_textarea_add_text(txtarea, btn_txt);
	}
}

/** Textarea callback
 *
 * This function is called when the textarea is ready.
 *
 */
static void textarea_event_ready_cb(lv_event_t *e)
{
	lb_cfg_benchmark_option_t *option;
	const char *param;
	lv_obj_t *txtarea;
	size_t length;

	option = (lb_cfg_benchmark_option_t *)lv_event_get_user_data(e);

	txtarea = lv_event_get_target(e);
	/* Get text */
	param = lv_textarea_get_text(txtarea);
	/* Parameter check */
	length = strlen(param);
	if ((length < 1) || (length > MAX_STRLEN_OPT_PARA)) {
		/* Basically, the length cannot exceed the maximum length
		   since it is limited by LVGL API. */
		fprintf(stderr, "ERROR!! detected illegal length at %s.\n",
								option->name);
		return;
	}
	/* Save the current value */
	memcpy(option->current_value, param, length + 1);
	option->update |= CFG_OPT_UPDATED_CURRENT_VALUE;

	/* Delete a temporary result file when the option is changed. */
	lb_demo_fileio_delete_tmp((lb_cfg_benchmark_t *)option->benchmark);
}

/** Set up a title label and a numeric key button matirx
 *
 * The value can be selected by the numeric key.
 *
 */
static lv_coord_t setup_option_param_numeric(lb_gui_demo_t *gui,
					lb_cfg_benchmark_option_t *option,
					lv_obj_t *base,
					lv_coord_t x, lv_coord_t y)
{
	lv_obj_t *label;
	lv_obj_t *txtarea;
	lv_obj_t *btnmtx;
	lb_rect_t rect;
	lv_coord_t pos_x, pos_y, w, h;
	lv_coord_t ofs_y = 0;
	static const char * btn_mtx_map[] = {
		"7", "8", "9", BENCH_CFG_OPT_PAR_BACKSP_TEXT, "\n",
		"4", "5", "6", " ", "\n",
		"1", "2", "3", " ", "\n",
		"0", ".", BENCH_CFG_OPT_PAR_ENTER_TEXT, ""
	};
	lv_btnmatrix_ctrl_t ctrl;

	/* Title */
	rect.x = x + BENCH_CFG_OPT_PAR_VAL_OFS_X;
	rect.y = y;
	rect.w = BENCH_CFG_OPT_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_VAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_PAR_VAL_TEXT);

	/* Current value */
	w = (lv_coord_t)strlen(option->option_str);
	w *= STANDARD_FONT_SIZE;
	rect.x = x + BENCH_CFG_OPT_PAR_CRVAL_OFS_X;
	rect.y = y;
	rect.w = (w > BENCH_CFG_OPT_WIDTH) ? BENCH_CFG_OPT_WIDTH: w;
	rect.h = BENCH_CFG_OPT_PAR_CRVAL_HEIGHT;
	label = lb_create_label(gui, base, &rect, option->option_str);

	/* Text area for Numerickey */
	txtarea = lv_textarea_create(base);
	lv_textarea_set_one_line(txtarea, true);
	lv_textarea_set_text(txtarea, option->current_value);
	lv_obj_add_state(txtarea, LV_STATE_FOCUSED);
	lv_textarea_set_max_length(txtarea, MAX_STRLEN_OPT_PARA);

	pos_x = (lv_coord_t)(((rect.x + rect.w) * gui->width) / STANDARD_SCREEN_WIDTH);
	pos_y = (lv_coord_t)(((y + BENCH_CFG_OPT_PAR_NUMTXT_OFS_Y) * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(txtarea, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
	lv_obj_add_event_cb(txtarea, textarea_event_ready_cb, LV_EVENT_READY, option);
	ofs_y += BENCH_CFG_OPT_PAR_NUMTXT_HEIGHT + BENCH_CFG_OPT_PAR_NUMTXT_OFS_Y;

	/* Button matrix for Numerickey */
	btnmtx = lv_btnmatrix_create(base);
	w = (lv_coord_t)((BENCH_CFG_OPT_PAR_NUM_WIDTH * gui->width)
						/ STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((BENCH_CFG_OPT_PAR_NUM_HEIGHT * gui->height)
						/ STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(btnmtx, w, h);
	pos_y = (lv_coord_t)(((y + ofs_y) * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(btnmtx, LV_ALIGN_TOP_LEFT, pos_x, pos_y);
	lv_obj_add_event_cb(btnmtx, btnmtx_event_cb, LV_EVENT_VALUE_CHANGED, txtarea);
	lv_obj_clear_flag(btnmtx, LV_OBJ_FLAG_CLICK_FOCUSABLE);
	lv_btnmatrix_set_map(btnmtx, btn_mtx_map);
	/* disable unused buttons */
	ctrl = LV_BTNMATRIX_CTRL_HIDDEN | LV_BTNMATRIX_CTRL_DISABLED;
	lv_btnmatrix_set_btn_ctrl(btnmtx, (uint16_t)7, ctrl);
	lv_btnmatrix_set_btn_ctrl(btnmtx, (uint16_t)11, ctrl);
	/* set the width of button 'Enter' to double */
	ctrl = 2;
	lv_btnmatrix_set_btn_ctrl(btnmtx, (uint16_t)14, ctrl);
	ofs_y += BENCH_CFG_OPT_PAR_NUM_HEIGHT;

	/* Guide */
	rect.x = x + BENCH_CFG_OPT_PAR_GUIDE_OFS_X;
	rect.y = y + BENCH_CFG_OPT_PAR_NUMTXT_HEIGHT +
		BENCH_CFG_OPT_PAR_NUMTXT_OFS_Y + BENCH_CFG_OPT_PAR_GUIDE_OFS_Y;
	rect.w = BENCH_CFG_OPT_PAR_GUIDE_WIDTH;
	rect.h = BENCH_CFG_OPT_PAR_GUIDE_HEIGHT;
	label = lb_create_label(gui, base, &rect, BENCH_CFG_OPT_PAR_GUIDE_TEXT);

	return ofs_y;
}

/** Set up an object for options
 *
 */
static lv_obj_t *setup_option_base(lb_gui_demo_t *gui, lv_obj_t *tab)
{
	lv_obj_t *obj;
	lv_coord_t x, y, w, h;

	obj = lv_obj_create(tab);
	x = (lv_coord_t)((BENCH_CFG_OPT_START_X * gui->width) / STANDARD_SCREEN_WIDTH);
	y = (lv_coord_t)((BENCH_CFG_OPT_START_Y * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_align(obj, LV_ALIGN_TOP_LEFT, x, y);
	w = (lv_coord_t)((BENCH_CFG_OPT_WIDTH * gui->width) / STANDARD_SCREEN_WIDTH);
	h = (lv_coord_t)((BENCH_CFG_OPT_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(obj, w, h);

	lv_obj_set_style_bg_color(obj, lv_color_hex(BENCH_CFG_OPT_BG_COLOR), 0);
	lv_obj_set_style_text_color(obj, lv_color_hex(BENCH_CFG_OPT_TXT_COLOR), 0);

	return obj;
}

typedef lv_coord_t (*setup_opt_func_t)(lb_gui_demo_t *, \
		lb_cfg_benchmark_option_t *, lv_obj_t *, \
		lv_coord_t, lv_coord_t);

/** Set up configuration of options
 *
 */
static void setup_configurations(lb_gui_demo_t *gui, lb_cfg_benchmark_t *bench,
					lv_obj_t *tab)
{
	lb_benchmark_screen_t *bench_scr;
	lb_cfg_benchmark_option_t *option;
	lv_coord_t x, y;
	static const setup_opt_func_t set_opt_funcs[CFG_OPT_PARAM_NUM + 1] = {
		&setup_option_param_none,
		&setup_option_param_label,
		&setup_option_param_dropdl,
		&setup_option_param_numeric,
		&setup_option_param_numeric,
		NULL
	};

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	bench_scr->opt_obj = setup_option_base(gui, tab);

	option = bench->options;
	if (!option)
		return;		/* No option */

	x = 0;
	y = 0;
	while (option) {
		/* Set up option name and use switch */
		y += setup_option_name_sw(gui, option, bench_scr->opt_obj, x, y);

		if (option->type < CFG_OPT_PARAM_NUM)
			y += set_opt_funcs[option->type](gui, option,
						bench_scr->opt_obj, x, y);

		y += setup_option_text_sep(gui, option, bench_scr->opt_obj, x, y);
		option = option->next;
	}
}

/** Unlock measurement tab
 *
 * When required peripherals are mounted or when the screen is moved to
 * benchmark list screen, lock of measurement tab is released.
 *
 */
static void unlock_meas_tab(lb_benchmark_screen_t *bench_scr)
{
	lv_obj_t * tab_btns;

	lv_timer_del(bench_scr->peri_timer);
	bench_scr->peri_timer = NULL;

	tab_btns = lv_tabview_get_tab_btns(bench_scr->tabview);
	lv_btnmatrix_clear_btn_ctrl(tab_btns,
					(uint16_t)BENCHMARK_TAB_ID_MEASURE,
						LV_BTNMATRIX_CTRL_DISABLED);
}

/** Timer event callback for checking peripherals
 *
 */
static void peripheral_timer_cb(lv_timer_t *timer)
{
	lb_benchmark_screen_t *bench_scr;
	int32_t check;

	bench_scr = (lb_benchmark_screen_t *)timer->user_data;
	/* Check necessary device */
	check = lb_demo_platform_check_peripheral(bench_scr->benchmark);
	if (check)
		return;	/* Not available yet */

	unlock_meas_tab(bench_scr);
	/* Clear error info on status bar */
	lb_set_text_to_status_bar(bench_scr->status_label, NULL);
}

/** Wait for necessary peripherals to be available
 *
 */
static void wait_for_peri_available(lb_benchmark_screen_t *bench_scr)
{
	lv_obj_t * tab_btns;
	lv_timer_t *timer;

	/* disable operation for measurement tab */
	tab_btns = lv_tabview_get_tab_btns(bench_scr->tabview);
	lv_btnmatrix_set_btn_ctrl(tab_btns, (uint16_t)BENCHMARK_TAB_ID_MEASURE,
						LV_BTNMATRIX_CTRL_DISABLED);

	/* Start a timer used for checking status of peripherals */
	bench_scr->peri_timer = lv_timer_create(peripheral_timer_cb,
				PERI_CHECK_TIMER_PERIOD, (void *)bench_scr);
}

/** Set up configuration tab
 *
 * Set up parts/objects on configuration tab when a benchmark tool is selected
 * on list screen.
 *
 * @param gui
 * @param bench
 * @return none
 */
void lb_setup_benchmark_cfg_tab(lb_gui_demo_t *gui, lb_cfg_benchmark_t *bench)
{
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_config_t *config_tab;
	char str_name[MAX_STRLEN_BENCH_NAME + MAX_STRLEN_BENCH_SUMMARY + 3];
	char str_time[MAX_STRLEN_BENCH_TIME + 80];
	int32_t check;

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	config_tab = (lb_benchtab_config_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_CONFIG];

	/* Operation guide */
	lv_label_set_text_static(config_tab->guide_label, BENCH_CFG_OPERATION_GUIDE_TXT);

	/* Name and summary */
	snprintf(str_name, sizeof str_name, "%s: %s", bench->name, bench->summary);
	lv_label_set_text(config_tab->name_label, str_name);
	/* Features */
	lv_label_set_text_static(config_tab->features_label,
			(bench->features) ? bench->features: DEFAULT_EMPTY_STRING);
	/* Time */
	if (bench->time[0] != '\0') {
		snprintf(str_time, sizeof str_time, BENCH_CFG_TIME_INFO_TXT,
								bench->time);
		lv_label_set_text(config_tab->time_label, str_time);
	}
	else {
		lv_label_set_text(config_tab->time_label, DEFAULT_EMPTY_STRING);
	}
	/* Configurations */
	setup_configurations(gui, bench,
			bench_scr->benchmark_tab[BENCHMARK_TAB_ID_CONFIG]);

	/* Check necessary device */
	check = lb_demo_platform_check_peripheral(bench);
	if (check) {
		wait_for_peri_available(bench_scr);
		fprintf(stderr, "Necessary peripherals are not detected.\n");
		lb_set_text_to_status_bar(bench_scr->status_label,
						BENCH_CFG_PERIPHERAL_ERR_TXT);
	}
	else {	/* Clear the previous error info on status bar */
		lb_set_text_to_status_bar(bench_scr->status_label, NULL);
	}
}

/*
 * Set up measurement tab
 */
/** Append a string
 *
 */
static void append_string(char *dst, char *src, size_t *index)
{
	size_t length;

	length = strlen(src);
	memcpy(&dst[*index], src, length);

	*index += length;
}

/** Generate argument list of a benchmark tool
 *
 * The argument list is created based on option settings in the config tab.
 *
 */
static void prepare_tool_command(lb_gui_demo_t *gui, lb_cfg_benchmark_t *bench)
{
	lb_benchmark_screen_t *bench_scr;
	lb_cfg_benchmark_option_t *options;
	size_t idx;
	char *top;
	char **argv;

	if ((!gui) || (!bench))
		return;

	if (bench->command)
		free(bench->command);

	bench->command = lb_allocate_memory(MAX_STRLEN_BENCH_COMMAND);
	if (!bench->command) {	/* Creating command failed due to malloc() error. */
		return;
	}
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	top = bench->command;
	argv = bench_scr->tool_argv;
	idx = 0;

	*argv++ = top;
	append_string(top, bench->path, &idx);
	top[idx++] = '\0';

	options = bench->options;
	while (options) {
		if (!options->use) {
			options = options->next;
			continue;	/* skip unused option */
		}
		if (options->option_str[0] != '\0') {
			*argv++ = &top[idx];
			append_string(top, options->option_str, &idx);
			if (top[idx - 1] == '=') {
				append_string(top, options->current_value, &idx);
				top[idx++] = '\0';
				options = options->next;
				continue;
			}
			top[idx++] = '\0';
		}
		if (options->current_value[0] != '\0') {
			*argv++ = &top[idx];
			append_string(top, options->current_value, &idx);
			top[idx++] = '\0';
		}
		options = options->next;
	}
	*argv = NULL;
}

/** Create a command for a benchmark tool
 *
 */
static void setup_benchmark_tool_cmd(lb_gui_demo_t *gui)
{
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_measure_t *measure_tab;
	char **argv;
	char command[MAX_STRLEN_BENCH_COMMAND];
	size_t len, idx;

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	idx = 0;
	argv = bench_scr->tool_argv;
	while (*argv) {
		len = strlen(*argv);
		memcpy(&command[idx], *argv, len);
		command[idx + len] = ' ';	/* Insert a space */
		idx += len + 1;
		if (idx >= sizeof (command)) {
			idx = sizeof (command) - 1;
			break;
		}
		argv++;
	}
	command[idx] = '\0';		/* end */

	lv_label_set_text(measure_tab->command_label, command);
}

/** Set up benchmark result by applying a filter
 *
 */
static int32_t setup_benchmark_result_with_filter(lv_obj_t *label,
				char *result, char *filter, size_t size)
{
	int32_t ret = 0;
	size_t len;
	FILE *fp = NULL;
	char *command = NULL;
	char *content = NULL;
	char *line = NULL;

	len = MAX_STRLEN_BENCH_FILTERS + strlen(LB_BENCHMARK_TMPRESULT_PATH);
	command = malloc(len);
	if (!command) {
		fprintf(stderr, "ERROR!! malloc() for benchmark result file"
								"failed.\n");
		goto ERROR;
	}
	/* Replace a file path in filter command with an actual result path */
	ret = lb_substitute_str(command, filter, LB_BENCHMARK_TMPRESULT_FILE,
									result);
	if (ret == -1)
		goto ERROR;

	/* filtering by popen */
	fp = popen(command, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! popen() for filtering failed.\n");
		goto ERROR;
	}
	content = malloc(size);
	if (!content) {
		fprintf(stderr, "ERROR!! malloc() for benchmark result file"
								"failed.\n");
		goto ERROR;
	}
	*content = '\0';
	line = malloc(size);
	if (!line) {
		fprintf(stderr, "ERROR!! malloc() for benchmark result file"
								"failed.\n");
		goto ERROR;
	}
	len = 0;
	while(fgets(line, size, fp) != NULL) {
		len += strlen(line);
		if (len > size) {
			size += size;
			content = realloc(content, size);
			if (content) {
				fprintf(stderr, "ERROR!! realloc() for"
					"benchmark result file failed.\n");
				goto ERROR;
			}
		}
		strcat(content, line);
	}
	lv_label_set_text(label, content);

ERROR:
	if (command)
		free(command);
	if (content)
		free(content);
	if (line)
		free(line);
	if (fp)
		pclose(fp);

	return ret;
}

/** Set up benchmark result
 *
 */
static void setup_benchmark_result(lb_benchmark_screen_t *bench_scr, lb_cfg_benchmark_t *bench)
{
	lb_benchtab_measure_t *measure_tab;
	lv_obj_t *parent;
	lv_coord_t pos_y;
	struct stat st;
	FILE *fp;
	char *content;
	size_t size, read_size;
	int32_t ret;

	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	/* Reset position of scroll bar */
	parent = lv_obj_get_parent(measure_tab->result_label);
	pos_y = lv_obj_get_scroll_y(parent);
	lv_obj_scroll_to_y(parent, -pos_y, LV_ANIM_OFF);

	if (!bench->result) {		/* There is no result file. */
		lv_label_set_text(measure_tab->result_label, " ");
		return;
	}

	/* Check the file */
	if (stat(bench->result, &st) == -1) {
		fprintf(stderr, "ERROR!! benchmark result file is not found.\n");
		free(bench->result);
		bench->result = NULL;
		return;
	}
	size = (size_t)st.st_size + 1;

	/* Didplay result with filtering */
	if (bench->filter) {
		ret = setup_benchmark_result_with_filter(
					measure_tab->result_label,
					bench->result, bench->filter, size);
		if (ret == 0)
			return;	/* Return when filtering succeeds. Otherwise
			benchmark result is displayed without filtering. */
	}
	/* Didplay result without filtering */
	fp = fopen(bench->result, "r");
	if (fp == NULL) {
		fprintf(stderr, "ERROR!! fopen() for benchmark result file failed.\n");
		return;
	}
	content = malloc(size);
	if (!content) {
		fprintf(stderr, "ERROR!! malloc() for benchmark result file failed.\n");
		fclose(fp);
		return;
	}
	read_size = fread(content, 1, size, fp);
	lv_label_set_text(measure_tab->result_label, content);

	free(content);
	fclose(fp);
}

/** Set up measurement tab
 *
 * Set up parts/objects on measurement tab when the tab is selected.
 *
 * @param gui
 * @param bench
 * @return none
 */
static void setup_benchmark_meas_tab(lb_gui_demo_t *gui, lb_cfg_benchmark_t *bench)
{
	lb_benchmark_screen_t *bench_scr;
	lb_benchtab_measure_t *measure_tab;

	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);
	measure_tab = (lb_benchtab_measure_t *)bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE];

	/* Operation guide */
	lv_label_set_text_static(measure_tab->guide_label, BENCH_MEAS_OPERATION_GUIDE_TXT);

	/* Create a tool command */
	prepare_tool_command(gui, bench);
	/* Display the tool command */
	setup_benchmark_tool_cmd(gui);

	/* Display result */
	setup_benchmark_result(bench_scr, bench);

	/* Benchmark tool has not started yet. */
	bench_scr->status = BENCHMARK_MEAS_STATE_STOP;
	/* Set up buttons */
	update_meas_buttons(bench_scr);
}

/** benchmark screen callback
 *
 * This function is called when load of benchmark screen starts.
 * The default tab is set to configuration tab.
 *
 * @param e
 * @return none
 */
static void create_bench_cb(lv_event_t *e)
{
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	lv_tabview_set_act(bench_scr->tabview, (uint32_t)BENCHMARK_TAB_ID_CONFIG, LV_ANIM_OFF);
}

/** tabvie event callback
 *
 * This funciton is called when tab is changed.
 * When measurement tab is selected, setup the measurement tab.
 *
 * @param e
 * @return none
 */
static void tabview_event_cb(lv_event_t *e)
{
	lb_gui_demo_t *gui;
	lb_benchmark_screen_t *bench_scr;
	lv_obj_t *tabview;
	uint16_t index;

	tabview = lv_event_get_target(e);
	index = lv_tabview_get_tab_act(tabview);

	gui = (lb_gui_demo_t *)lv_event_get_user_data(e);
	bench_scr = GET_SCREEN_DATA(lb_benchmark_screen_t, SCREEN_ID_BENCHMARK);

	if ((lb_benchmark_tab_id_t)index == BENCHMARK_TAB_ID_CONFIG) {
		lb_set_text_to_status_bar(bench_scr->status_label, NULL);
	}
	else if ((lb_benchmark_tab_id_t)index == BENCHMARK_TAB_ID_MEASURE) {
		setup_benchmark_meas_tab(gui, bench_scr->benchmark);
	}
}

/** Set up color styles for tab buttons
 *
 */
static void setup_tabbutton_styles(lv_obj_t *tab_btns)
{
	lv_style_selector_t selector;

	/* Base color */
	selector = LV_PART_MAIN | LV_STATE_DEFAULT;
	lv_obj_set_style_bg_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_BG_COLOR), selector);

	/* Default, unfocused tab */
	selector = LV_PART_ITEMS | LV_STATE_DEFAULT;
	lv_obj_set_style_text_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_TXT_COLOR), selector);

	/* Selected tab */
	selector = LV_PART_ITEMS | LV_STATE_CHECKED;
	lv_obj_set_style_bg_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_SEL_BG_COLOR), selector);
	lv_obj_set_style_bg_opa(tab_btns, BENCH_TAB_BTN_SEL_BG_OPACITY, selector);
	lv_obj_set_style_text_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_SEL_TXT_COLOR), selector);
	lv_obj_set_style_border_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_SEL_BDR_COLOR), selector);

	/* Disabled (locked) tab */
	selector = LV_PART_ITEMS | LV_STATE_DISABLED;
	lv_obj_set_style_text_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_DIS_TXT_COLOR), selector);

	/* Pressed tab */
	selector = LV_PART_ITEMS | LV_STATE_PRESSED;
	lv_obj_set_style_text_color(tab_btns, lv_color_hex(BENCH_TAB_BTN_PRESS_TXT_COLOR), selector);
}

/** Create benchmark screen
 *
 * Create basic parts for benchmark screen when the demo is initialized.
 *
 * @param gui
 * @return 0 on success, -1 on failure
 */
int32_t lb_create_benchmark_screen(lb_gui_demo_t *gui)
{
	lv_obj_t *screen;
	lv_obj_t *tabview;
	lv_obj_t *tab_btns;
	lv_obj_t *tab;
	lb_benchmark_screen_t *bench_scr;
	void *tab_data;
	lv_coord_t x, w, h;

	bench_scr = lb_allocate_memory(sizeof (lb_benchmark_screen_t));
	if (bench_scr == NULL) {
		return -1;
	}
	gui->screen_info.screen_data[SCREEN_ID_BENCHMARK] = (void *)bench_scr;

	tab_data = lb_allocate_memory(sizeof (lb_benchtab_config_t));
	if (tab_data == NULL) {
		return -1;
	}
	bench_scr->tab_data[BENCHMARK_TAB_ID_CONFIG] = tab_data;

	tab_data = lb_allocate_memory(sizeof (lb_benchtab_measure_t));
	if (tab_data == NULL) {
		return -1;
	}
	bench_scr->tab_data[BENCHMARK_TAB_ID_MEASURE] = tab_data;

	/* Benchmark configuration screen and measurement screen are the same
	   screen. They are implemented by using tabview. */
	screen = lv_obj_create(NULL);
	lv_obj_set_style_bg_color(screen, lv_color_hex(BENCH_COMMON_BG_COLOR), 0);
	bench_scr->screen = screen;

	lv_obj_add_event_cb(screen, create_bench_cb, LV_EVENT_SCREEN_LOAD_START, gui);

	/* Tabview */
	h = (lv_coord_t)((BENCH_TAB_BTN_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	tabview = lv_tabview_create(screen, LV_DIR_TOP, h);

	lv_obj_set_style_bg_color(tabview, lv_color_hex(BENCH_COMMON_BG_COLOR), 0);
	lv_obj_set_style_text_color(tabview, lv_color_hex(BENCH_COMMON_TXT_COLOR), 0);

	w = gui->width;
	h = (lv_coord_t)((BENCH_TABVIEW_HEIGHT * gui->height) / STANDARD_SCREEN_HEIGHT);
	lv_obj_set_size(tabview, w, h);

	tab_btns = lv_tabview_get_tab_btns(tabview);
	x = (lv_coord_t)((BENCH_TAB_BTN_LEFT_OFS * gui->width) / STANDARD_SCREEN_WIDTH);
	lv_obj_set_style_pad_left(tab_btns, x, 0);
	x = (lv_coord_t)((BENCH_TAB_BTN_RIGHT_OFS * gui->width) / STANDARD_SCREEN_WIDTH);
	lv_obj_set_style_pad_right(tab_btns, x, 0);

	setup_tabbutton_styles(tab_btns);

	bench_scr->tabview = tabview;

	lv_obj_add_event_cb(tabview, tabview_event_cb, LV_EVENT_VALUE_CHANGED, gui);
	/* Disable swiping */
	lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);

	/* Tab */
	tab = lv_tabview_add_tab(tabview, BENCH_TAB_BTN_CFG);
	create_configuration_tab(tab, gui);
	bench_scr->benchmark_tab[BENCHMARK_TAB_ID_CONFIG] = tab;

	tab = lv_tabview_add_tab(tabview, BENCH_TAB_BTN_MEASURE);
	create_measurement_tab(tab, gui);
	bench_scr->benchmark_tab[BENCHMARK_TAB_ID_MEASURE] = tab;

	/* Status bar */
	lb_create_status_bar(gui, screen, &bench_scr->status_label);

	/* Back button */
	create_back_button(gui, screen);

	/* Quit button */
	bench_scr->quit_btn = lb_create_quit_button(gui, screen);

	return 0;
}

