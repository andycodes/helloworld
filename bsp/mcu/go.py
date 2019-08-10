#! /usr/bin/python

import os
import shutil
OUT_PATH="./out"
OUT_OBJ_PATH= OUT_PATH +"/obj"
OUT_LIBS_PATH = OUT_PATH +"/libs"
if os.path.exists(OUT_PATH):
	shutil.rmtree(OUT_PATH)

os.makedirs(OUT_OBJ_PATH)
os.makedirs(OUT_LIBS_PATH)
os.system('make')