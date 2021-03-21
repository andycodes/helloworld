#! /usr/bin/python3

'write_and_read_file.py -- write and read text file.'

import makeTextFile
import readTextFile

if __name__ == '__main__':
    
    #wrie file
    filename = makeTextFile.write_file()
    
    #read file
    readTextFile.read_file(filename)
