/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024, 2025 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	BENCHMARK_DEMO_GUI_H
#define	BENCHMARK_DEMO_GUI_H

#include	<stdint.h>
#include	<stdbool.h>


#include	"lvgl/lvgl.h"
#include	"lvgl/lv_drivers/lv_drv_conf.h"

#if	USE_FBDEV && USE_EVDEV
  #undef	RUNS_ON_WAYLAND
#elif	USE_WAYLAND
  #define	RUNS_ON_WAYLAND
#else
  #error	LVGL drivers configration error.
#endif

#ifdef	RUNS_ON_WAYLAND
#include	"lvgl/lv_drivers/wayland/wayland.h"
#else
#include	"lvgl/lv_drivers/display/fbdev.h"
#include	"lvgl/lv_drivers/indev/evdev.h"
#endif	/* RUNS_ON_WAYLAND */

#include	"../include/benchmark_demo_gui_text.h"

/******************************************************************************
 * Declarations and definition for configuration file
 *****************************************************************************/
#define	LB_DEFAULT_CFGFILE		"/usr/share/benchmark_demo/rz_bench_config.toml"

#define MAX_STRLEN_OPT_NAME		((size_t)79)
#define MAX_STRLEN_OPT_STR		((size_t)79)
#define MAX_STRLEN_OPT_TEXT		((size_t)319)
#define MAX_STRLEN_OPT_PARA		((size_t)79)
#define MAX_NUM_OPTIONS			(16)
#define MAX_NUM_VALUES			(16)

#define CFG_OPT_UPDATED_USE		((uint32_t)1u)
#define CFG_OPT_UPDATED_CURRENT_VALUE	((uint32_t)2u)

typedef enum
{
	CFG_OPT_PARAM_NONE = 0,
	CFG_OPT_PARAM_LABEL,
	CFG_OPT_PARAM_DROPDL,
	CFG_OPT_PARAM_NUMERIC,
	CFG_OPT_PARAM_IPADDR,
	CFG_OPT_PARAM_NUM
} lb_cfg_opt_param_t;

typedef struct _lb_cfg_benchmark_option_t
{
	char name[MAX_STRLEN_OPT_NAME + 1];
	char option_str[MAX_STRLEN_OPT_STR + 1];
	bool use;
	lb_cfg_opt_param_t type;
	char *option_text;
	char *values_list[MAX_NUM_VALUES];
	char current_value[MAX_STRLEN_OPT_PARA + 1];
	uint32_t update;
	void *benchmark;
	struct _lb_cfg_benchmark_option_t *next;
} lb_cfg_benchmark_option_t;


#define MAX_STRLEN_BENCH_NAME		((size_t)79)
#define MAX_STRLEN_BENCH_SUMMARY	((size_t)79)
#define MAX_STRLEN_BENCH_PATH		((size_t)4095)
#define MAX_STRLEN_BENCH_FEATURES	((size_t)1600)
#define MAX_STRLEN_BENCH_TIME		((size_t)79)
#define MAX_STRLEN_BENCH_FILTERS	((size_t)1600)
#define MAX_STRLEN_BENCH_COMMAND	((size_t)6556)
#define MAX_NUM_BENCHMARKS		(256)

#define CFG_BENCH_PERI_SD_CARD		((uint64_t)(1 << 0))
#define CFG_BENCH_PERI_USB_FLASH	((uint64_t)(1 << 1))
#define CFG_BENCH_PERI_EMMC		((uint64_t)(1 << 2))
#define CFG_BENCH_PERI_ETHERNET		((uint64_t)(1 << 3))

typedef struct _lb_cfg_benchmark_t
{
	char name[MAX_STRLEN_BENCH_NAME + 1];
	char summary[MAX_STRLEN_BENCH_SUMMARY + 1];
	char *path;
	char *features;
	char time[MAX_STRLEN_BENCH_TIME + 1];
	uint64_t peripheral;
	char *filter;
	lb_cfg_benchmark_option_t *options;
	char *result;
	char *command;
	bool updated;
	struct _lb_cfg_benchmark_t *next;
} lb_cfg_benchmark_t;


#define MAX_STRLEN_VERSION		((size_t)15)
#define MIN_STRLEN_VERSION		((size_t)9)
#define MAX_STRLEN_LOG_PATH		((size_t)3968)

