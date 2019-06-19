#! /usr/bin/python
#-*- coding: utf8 -*-

#read EXECL
import xlrd

def get_attribute_by_
    

fname = "hi6xxx_cpu_info.xls"
bk = xlrd.open_workbook(fname)
shxrange = range(bk.nsheets)
try:
    sh = bk.sheet_by_name("Sheet1")
except:
    print "no sheet in %s named Sheet1" % fname

this_sh = bk.sheet_by_name(u'Sheet1')

nrows = sh.nrows
ncols = sh.ncols
print "nrows %d, ncols %d" % (nrows,ncols)
print "cell %s" % (sh.cell(8,0).value)


#生成DTSI
cpu_id = 0
cpu_max = 4
f = open("fansaihua.dtsi","w")
for i in range(cpu_max):
    f.write("   cpu@%d {\n" %cpu_id)
    f.write("       device_type = \"cpu\";\n")
    f.write("       compatible = \"arm,cortex-a15\";\n")
    f.write("       reg = <%d>;\n" %cpu_id)
    f.write("   };\n")
    cpu_id = cpu_id+1
f.close

sss = "1/2/3/4/5/6"
aaa = sss.split("/")
print aaa
print aaa[0]

s = "a#b#c"
ls = s.split("#")
print ls

