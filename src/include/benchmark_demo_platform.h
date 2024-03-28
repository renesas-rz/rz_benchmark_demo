/**
 * RZ Linux Benchmark Demo
 *
 * Copyright (C) 2024 Renesas Electronics Corp. All rights reserved.
 */

#ifndef	BENCHMARK_DEMO_PLATFORM_H
#define	BENCHMARK_DEMO_PLATFORM_H

#include        "lvgl/lvgl.h"
#include        "lvgl/lv_drivers/wayland/wayland.h"

#include	"../include/benchmark_demo_gui.h"

int32_t lb_demo_platform_get_resolution(int32_t *width, int32_t *height);
int32_t lb_demo_platform_start_benchmark(lb_benchmark_screen_t *bench_scr);
int32_t lb_demo_platform_check_benchmark_stop(void);
int32_t lb_demo_platform_cancel_benchmark(void);
int32_t lb_demo_platform_check_peripheral(lb_cfg_benchmark_t *bench);

#endif	/* BENCHMARK_DEMO_PLATFORM_H */
