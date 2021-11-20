#!/user/bin/python
#!conding=utf8

import glob 
import os
import shutil

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
