/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	BENCHMARK_DEMO_GUI_TEXT_H
#define	BENCHMARK_DEMO_GUI_TEXT_H

#include	<stdint.h>
#include	<stdbool.h>


/******************************************************************************
 * Operation guide text for GUI screen
 *****************************************************************************/
#define		GUIDE_TEXT_COLOR	(0xFF8989)

/* Benchmark list screen */
#define	LIST_OPERATION_GUIDE_TXT	"Select a tool in the list below."

/* Benchmark configuration/measurement screen */
#define	BENCH_CFG_OPERATION_GUIDE_TXT	"Configure the benchmark tool options on the right side of the screen, "\
	"and then, select 'Measurement' tab to run the tool.\n"\
	"To save change of the configuration, press 'Save' button."

#define	BENCH_CFG_TIME_INFO_TXT		"This benchmark takes about %s to complete measurement."

#define	BENCH_MEAS_OPERATION_GUIDE_TXT	"Press 'Start' button to run the tool."\
	"After the tool finishes, result will be displayed below."\
	"The result can be saved into a file by pressing 'Save' button.\n"\
	"To stop the tool running, press 'Cancel' button. Please be aware "\
	"that you will not be able to do anything except for cancel "\
	"while the tool is running."

/* Modal dialog for shutdown */
#define	SHUTDOWN_DLG_GUIDE_TXT		"#FF8989 Press the button below:#\n\n"\
	"- #DFB118 Quit#:      exit this application demo program.\n"\
	"- #DFB118 Power Off#: exit this application demo program, and the system will be shut down.\n"\
	"- #DFB118 Reboot#:    exit this application demo program, and the system will be rebooted.\n"\
	"- #DFB118 Cancel#:    go back to the application demo porgram.\n"

/******************************************************************************
 * Status information text for GUI screen
 *****************************************************************************/
/* Benchmark list screen */
#define	LIST_CONFIG_ERR_TXT		"#D70000 ERROR!! Reading the configuration file failed. #"\
	"Please confirm whether the configuration file is correct.#"

/* Benchmark configuration/measurement screen */
#define	BENCH_CFG_PERIPHERAL_ERR_TXT	"#D70000 ERROR!! Peripherals required for the tool running are not detected. #"\
	"Please mount necessary peripherals, or you cannot select 'Measurement' tab.#"

#define	BENCH_MEAS_TOOL_STATUS_STOP	"#06418C The tool is stopped.#"
#define	BENCH_MEAS_TOOL_STATUS_RUN	"#06418C The tool is running.#"

#endif	/* BENCHMARK_DEMO_GUI_TEXT_H */
