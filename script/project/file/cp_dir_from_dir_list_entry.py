#! /usr/bin/python3

#! python  
#coding:utf-8  
# Filename : fileCp.py  
import sys  
import os    
import shutil   
  
fileList='dir_list.txt'  
targetDir='target'  

import string_split


filedir = open(fileList)  
line = filedir.readline()  
log = open('running.log','w')  
while line:  
        line = line.strip('\n'); 
        basename =  os.path.basename(line) 
        exists = os.path.exists(line)  
        if exists :  
            print ('copy '+line+' to '+os.getcwd()+'/'+targetDir+'/'+basename) 
            log.write('copy '+line+' to '+os.getcwd()+'/'+targetDir+'/'+basename+'\r\n')  
            target = targetDir+'/'+basename
            exists = os.path.exists(target)
            if exists:
                print (target+' already exists')
            else:
                shutil.copytree(line,targetDir+'/'+basename)  
        else:  
            print (line+' not exists')  
            log.write(line+' not exists'+'\r\n')  
        line = filedir.readline()  
log.close()