typedef struct _lb_demo_configuration_t
{
	char version[MAX_STRLEN_VERSION + 1];
	char *log_path;
	lb_cfg_benchmark_t *benchmarks;
	bool configration_error;
} lb_demo_configuration_t;


/******************************************************************************
 * Declarations and definition for GUI screen
 *****************************************************************************/
#define		STANDARD_SCREEN_WIDTH		((lv_coord_t)1920)
#define		STANDARD_SCREEN_HEIGHT		((lv_coord_t)1080)
#define		STANDARD_FONT_SIZE		(28)
#define		STANDARD_BG_COLOR		((uint32_t)0xFFFFFF)
#define		DEFAULT_EMPTY_STRING		" "

/*
 * Common parts
 */
/* Button color */
#define		BUTTON_BG_COLOR			((uint32_t)0x2A289Du)
#define		BUTTON_BG_DISABLED_COLOR	((uint32_t)0x9D9D9Du)

/* Status bar */
#define		STATUS_BAR_POS_X		((lv_coord_t)0)
#define		STATUS_BAR_POS_Y		((lv_coord_t)0)
#define		STATUS_BAR_WIDTH		(STANDARD_SCREEN_WIDTH)
#define		STATUS_BAR_HEIGHT		((lv_coord_t)96)
#define		STATUS_BAR_TXT_POS_X		((lv_coord_t)64)
#define		STATUS_BAR_TXT_POS_Y		((lv_coord_t)0)
#define		STATUS_BAR_TXT_WIDTH		(STATUS_BAR_WIDTH - STATUS_BAR_TXT_POS_X * 2)
#define		STATUS_BAR_TXT_HEIGHT		(STATUS_BAR_HEIGHT)

#define		STATUS_BAR_BG_COLOR		((uint32_t)0xB5B5B5)
#define		STATUS_BAR_DEFAULT_LABEL	"Staus: "

/* Quit button */
#define		QUIT_BUTTON_POS_X		((lv_coord_t)1792)
#define		QUIT_BUTTON_POS_Y		((lv_coord_t)16)
#define		QUIT_BUTTON_WIDTH		((lv_coord_t)96)
#define		QUIT_BUTTON_HEIGHT		((lv_coord_t)64)

/* Modal dialog for shutdown */
#define		SHUTDOWN_DLG_WIDTH		((lv_coord_t)896)
#define		SHUTDOWN_DLG_HEIGHT		((lv_coord_t)504)
#define		SHUTDOWN_DLG_BTN_HEIGHT		((lv_coord_t)96)

#define		SHUTDOWN_DLG_BTNTXT_QUIT	"Quit"
#define		SHUTDOWN_DLG_BTNTXT_POWOFF	"Power Off"
#define		SHUTDOWN_DLG_BTNTXT_REBOOT	"Reboot"
#define		SHUTDOWN_DLG_BTNTXT_CANCEL	"Cancel"

#define		SHUTDOWN_DLG_BG_COLOR		((uint32_t)0x7C909B)
#define		SHUTDOWN_DLG_TXT_COLOR		((uint32_t)0xFFFFFF)
#define		SHUTDOWN_DLG_BTN_BG_COLOR	((uint32_t)0x8AA9D0)
#define		SHUTDOWN_DLG_BTN_TXT_COLOR	((uint32_t)0xFFFFFF)

typedef enum {
	SHUTDOWN_BTN_ID_QUIT = 0,
	SHUTDOWN_BTN_ID_POWOFF,
	SHUTDOWN_BTN_ID_REBOOT,
	SHUTDOWN_BTN_ID_CANCEL,
	SHUTDOWN_BTN_ID_NUM
} lb_shutdown_btn_id_t;

typedef struct {
	lv_coord_t x;
	lv_coord_t y;
	lv_coord_t w;
	lv_coord_t h;
} lb_rect_t;

/*
 * Splash screen
 */
#define		DEFAULT_MAGNIFICATION	(256)
#define		STANDARD_LOGO_RATIO	(960)

typedef struct {
	lv_obj_t *screen;
} lb_splash_screen_t;

/*
 * Benchmark list screen
 */
#define		LIST_OPERATION_GUIDE_POS_X	((lv_coord_t)64)
#define		LIST_OPERATION_GUIDE_POS_Y	((lv_coord_t)64)

