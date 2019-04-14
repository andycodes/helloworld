#! /usr/bin/python
#-*- coding: utf8 -*-

#读取read.xls中的某些信息进行处理后写入mini.xls文件中。
import xlrd
from pyExcelerator import *  

w = Workbook()  
ws = w.add_sheet('Sheet1')  

fname = "read.xls"
bk = xlrd.open_workbook(fname)
shxrange = range(bk.nsheets)
try:
    sh = bk.sheet_by_name("Sheet1")
except:
    print "no sheet in %s named Sheet1" % fname

nrows = sh.nrows
ncols = sh.ncols
print "nrows %d, ncols %d" % (nrows,ncols)

cell_value = sh.cell_value(1,1)
print cell_value

row_list = []
mydata = []
for i in range(1,nrows):
    row_data = sh.row_values(i)
    pkgdatas = row_data[3].split(',')
    #pkgdatas.split(',')
    #获取每个包的前两个字段
    for pkgdata in pkgdatas:
        pkgdata = '.'.join((pkgdata.split('.'))[:2])
        mydata.append(pkgdata)
    #将列表排序
    mydata = list(set(mydata))
    print mydata
    #将列表转化为字符串
    mydata = ','.join(mydata)
    #写入数据到每行的第一列
    ws.write(i,0,mydata)
    mydata = []
    row_list.append(row_data[3])
#print row_list

w.save('mini.xls')

