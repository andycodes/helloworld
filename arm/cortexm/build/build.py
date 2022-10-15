#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys

ARCH = 'armv7m'
BOARD_LISTS = ['mps3-an547', 'mps2-an505', 'cm85']

board_parm = 'mps3-an547'
if len(sys.argv) > 1:
    board_parm = sys.argv[1]

if board_parm in BOARD_LISTS:
    ARCH = 'armv8m'

print (ARCH)


bin_obj_dir = './bin/' + board_parm + '/'

if os.path.exists("./obj"):
	shutil.rmtree("./obj")

if os.path.exists(bin_obj_dir):
	shutil.rmtree(bin_obj_dir)
	
os.mkdir("obj")
os.makedirs(bin_obj_dir)	

board = 'board=' + board_parm
arch = 'makefile_' + ARCH
toolchain = 'PWD_TOOLCHAIN=/project/gcc/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/bin'
os.system("make -f %s %s %s" % (arch, board, toolchain))

#move *.o
g = os.walk("./src")
for path,d,filelist in g:
	#print d;
	for filename in filelist:
		#print os.path.join(path, filename)
                if filename.endswith(".o"):
                    #print filename
                    file_path = os.path.join(path, filename)
                    print (file_path)
                    shutil.move(file_path, "./obj")