#define		LIST_POS_Y			((lv_coord_t)192)
#define		LIST_HEIGHT			((lv_coord_t)792)
#define		LIST_BUTTON_HEIGHT		((lv_coord_t)96)
#define		LIST_SCROLLBAR_WIDTH		((lv_coord_t)16)
#define		LIST_TITLE_HEIGHT		((lv_coord_t)48)

#define		LIST_COMMON_BG_COLOR		((uint32_t)0x615E8E)
#define		LIST_COMMON_TXT_COLOR		((uint32_t)0xFFFFFF)
#define		LIST_TITLE_BG_COLOR		((uint32_t)0x06418C)

typedef struct {
	lv_obj_t *screen;

	lv_obj_t *status_label;
} lb_list_screen_t;

/*
 * Benchmark configuration/measurement screen
 */
#define		BENCH_COMMON_BG_COLOR		((uint32_t)0x615E8E)
#define		BENCH_COMMON_TXT_COLOR		((uint32_t)0xFFFFFF)

/* Back button */
#define		BENCH_BACK_BUTTON_POS_X		((lv_coord_t)32)
#define		BENCH_BACK_BUTTON_POS_Y		((lv_coord_t)16)
#define		BENCH_BACK_BUTTON_WIDTH		((lv_coord_t)96)
#define		BENCH_BACK_BUTTON_HEIGHT	((lv_coord_t)64)
/* Tab view */
#define		BENCH_TABVIEW_HEIGHT		((lv_coord_t)(STANDARD_SCREEN_HEIGHT - STATUS_BAR_HEIGHT))

#define		BENCH_TAB_BTN_HEIGHT		((lv_coord_t)96)
#define		BENCH_TAB_BTN_CFG		"Configuration"
#define		BENCH_TAB_BTN_MEASURE		"Measurement"

#define		BENCH_TAB_BTN_LEFT_OFS		((lv_coord_t)192)
#define		BENCH_TAB_BTN_RIGHT_OFS		((lv_coord_t)960)

#define		BENCH_TAB_BTN_BG_COLOR		((uint32_t)0xB1C6E0)
#define		BENCH_TAB_BTN_TXT_COLOR		(BENCH_COMMON_TXT_COLOR)
#define		BENCH_TAB_BTN_SEL_BG_COLOR	((uint32_t)0x2A289D)
#define		BENCH_TAB_BTN_SEL_BG_OPACITY	((lv_opa_t)0x20u)
#define		BENCH_TAB_BTN_SEL_TXT_COLOR	((uint32_t)0x2A289D)
#define		BENCH_TAB_BTN_SEL_BDR_COLOR	((uint32_t)0x2A289D)
#define		BENCH_TAB_BTN_DIS_TXT_COLOR	((uint32_t)0x9D9D9D)
#define		BENCH_TAB_BTN_PRESS_TXT_COLOR	((uint32_t)0x2A289D)

/* Operation guide on tabs  */
#define		BENCH_OPERATION_GUIDE_POS_X	((lv_coord_t)128)
#define		BENCH_OPERATION_GUIDE_POS_Y	((lv_coord_t)0)
#define		BENCH_OPERATION_GUIDE_WIDTH	((lv_coord_t)1440)
#define		BENCH_OPERATION_GUIDE_HEIGHT	((lv_coord_t)128)

/* Save button on configuration tab  */
#define		BENCH_CFG_SAVE_BTN_POS_X	((lv_coord_t)1776)
#define		BENCH_CFG_SAVE_BTN_POS_Y	((lv_coord_t)16)
#define		BENCH_CFG_SAVE_BTN_WIDTH	((lv_coord_t)96)
#define		BENCH_CFG_SAVE_BTN_HEIGHT	((lv_coord_t)64)
/* Name and summary (description field) on configuration tab */
#define		BENCH_CFG_NAME_POS_X		((lv_coord_t)0)
#define		BENCH_CFG_NAME_POS_Y		((lv_coord_t)128)
#define		BENCH_CFG_NAME_WIDTH		((lv_coord_t)900)
#define		BENCH_CFG_NAME_HEIGHT		((lv_coord_t)60)
/* Features (description field) on configuration tab */
#define		BENCH_CFG_FEATUREs_POS_X	((lv_coord_t)0)
#define		BENCH_CFG_FEATURES_POS_Y	((lv_coord_t)192)
#define		BENCH_CFG_FEATURES_WIDTH	((lv_coord_t)900)
#define		BENCH_CFG_FEATURES_HEIGHT	((lv_coord_t)540)
/* Time (description field) on configuration tab */
#define		BENCH_CFG_TIME_POS_X		((lv_coord_t)0)
#define		BENCH_CFG_TIME_POS_Y		((lv_coord_t)740)
#define		BENCH_CFG_TIME_WIDTH		((lv_coord_t)900)
#define		BENCH_CFG_TIME_HEIGHT		((lv_coord_t)120)
/* Header (configuration field) on configuration tab */
#define		BENCH_CFG_OPT_HEADER_POS_X	((lv_coord_t)900)
#define		BENCH_CFG_OPT_HEADER_POS_Y	((lv_coord_t)128)
#define		BENCH_CFG_OPT_HEADER_WIDTH	((lv_coord_t)960)
#define		BENCH_CFG_OPT_HEADER_HEIGHT	((lv_coord_t)80)
#define		BENCH_CFG_OPT_HEADER_BG_COLOR	((uint32_t)0x06418C)
#define		BENCH_CFG_OPT_HEADER		"Benchmark tool options"

