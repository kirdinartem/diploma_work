#!/usr/bin/env python3
from enum import Enum
import os

"""
This script containts json contants
"""

APP_VERSION = 1.0

class JsonNames:
    START = "start"
    FINISH = "finish"
    CELLS_AMOUNT = "cells amount"
    CELLS_SIZE = "cells size"
    SIZE = "size"
    OBJECTS = "objects"
    NAME = "name"
    POSITION = "position"
    POINT_1 = "point1"
    POINT_2 = "point2"
    SIGN_TYPE = "sign type"

    BOX = "box"
    WALL = "wall"
    SIGN = "sign"

class SignsTypes(Enum):
    STOP = "stop sign"
    ONLY_FORWARD = "only forward sign"
    ONLY_RIGHT = "only right sign"
    ONLY_LEFT = "only left sign"
    FORWARD_OR_RIGHT = "forward or right sign"
    FORWARD_OR_LEFT = "forward or left sign"

class ImagesPaths():
    PATH_TO_IMAGE = 'models'
    STOP = os.path.join(PATH_TO_IMAGE, 'brick-sign/brick.png')
    ONLY_FORWARD = os.path.join(PATH_TO_IMAGE, 'forward-sign/forward.png')
    ONLY_LEFT = os.path.join(PATH_TO_IMAGE, 'left-sign/left.png')
    ONLY_RIGHT = os.path.join(PATH_TO_IMAGE, 'right-sign/right.png')
    FORWARD_OR_LEFT = os.path.join(PATH_TO_IMAGE, 'forward-left-sign/frwd_left.png')
    FORWARD_OR_RIGHT = os.path.join(PATH_TO_IMAGE, 'forward-right-sign/frwd_right.png')

def sign_path_to_sign_type(img_path):
    if img_path is ImagesPaths.STOP:
        return SignsTypes.STOP.value
    elif img_path is ImagesPaths.ONLY_FORWARD:
        return SignsTypes.ONLY_FORWARD.value
    elif img_path is ImagesPaths.ONLY_LEFT:
        return SignsTypes.ONLY_LEFT.value
    elif img_path is ImagesPaths.ONLY_RIGHT:
        return SignsTypes.ONLY_RIGHT.value
    elif img_path is ImagesPaths.FORWARD_OR_LEFT:
        return SignsTypes.FORWARD_OR_LEFT.value
    elif img_path is ImagesPaths.FORWARD_OR_RIGHT:
        return SignsTypes.FORWARD_OR_RIGHT.value
    else:
        return " "

def sign_type_to_sign_path(sign_type):
    if sign_type == SignsTypes.STOP.value:
        return ImagesPaths.STOP
    elif sign_type == SignsTypes.ONLY_FORWARD.value:
        return ImagesPaths.ONLY_FORWARD
    elif sign_type == SignsTypes.ONLY_LEFT.value:
        return ImagesPaths.ONLY_LEFT
    elif sign_type == SignsTypes.ONLY_RIGHT.value:
        return ImagesPaths.ONLY_RIGHT
    elif sign_type == SignsTypes.FORWARD_OR_LEFT.value:
        return ImagesPaths.FORWARD_OR_LEFT
    elif sign_type == SignsTypes.FORWARD_OR_RIGHT.value:
        return ImagesPaths.FORWARD_OR_RIGHT
    else:
        return " "
