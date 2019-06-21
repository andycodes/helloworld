#! /usr/bin/python

import os
import shutil
OUT_PATH="./out"
OBJ_PATH= OUT_PATH +"/obj"
if os.path.exists(OUT_PATH):
	shutil.rmtree(OUT_PATH)

os.makedirs(OBJ_PATH)
os.system('make')