## How to Build RZ Linux Benchmark Demo

To build the RZ Linux Benchmark Demo, use a PC with Ubuntu 20.04 LTS.

Currently, RZ Linux Benchmark Demo is built based on RZ/G Verified Linux Package (hereinafter referred to as the "VLP") v3.0.5.
You can get the VLP/G from the following links:
* [RZ/G Verified Linux Package v3.0.5-update3](https://www.renesas.com/us/en/document/swo/rzg-verified-linux-package-v305-update3rtk0ef0045z0021azj-v305-update3zip?r=1597481)
* [RZ MPU Graphics Library Evaluation Version for RZ/G2L and RZ/G2LC v1.1.2](https://www.renesas.com/us/en/document/swo/rz-mpu-graphics-library-evaluation-version-rzg2l-and-rzg2lc-rtk0ef0045z13001zj-v112enzip?language=en&r=1522761)
* [RZ MPU Video Codec Library Evaluation Version for RZ/G2L v1.1.0](https://www.renesas.com/us/en/document/swo/rz-mpu-video-codec-library-evaluation-version-rzg2l-rtk0ef0045z15001zj-v110xxzip?language=en&r=1535641)

The build instructions below are almost the same as instructions in "Linux Start-up Guide" of the VLP.
For more detailed information about the instructions, see "Linux Start-up Guide".

---

1. Install the required packages  
Install some packages into your Linux Host PC, which are necessary in the following steps.
	```bash
	$ sudo apt-get update
	$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
	build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
	xz-utils debianutils iputils-ping libsdl1.2-dev xterm p7zip-full libyaml-dev \
	libssl-dev bmap-tools
	```
	And set up your git environment if you have never done it.  
	```bash
	$ git config --global user.email "<Your email address>"
	$ git config --global user.name "<Your user name>"
	```
	For more information, refer to "[Yocto Prject Quick Build](https://docs.yoctoproject.org/3.1.26/brief-yoctoprojectqs/brief-yoctoprojectqs.html)".

2. Set environment variables  
Set the following environment variables.
	```bash
	$ export WORK=<A directory path for building>
	$ export PLATFORM=rzg2l
	$ export BOARD=smarc-rzg2l
	$ export VLP_DIR=<A directory path for VLP packages>
	```
	Currently, RZ Linux benchmark demo supports only '_rzg2l_' for PLATFORM and '_smarc-rzg2l_' for BOARD.
	The directory set to VLP_DIR shall include VLP, graphics library package, and video codec package.  
	E.g.,
	* RTK0EF0045Z0021AZJ-v3.0.5-update3.zip
	* RTK0EF0045Z13001ZJ-v1.1.2_EN.zip
	* RTK0EF0045Z15001ZJ-v1.1.0_EN.zip

3. Decompress packages  
Create a working directory, and decompress VLP, graphics library package, and video codec package.
	```bash
	$ mkdir -p $WORK

	$ cd $VLP_DIR
	$ unzip RTK0EF0045Z0021AZJ-v3.0.5-update3.zip
	$ tar zxvf ${VLP_DIR}/RTK0EF0045Z0021AZJ-v3.0.5-update3/rzg_vlp_v3.0.5.tar.gz -C $WORK
	$ unzip RTK0EF0045Z13001ZJ-v1.1.2_EN.zip
	$ tar zxvf ${VLP_DIR}/RTK0EF0045Z13001ZJ-v1.1.2_EN/meta-rz-features_graphics_v1.1.2.tar.gz -C $WORK
	$ unzip RTK0EF0045Z15001ZJ-v1.1.0_EN.zip
	$ tar zxvf ${VLP_DIR}/RTK0EF0045Z15001ZJ-v1.1.0_EN/meta-rz-features_codec_v1.1.0.tar.gz -C $WORK
	```

4. Initialize build environment  
Run an environment setup script as follows.
	```bash
	$ cd $WORK
	$ TEMPLATECONF=$PWD/meta-renesas/meta-${PLATFORM}/docs/template/conf/ source poky/oe-init-build-env build
	```
5. Add layers  
Add meta-rz-graphics layer for graphics and meta-rz-codecs layer for video codec.
	```bash
	$ cd $WORK/build
	$ bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics
	$ bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs
	```

6. Apply a patch  
Apply a patch when you use VLP v3.0.5-update3.
	```bash
	$ cd $WORK/
	$ patch -p1 < ${VLP_DIR}/RTK0EF0045Z0021AZJ-v3.0.5-update3/v3.0.5-to-v3.0.5update3.patch
	```
	In this guide, VLP v3.0.5-update3 package is used. The different patches may be provided in a different version of the package.

7. Add a meta-layer for the demo  
Download and add meta-rz-demos layer.
	```bash
	$ cd $WORK/
	$ git clone https://github.com/renesas-rz/meta-rz-demos.git
	$ cd meta-rz-demos/
	$ git checkout dunfell/rz
	$ cd $WORK/build
	$ bitbake-layers add-layer ../meta-rz-demos
	```
8. Modify local.conf  
Modify local.conf to add RZ benchmark demo packages.
	```bash
	$ cd $WORK/build
	$ vi conf/local.conf
	```
	Add IMAGE_INSTALL_append and WHITELIST_GPL-3.0 to local.conf as follows.
	```
	IMAGE_INSTALL_append = " packagegroup-lvgl-demo packagegroup-benchmark-tools packagegroup-rz-benchmark-demo"
	WHITELIST_GPL-3.0 += " glmark2 "
	```
9. Build images  
Run bitbake command to build images.
	```bash
	$ cd $WORK/build
	$ MACHINE=${BOARD} bitbake core-image-weston
	```
	If you need to create an SDK toolchain, run bitbake command as follows.
	```bash
	$ cd $WORK/build
	$ MACHINE=${BOARD} bitbake core-image-weston -c populate_sdk
	```
	After building images or SDK toolchain, you can find them in the following directories respectively.
	* Images  
	\${WORK}/build/tmp/deploy/images/${BOARD}/
	* SDK toolchain  
	${WORK}/build/tmp/deploy/sdk/

The information about how to use the built images, refer to "Linux Start-up Guide" in the VLP.


[Back](../README.md)
