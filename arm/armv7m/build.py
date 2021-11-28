#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys


board_parm = 'netp'
if len(sys.argv) > 1:
    board_parm = sys.argv[1]

bin_obj_dir = './bin/' + board_parm + '/'

if os.path.exists("./obj"):
	shutil.rmtree("./obj")

if os.path.exists(bin_obj_dir):
	shutil.rmtree(bin_obj_dir)
	
os.mkdir("obj")
os.makedirs(bin_obj_dir)	

board = 'board=' + board_parm
os.system("make %s" % (board))

g = os.walk("./src")
for path,d,filelist in g:
	#print d;
	for filename in filelist:
		#print os.path.join(path, filename)
                if filename.endswith(".o"):
                    #print filename
                    file_path = os.path.join(path, filename)
                    print file_path
                    shutil.move(file_path, "./obj")
