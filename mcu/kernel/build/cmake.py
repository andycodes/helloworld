#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys

board_parm = 'mps3-an547'
bin_obj_dir = './bin/' + board_parm + '/'

if os.path.exists("./_build"):
	shutil.rmtree("./_build")

if os.path.exists(bin_obj_dir):
	shutil.rmtree(bin_obj_dir)

os.makedirs(bin_obj_dir)
os.mkdir("_build")
os.chdir("./_build")
os.system('pwd')
os.system('cmake .. -DCUR_PLAT=mps3-an547 -DCPU=cortex-m33')
os.system('make')

os.system('cp felix.* ../bin/mps3-an547/ -rf')