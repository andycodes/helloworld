#! /usr/bin/python3

import string

import make_new_register_info_dict

g_register_info_dict = {}

def build_new_register_info_dict(filename):
	'used to read a text file.'

	try:
		fobj = open(filename,  'r')
	except IOError as err:
		print('file open error: {0}'.format(err))
	else:
		for eachLine in fobj:
			#print(eachLine)
			register_addr = eachLine.split(' ')
			index = 0
			new_register_addr = 0
			for x in register_addr:
				if index == 1:
					num =int(x,16)
					num = num&0x000fffff|0xe1300000
					new_register_addr = '0x%x'%num
				index = index + 1
			g_register_info_dict[register_addr[0]] = new_register_addr
			#print (g_register_info_dict)
		fobj.close()
		
	return g_register_info_dict
        

    
