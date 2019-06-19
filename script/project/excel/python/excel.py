#! /usr/bin/python
#encoding:utf8
import xlrd
import xlwt

class OperExcel():
    #读取Excel表
    def rExcel(self,inEfile,outfile):
        rfile = xlrd.open_workbook(inEfile)
        #创建索引顺序获取一个工作表
        table = rfile.sheet_by_index(0)
        #其他方式
        #table = rfile.sheets()[0]
        #table = rfile.sheet_by_name(u'Sheet1')
    
        #获取整行，整列的值
        table.row_values(0)
        table.col_values(0)
    
        #获取行数和列数
        nrows = table.nrows - 1
        ncols = table.ncols
    
        #循环获取列表的数据
        #for i in range(nrows):
        # print table.row_values(i)
        wfile = open(outfile,'w')
        #获取第一列中的所有值
        for i in range(nrows):
        #table.cell(i,0).value获取某一单元格的值
            wfile.write(table.cell(i,0).value.encode('utf8') + '\n')
        wfile.close()
    
    #将数据写入Excel表
    def wExcel(self,infile,outEfile):
        rfile = open(infile,'r')
        buf = rfile.read().split('\n')
        rfile.close()
    
    w = xlwt.Workbook()
    sheet = w.add_sheet('sheet1')
    for i in range(len(buf)):
        print buf[i]
        sheet.write(i,0,buf[i].decode('utf8'))
    w.save(outEfile)
    
    if __name__ == '__main__':
        t = OperExcel()
    t.rExcel('test.xls','test')
    t.wExcel('test','1.xls')

