#! /usr/bin/python
#-*- coding: utf8 -*-
import xlrd
import matplotlib.pyplot as plt

fname = "matplotlib.xls"
bk = xlrd.open_workbook(fname)
shxrange = range(bk.nsheets)
try:
    sh = bk.sheet_by_name("Sheet1")
except:
    print ("no sheet in %s named Sheet1" % fname)
#获取行数
nrows = sh.nrows
#获取列数
ncols = sh.ncols
print ("nrows %d, ncols %d" % (nrows,ncols))
#获取第一行第一列数据 
cell_value = sh.cell_value(1,1)
print (cell_value)

print("column data\n")
column_list = []
#获取各column数据
for i in range(0,ncols):
    ncol_data = sh.col_values(i)
    column_list.append(ncol_data)

#print column_list[0:ncols]
print (column_list[0])
print("\n")
print (column_list[1])

# scatter ops
#from pylab import *

X = column_list[0]
Y = column_list[1]

plt.figure('TEST')
plt.title('FANSAIHUA')
plt.grid(True)
plt.plot(X,Y,'-r')
plt.legend('fan','best')
plt.xlabel("x axis")
plt.ylabel("y axis")
#plt.sca(plt.subplot(410))
#plt.legend()
plt.show()
