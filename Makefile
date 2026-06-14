# 总的 Makefile，用于调用目录下各个子工程对应的 Makefile
# 注意： Linux 下编译方式：
# 1. 从 http://pkgman.jieliapp.com/doc/all 处找到下载链接
# 2. 下载后，解压到 /opt/jieli 目录下，保证
#   /opt/jieli/common/bin/clang 存在（注意目录层次）
# 3. 确认 ulimit -n 的结果足够大（建议大于8096），否则链接可能会因为打开文件太多而失败
#   可以通过 ulimit -n 8096 来设置一个较大的值
# 支持的目标
# make ac791n_demo_demo_ui
# make ac791n_demo_demo_matter
# make ac791n_demo_demo_hello
# make ac791n_demo_demo_edr
# make ac791n_demo_demo_uvc
# make ac791n_demo_demo_video
# make ac791n_demo_demo_wifi
# make ac791n_demo_demo_wifi_ext
# make ac791n_demo_demo_devkitboard
# make ac791n_demo_demo_audio
# make ac791n_demo_demo_ble
# make ac790n_wifi_camera
# make ac791n_wifi_camera
# make ac790n_wifi_story_machine
# make ac791n_wifi_story_machine
# make ac791n_wifi_ipc
# make ac791n_scan_box

.PHONY: all clean   ac791n_wifi_story_machine clean_ac791n_wifi_story_machine

all: ac791n_wifi_story_machine
	@echo +ALL DONE

clean: clean_ac791n_wifi_story_machine
	@echo +CLEAN DONE

ac791n_wifi_story_machine:
	$(MAKE) -C apps/wifi_story_machine/board/wl82 -f Makefile

clean_ac791n_wifi_story_machine:
	$(MAKE) -C apps/wifi_story_machine/board/wl82 -f Makefile clean

