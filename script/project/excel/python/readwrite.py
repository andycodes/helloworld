#! /usr/bin/python
#-*- coding: utf8 -*-

import xlrd
import xlwt
from datetime import datetime
 
def testXlrd(filename):
    book=xlrd.open_workbook(filename)
    sh=book.sheet_by_index(0)
    print "Worksheet name(s): ",book.sheet_names()[0]
    print 'book.nsheets',book.nsheets
    print 'sh.name:',sh.name,'sh.nrows:',sh.nrows,'sh.ncols:',sh.ncols
    print 'A1:',sh.cell_value(rowx=0,colx=1)
    #如果A3的内容为中文
    print 'A2:',sh.cell_value(0,2).encode('gb2312')
 
def testXlwt(filename):
    book=xlwt.Workbook()
    sheet1=book.add_sheet('hello')
    book.add_sheet('word')
    sheet1.write(0,0,'hello')
    sheet1.write(0,1,'world')
    row1 = sheet1.row(1)
    row1.write(0,'A2')
    row1.write(1,'B2')
     
    sheet1.col(0).width = 10000
     
    sheet2 = book.get_sheet(1)
    sheet2.row(0).write(0,'Sheet 2 A1')
    sheet2.row(0).write(1,'Sheet 2 B1')
    sheet2.flush_row_data()
     
    sheet2.write(1,0,'Sheet 2 A3')
    sheet2.col(0).width = 5000
    sheet2.col(0).hidden = True
     
    book.save(filename)
 
if __name__=='__main__':
    testXlrd('read.xls')
    testXlwt('helloWord.xls')
