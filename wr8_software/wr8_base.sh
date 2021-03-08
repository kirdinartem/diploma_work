#!/bin/zsh

# stop_base.sh

roslaunch wr8_software base_start.launch   camera_s:=false \
											camera_r:=false \
											solver:=true \
											lidar:=true \
											gui_server:=false \
											uc:=true
