#!/bin/bash

CATKIN_WS=`catkin locate`
ret=$?
if [ $ret -ne 0 ]; then
	echo "Must be called inside catkin workspace"
	exit 1
fi

CALL_DIR=`dirname $0`
if [ "$CALL_DIR" != "./wr8_msgs" ]; then
	echo "Must be called inside base repository"
	exit 1
fi

LIB_DST_DIR=`rospack find wr8_msgs`
rm -rf $LIB_DST_DIR/ros_lib

rosrun wr8_msgs make_uc_lib.py $LIB_DST_DIR $CATKIN_WS &&
rsync -avzPc $LIB_DST_DIR/ros_lib/ controller_wr_driver/ros_lib/
