# coding:utf-8
# -*- coding: utf-8 -*

import serial
import serial.tools.list_ports
import time

plist = list(serial.tools.list_ports.comports())
if len(plist) <= 0:
    print("没有发现物理端口!")
else:
    plist_0 = list(plist[0])
    serialName = plist_0[0]
    serialFd = serial.Serial(serialName, 115200, timeout=60)
    print("可用物理端口名>>>", serialFd.name)


# 打开串口
ser = serial.Serial("COM1", 115200,timeout=0.5)
def main():
    while True:
        # 获得接收缓冲区字符
        count = ser.inWaiting()
        if count != 0:
            # 读取内容并回显
            recv = ser.read(count)
            ser.write(recv)
        # 清空接收缓冲区
        ser.flushInput()
        # 必要的软件延时
        time.sleep(0.1)
    
if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        if ser != None:
            ser.close()