#! /usr/bin/python3

'readTextFile.py -- read and display text file.'

def read_file(filename):
    'used to read a text file.'
    
    try:
        fobj = open(filename,  'r')
    except IOError as err:
        print('file open error: {0}'.format(err))  
    else:
        for eachLine in fobj:
            print(eachLine)
        fobj.close()
        

    
