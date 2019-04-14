#! /usr/bin/python3


import string_split

if __name__ == '__main__':
    try:
        fsrc = open("Makefile",  'r')
        fobj = open("dir_list.txt",  'w')
    except IOError as err:
        print('file open error: {0}'.format(err))  
    else:
        for eachLine in fsrc:
            #print(eachLine)
            print (string_split.string_split(eachLine))
            if string_split.string_split(eachLine):
                fobj.writelines(string_split.string_split(eachLine))
        fsrc.close()
        fobj.close()
