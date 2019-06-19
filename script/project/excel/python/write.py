#!/usr/bin/env python
# -*- coding: utf-8 -*-

from pyExcelerator import *

w = Workbook()
ws = w.add_sheet('sheet')
#第一行作为header：注意是(0,0)作为第一行第一列
ws.write(0,0,u"姓名")
ws.write(0,1,u"年龄")
ws.write(0,2,u"班级")

data = [["aaaa",9,u"三年二班"], ["bbbb",9,u"三年二班"], ["cccc",9,u"三年二班"]]

#这里一般的处理是对数据循环，对应到sheet中的行列，写入数据
for i in range(len(data)):
    for j in range(len(data[i])):
        ws.write(i+1,j,data[i][j])
    i+=1

w.save('mini.xls')
