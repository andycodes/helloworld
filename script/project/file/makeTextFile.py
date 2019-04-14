#! /usr/bin/python3

'makeTextFile.py -- create text file'

import os

def write_file():
    "used to write a text file."
    
    ls = os.linesep
    #get filename
    fname = input("Please input filename:")

    while True:
    
        if os.path.exists(fname):
            print("Error: '%s' already exists" % fname)
            fname = input("Please input filename:")
        else:
            break
        
    #get file conent linesOnScreen
    all = []
    print("\nEnter lines ('.' to quit).\n")

    while True:
        entry = input('>')
        if entry == '.':
            break
        else:
            all.append(entry)
            
    try:
        fobj = open(fname,  'w')
    except IOError as err:
        print('file open error: {0}'.format(err))  
        
    fobj.writelines(['%s%s' % (x,  ls) for x in all])
    fobj.close()
    
    print('WRITE FILE DONE!')
    
    return fname
