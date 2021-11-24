#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil
import sys


if os.path.exists("./obj"):
	shutil.rmtree("./obj")
	shutil.rmtree("./bin")
	
os.mkdir("obj")
os.mkdir("bin")	

#board = 'board=net' 'board=netp' 'board=lm3'
board = 'board=netp'
if len(sys.argv) > 1:
    board = 'board=' + sys.argv[1]

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