/* Options area (configuration field) on configuration tab */
#define		BENCH_CFG_OPT_START_X		(BENCH_CFG_OPT_HEADER_POS_X)
#define		BENCH_CFG_OPT_START_Y		(BENCH_CFG_OPT_HEADER_POS_Y + \
						BENCH_CFG_OPT_HEADER_HEIGHT + \
						(lv_coord_t)16)
#define		BENCH_CFG_OPT_WIDTH		(BENCH_CFG_OPT_HEADER_WIDTH)
#define		BENCH_CFG_OPT_HEIGHT		((lv_coord_t)640)
#define		BENCH_CFG_OPT_MARGIN_WIDTH	((lv_coord_t)32)

#define		BENCH_CFG_OPT_BG_COLOR		((uint32_t)0x8AA9D0)
#define		BENCH_CFG_OPT_TXT_COLOR		(BENCH_COMMON_TXT_COLOR)

#define		BENCH_CFG_OPT_NAME_HEIGHT	((lv_coord_t)60)
#define		BENCH_CFG_OPT_NAME_OFS_X	((lv_coord_t)0)
#define		BENCH_CFG_OPT_USE_HEIGHT	((lv_coord_t)60)
#define		BENCH_CFG_OPT_USE_OFS_X		((lv_coord_t)40)
#define		BENCH_CFG_OPT_USE_TEXT		"Enable/Disable option: "
#define		BENCH_CFG_OPT_USESW_OFS_X	((lv_coord_t)440)

#define		BENCH_CFG_OPT_PAR_VAL_HEIGHT	((lv_coord_t)60)
#define		BENCH_CFG_OPT_PAR_VAL_OFS_X	((lv_coord_t)40)
#define		BENCH_CFG_OPT_PAR_VAL_TEXT	"Current value: "
#define		BENCH_CFG_OPT_PAR_CRVAL_HEIGHT	(BENCH_CFG_OPT_PAR_VAL_HEIGHT)
#define		BENCH_CFG_OPT_PAR_CRVAL_OFS_X	((lv_coord_t)320)
#define		BENCH_CFG_OPT_PAR_GUIDE_OFS_X	((lv_coord_t)60)
#define		BENCH_CFG_OPT_PAR_GUIDE_OFS_Y	((lv_coord_t)40)
#define		BENCH_CFG_OPT_PAR_GUIDE_WIDTH	((lv_coord_t)300)
#define		BENCH_CFG_OPT_PAR_GUIDE_HEIGHT	((lv_coord_t)240)
#define		BENCH_CFG_OPT_PAR_GUIDE_TEXT	"Press enter key after the value is changed.\n"\
	"Empty value cannot be set."
#define		BENCH_CFG_OPT_PAR_BACKSP_TEXT	"BS"
#define		BENCH_CFG_OPT_PAR_ENTER_TEXT	"Enter"

#define		BENCH_CFG_OPT_PAR_DRPDWN_OFS_Y	((lv_coord_t)-8)
#define		BENCH_CFG_OPT_PAR_DRPDWN_HEIGHT	((lv_coord_t)72)
#define		BENCH_CFG_OPT_PAR_NUMTXT_OFS_Y	((lv_coord_t)-8)
#define		BENCH_CFG_OPT_PAR_NUMTXT_HEIGHT	((lv_coord_t)72)
#define		BENCH_CFG_OPT_PAR_NUM_WIDTH	((lv_coord_t)300)
#define		BENCH_CFG_OPT_PAR_NUM_HEIGHT	((lv_coord_t)240)

