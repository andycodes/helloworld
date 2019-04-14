#! /usr/bin/python3

import os
import shutil

def string_split(str_name):
	ls = str_name.split("-I")
	if len(ls) > 1:
		tmp_str = ls[1].replace("\\", '')
		return tmp_str

	ls = str_name.strip()
	if ".c" in ls:
		ls = ls.split(".c")
		if len(ls) > 1:
			path = ls[0]
			father_path = os.path.split(path)
			return (father_path[0]+'\n')

        

    
