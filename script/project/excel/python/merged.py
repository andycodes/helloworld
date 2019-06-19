#!/usr/bin/env python
#-*- coding: utf8 -*-

from pyExcelerator import *

#这里设置边框
borders = Borders()
borders.left = 1
borders.right = 1
borders.top = 1
borders.bottom = 1

#这里设置对齐方式
al = Alignment()
al.horz = Alignment.HORZ_CENTER
al.vert = Alignment.VERT_CENTER

style = XFStyle()
style.borders = borders
style.alignment = al

wb = Workbook()
ws = wb.add_sheet('sheet1')

#跨列合并
ws.write_merge(1, 1, 1, 5, u"这个合并(1,1)-(1,5)", style)
ws.write_merge(2, 2, 2, 3, u"这个合并(2,2)-(2,3)", style)
ws.write_merge(2, 2, 4, 5, u"这个合并(2,4)-(2,5)", style)
#跨行合并
ws.write_merge(2, 4, 1, 2, u"这个合并(2,1)-(4,1)", style)
ws.write_merge(3, 4, 2, 3, u"这个合并(3,2)-(4,2)", style)
ws.write_merge(3, 4, 3, 4, u"这个合并(3,3)-(4,3)", style)
ws.write_merge(3, 4, 4, 5, u"这个合并(3,4)-(4,4)", style)
ws.write_merge(3, 4, 5, 6, u"这个合并(3,5)-(4,5)", style)
#合并多行多列
ws.write_merge(1, 4, 6, 7, u"这个合并(1,6)-(4,7)", style)

wb.save('merged.xls')
