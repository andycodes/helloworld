#!/usr/bin/env python
# -*- coding: utf-8 -*-
from pyExcelerator import *

w = Workbook()
ws = w.add_sheet('sheet')

for i in range(6, 80):
    fnt = Font()
    #这里设置字体的高度,可以用来设置行的高度。可没有宽度
    fnt.height = i*5
    style = XFStyle()
    style.font = fnt
    ws.write(1, i, 'Test', style) #也可以这样来设置行高
    ws.write(1, i, 'Test')
    #这里设置列宽，主要通过设置Worksheet中的col来操作，其底层也是通过设置Column.width来达到改变其宽度的目的
    ws.col(i).width = 0x0d00 + i*50
    #这里设置行高，通过设置字体高度
    ws.row(1).set_style(style)
w.save('width.xls')
