# rz_benchmark_demo

## Overview
'_rz_benchmark_demo_' is a demo application for RZ Linux Benchmark Demo.  
This demo program is a wayland client running on Weston.
It works as a program launcher.
User can start existing tools via GUI of the demo program.

### License

'_rz_benchmark_demo_' is licensed under the MIT License.
See [LICENSE.txt](../LICENSE.txt).

This program uses the following open-source libraries:

* Light and Versatile Graphics Library (LVGL)
  * URL: https://github.com/lvgl/lvgl
  * Version: v8.3
  * License: [MIT Licnese](https://github.com/lvgl/lvgl/blob/master/LICENCE.txt)

* LVGL Display and Touch pad drivers
  * URL: https://github.com/lvgl/lv_drivers
  * Version: v8.3
  * License: [MIT Licnese](https://github.com/lvgl/lv_drivers/blob/master/LICENSE)

* tomlc99 (a C library for TOML in c99)
  * URL: https://github.com/cktan/tomlc99
  * commit 5221b3d3d66c25a1dc6f0372b4f824f1202fe398
  * License: [MIT Licnese](https://github.com/cktan/tomlc99/blob/master/LICENSE)

And this demo program uses a font in the "FiraCode" family.
* Fira Code
  * URL: https://github.com/tonsky/FiraCode
  * Version: v6.2
  * License: [SIL OPEN FONT LICENSE Version 1.1](https://github.com/tonsky/FiraCode/blob/master/LICENSE)
    * See also [LICENSE.txt](../src/gui/material/font/LICENSE.txt).


### Target Devices and Supported Environment
* Target Devices
	* [RZ/G2L Evaluation Board Kit](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rz-mpus/rzg2l-evkit-rzg2l-evaluation-board-kit)

* Supported Environment
	* [RZ/G Verified Linux Package for RZ/G2L v3.0.5](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rz-mpus/rzg-linux-platform/rzg-marketplace/verified-linux-package/rzg-verified-linux-package#Download)


## Build Instructions
To build this demo program, use a PC with Ubuntu 20.04 LTS, and prepare the toolchain SDK.
For information about the toolchain, see ["How to build"](./how-to-build.md).

### Build
```bash
$ source /opt/poky/<version number of toolchain>/environment-setup-aarch64-poky-linux
$ make
```
Note: The LVGL libraries and tomlc99 libraries shall be installed in the toolchain in advance.

### Install
```bash
$ prefix=<a path to rootfs>/usr make install
```

## How to Use the Benchmark Demo
```bash
Usage: rz_benchmark_demo [OPTION]

Options are:
        -c, --config    specify configuration file
                        unless specified, /usr/share/benchmark_demo/rz_bench_config.toml is used
        -v, --version   output version information and exit
        -h, --help      display this help message and exit
```


## Configuration

'_rz_benchmark_demo_' has a configuration file written in TOML format.
<br>
All benchmark tools launched on this program are defined in the configuration file.
It means that you can add some tools to the RZ Linux Benchmark Demo by editing the configuration file without rebuilding the demo program.
The configuration file "_rz_bench_config.toml_" in "_/usr/share/benchmark_demo_" is used by default.

The information about how to change the configuration file, see [_rz_bench_config.toml_](../config/rz_bench_config.toml).
The specification of the configuration file is explained in the comments of the default configuration file.


[Back](../README.md)
