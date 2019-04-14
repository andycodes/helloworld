#! /usr/bin/python
#-*- coding: utf8 -*-

from pyExcelerator import *
import random

w = Workbook()
#w = Workbook(encoding='utf-8') 支持中文
ws = w.add_sheet('sheet')
ws.frmla_opts=RecalcAlways
#ws.show_formulas = True

#写入一些数据
for i in range(30):
    for j in range(20):
        ws.write(i, j, random.randint(1, 100))
        
#这里写公式        
ws.write(30, 0, Formula("SUM(A1:A30)"))
ws.write(30, 2, Formula("SUM(B1:B30)*SUM(C1:C30)"))
w.save('random.xls')
