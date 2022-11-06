#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys

board_parm = sys.argv[1]
board = 'board=' + board_parm
os.system("make  %s " % (board))