#define		BENCH_CFG_OPT_TEXT_CHAR_LINE	((lv_coord_t)50)
#define		BENCH_CFG_OPT_TEXT_HEIGHT	((lv_coord_t)36)
#define		BENCH_CFG_OPT_TEXT_OFS_X	((lv_coord_t)80)
#define		BENCH_CFG_OPT_SEP_HEIGHT	((lv_coord_t)60)
#define		BENCH_CFG_OPT_SEP_OFS_X		((lv_coord_t)0)
#define		BENCH_CFG_OPT_SEP_TEXT		"________________________________"

/* Start button on measurement tab  */
#define		BENCH_MEAS_START_BTN_POS_X	((lv_coord_t)1552)
#define		BENCH_MEAS_START_BTN_POS_Y	((lv_coord_t)16)
#define		BENCH_MEAS_START_BTN_WIDTH	((lv_coord_t)96)
#define		BENCH_MEAS_START_BTN_HEIGHT	((lv_coord_t)64)
/* Cancel button on measurement tab  */
#define		BENCH_MEAS_CANCEL_BTN_POS_X	((lv_coord_t)1664)
#define		BENCH_MEAS_CANCEL_BTN_POS_Y	((lv_coord_t)16)
#define		BENCH_MEAS_CANCEL_BTN_WIDTH	((lv_coord_t)96)
#define		BENCH_MEAS_CANCEL_BTN_HEIGHT	((lv_coord_t)64)
/* Save button on measurement tab  */
#define		BENCH_MEAS_SAVE_BTN_POS_X	((lv_coord_t)1776)
#define		BENCH_MEAS_SAVE_BTN_POS_Y	((lv_coord_t)16)
#define		BENCH_MEAS_SAVE_BTN_WIDTH	((lv_coord_t)96)
#define		BENCH_MEAS_SAVE_BTN_HEIGHT	((lv_coord_t)64)

/* Command (result field) on measurement tab */
#define		BENCH_MEAS_CMD_POS_X		((lv_coord_t)0)
#define		BENCH_MEAS_CMD_POS_Y		((lv_coord_t)144)
#define		BENCH_MEAS_CMD_WIDTH		((lv_coord_t)1878)
#define		BENCH_MEAS_CMD_HEIGHT		((lv_coord_t)60)
#define		BENCH_MEAS_CMD_BG_COLOR		((uint32_t)0x000000)
#define		BENCH_MEAS_CMD_TXT_COLOR	((uint32_t)0xFFFFFF)
/* Result (result field) on measurement tab */
#define		BENCH_MEAS_RESULT_POS_X		((lv_coord_t)0)
#define		BENCH_MEAS_RESULT_POS_Y		((lv_coord_t)208)
#define		BENCH_MEAS_RESULT_WIDTH		((lv_coord_t)1878)
#define		BENCH_MEAS_RESULT_HEIGHT	((lv_coord_t)680)
#define		BENCH_MEAS_RESULT_BG_COLOR	((uint32_t)0x000000)
#define		BENCH_MEAS_RESULT_TXT_COLOR	((uint32_t)0xFFFFFF)

typedef struct {
	lv_obj_t *guide_label;
	lv_obj_t *name_label;
	lv_obj_t *features_label;
	lv_obj_t *time_label;
} lb_benchtab_config_t;

typedef struct {
	lv_obj_t *guide_label;
	lv_obj_t *command_label;
	lv_obj_t *result_label;
	lv_obj_t *start_btn;
	lv_obj_t *cancel_btn;
	lv_obj_t *save_btn;
} lb_benchtab_measure_t;

typedef enum {
	BENCHMARK_MEAS_STATE_STOP = 0,
	BENCHMARK_MEAS_STATE_RUN,
	BENCHMARK_MEAS_STATE_NUM
} lb_benchmark_meas_state_t;

typedef enum {
	BENCHMARK_TAB_ID_CONFIG = 0,
	BENCHMARK_TAB_ID_MEASURE,
	BENCHMARK_TAB_ID_NUM
} lb_benchmark_tab_id_t;

