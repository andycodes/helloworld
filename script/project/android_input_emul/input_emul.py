import string
import operator
import os

if os.path.exists('./input_emul.bat'):
	os.remove('./input_emul.bat')

event_port = 2
fp=open("./getvalue", "r");
config_file=open("./input_emul.bat", "w");

for eachline in fp:
	line_list = eachline.rstrip().split(" ")
	if 1 != operator.eq('',line_list[0]):
		config_file.write('@adb shell sendevent  /dev/input/event%d  %s %d %d\n' %(event_port,line_list[0],int(line_list[1],16),int(line_list[2],16)))
fp.close()
config_file.close()

#os.remove('./getvalue')