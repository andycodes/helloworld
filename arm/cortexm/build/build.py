#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys

board_parm = sys.argv[1]
bin_obj_dir = './bin/' + board_parm + '/'

if os.path.exists("./obj"):
	shutil.rmtree("./obj")

if os.path.exists(bin_obj_dir):
	shutil.rmtree(bin_obj_dir)
	
os.mkdir("obj")
os.makedirs(bin_obj_dir)	

board = 'board=' + board_parm
toolchain = 'PWD_TOOLCHAIN=/project/gcc/arm-gnu-toolchain-12.2.mpacbti-bet1-x86_64-arm-none-eabi/bin'
os.system("make  %s %s" % (board, toolchain))

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