typedef struct {
	lv_obj_t *screen;
	uint32_t index;
	lb_cfg_benchmark_t *benchmark;

	lv_obj_t *tabview;
	lv_obj_t *benchmark_tab[BENCHMARK_TAB_ID_NUM];
	lb_benchmark_tab_id_t current_tab;
	void *tab_data[BENCHMARK_TAB_ID_NUM];

	lv_obj_t *status_label;
	lv_obj_t *back_btn;
	lv_obj_t *quit_btn;

	lv_obj_t *opt_obj;	/* base object for configuratio area */
	lv_timer_t *peri_timer;
	char *tool_argv[MAX_NUM_OPTIONS * 2 + 2];
	lb_benchmark_meas_state_t status;
} lb_benchmark_screen_t;

/*
 * Common
 */

typedef enum {
        SCREEN_ID_SPLASH = 0,
        SCREEN_ID_LIST,
        SCREEN_ID_BENCHMARK,
        SCREEN_ID_NUM
} lb_screen_id_t;

typedef struct {
	lb_screen_id_t current_screen;
	void *screen_data[SCREEN_ID_NUM];
	lv_style_t base_style;
	lv_style_t button_style;
} lb_gui_screen_t;

#define		GET_SCREEN_DATA(type, index) \
		((type *)(gui->screen_info.screen_data[index]))


/******************************************************************************
 * Declarations and definition for GUI demo
 *****************************************************************************/
#define	LB_MAJOR_VERSION		(1)	/* Major number 0 ~ 9999999 */
#define	LB_MINOR_VERSION		(2)	/* Minor number 0 ~ 99 */

#if LB_MAJOR_VERSION > 9999999
	#error	"LB_MAJOR_VERSION is too big."
#endif
#if LB_MINOR_VERSION > 99
	#error	"LB_MINOR_VERSION is too big."
#endif

#define	LB_BENCHMARK_TMPRESULT_FILE	"rz_bench_XXXXXX"
#define	LB_BENCHMARK_TMPRESULT_PATH	"/tmp/rz_bench_XXXXXX"

#ifndef RUNS_ON_WAYLAND /* Runs with FBDEV and EVDEV */
typedef struct {
	lv_coord_t width;
	lv_coord_t height;
	bool end;
	lv_color_t *buff;
	lv_disp_draw_buf_t draw_buf;
	lv_disp_drv_t drv;
	lv_disp_t *disp;
	lv_indev_drv_t indev_drv;
	lv_indev_t *mouse_indev;
} lb_disp_fbevdev_t;
#endif

typedef enum {
	GUI_SHUTDOWN_TYPE_QUIT = 0,
	GUI_SHUTDOWN_TYPE_POWEROFF,
	GUI_SHUTDOWN_TYPE_REBOOT,
	GUI_SHUTDOWN_TYPE_NUM
} lb_gui_shutdown_type_t;

typedef struct {
	lv_coord_t width;
	lv_coord_t height;
	void *disp;
	lb_gui_shutdown_type_t shutdown_type;

	lb_gui_screen_t screen_info;

	char *config_path;
	lb_demo_configuration_t config;
} lb_gui_demo_t;


int32_t lb_demo_gui(int32_t width, int32_t height, void *disp, char *cfg_path);
void lb_demo_quit(void);
lb_gui_shutdown_type_t lb_demo_get_shutdown_type(void);

int32_t lb_create_splash_screen(lb_gui_demo_t *gui);
int32_t lb_create_benchmark_list_screen(lb_gui_demo_t *gui);
int32_t lb_create_benchmark_screen(lb_gui_demo_t *gui);

void *lb_allocate_memory(size_t size);
int32_t lb_substitute_str(char *output, char *input, const char *oldstr,
						const char *newstr);
lv_obj_t *lb_create_quit_button(lb_gui_demo_t *gui, lv_obj_t *obj);
void lb_set_text_to_status_bar(lv_obj_t *label, const char *text);
void lb_create_status_bar(lb_gui_demo_t *gui, lv_obj_t *obj,
			lv_obj_t **status_label);
lv_obj_t *lb_create_label(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text);
lv_obj_t *lb_create_label_with_concat(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect,
			const char *text1, const char *text2, bool space);
lv_obj_t *lb_create_label_with_bg(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text,
			uint32_t bg_color);
lv_obj_t *lb_create_button(lb_gui_demo_t *gui, lv_obj_t *obj,
			const lb_rect_t *rect, const char *text);
void lb_setup_benchmark_cfg_tab(lb_gui_demo_t *gui, lb_cfg_benchmark_t *bench);

#endif	/* BENCHMARK_DEMO_GUI_H */
