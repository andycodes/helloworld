import os
import re
import shutil

path=r'/project/atf/arm-trusted-firmware-arm_cca_v0.1/'
pattern=r"aarch32"

for i in os.walk(path):
    #print(i)#i is a tuple
    #print(i[0])# i[0] is full path
    m = re.search(pattern, i[0])
    #print(m)
    if m != None:
        #print(i[0])
        if os.path.exists(i[0]) :
            shutil.rmtree(i[0])#rm dirs