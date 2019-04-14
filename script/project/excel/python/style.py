#!/usr/bin/env python
#-*- coding: utf8 -*-

from datetime import datetime
from pyExcelerator import *

num_data = ["123", "123.1232", "123.12", datetime.now(), datetime.now(), datetime.now()]
fmts =     ['general', '0.00', '#,##0.00', 'D-MMM-YY', 'h:mm:ss AM/PM','M/D/YY']

w = Workbook()
ws = w.add_sheet('sheet')

for i in range(len(num_data)):
    ws.write(i+1, 0, num_data[i])
    ws.write(i+1, 2, fmts[i])
    #写入样式
    style = XFStyle()
    style.num_format_str = fmts[i]
    style.font.name = 'Times New Roman'
    style.font.struck_out = True
    style.font.bold = True
    style.font.outline = True
    ws.write(i+1, 4, num_data[i], style)
    i+=1

w.save('mini.xls')
