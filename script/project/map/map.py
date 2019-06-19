# -*- coding:UTF-8 -*-
import Image
import httplib
from math import *


class MapImage():
    """将经纬度坐标转换为 Google Map 的 URL，并且可以把图片下载下来，合成一幅大图。
    下载后的图片依次命名为 1.jpg 2.jpg ...，最后合并的大图命名为 map.jpg
    合并成大图的话需要 PIL 库。
    """

    def __init__(self, Zoom = 10, nX = 3, nY = 3):
        """nX 和 nY 的设置就会由3x3个图生成大图。
        Zoom 是放大级别(1 - 20)，某些地区的最大级别不到 20 或更小。
        """
        self.w = 0
        self.h = 0
        self.nx = nX
        self.ny = nY
        self.zoom = Zoom
        self.outputImg = "map.jpg"
        self.imgFiles = []

    def SetTiles(self, nX, nY):
        self.nx = nX
        self.ny = nY

    def SetZoom(self, Zoom):
        self.zoom = Zoom
    
    def GetAddress(self, lon, lat):
        "转换为 Mercator 投影"
        
        PI = 3.1415926535897
        digits = 20
        x = (180.0 + lon) / 360.0

        y = -lat * PI / 180.0
        y = 0.5 * log( (1 + sin(y)) / (1 - sin(y)) )
        y *= 1.0 / (2 * PI)
        y += 0.5

        quad = "t"
        lookup = "qrts"

        while digits > 0:
            x -= floor(x)
            y -= floor(y)
            quad = quad + lookup[(x >= 0.5 and 1 or 0) + (y >= 0.5 and 2 or 0)]
            x *= 2
            y *= 2
            digits -= 1
        
        return quad


    def GetNextTileX(self, addr, forward):
        "获得下一个横图块"
        
        if addr == '':
            return addr
            
        parent = addr[:len(addr) - 1]
        last = addr[len(addr) - 1]
        
        if last == 'q':
            last = 'r'
            if (not forward):
                    parent = self.GetNextTileX(parent, forward)
        elif last == 'r':
            last = 'q'
            if (forward):
                    parent = self.GetNextTileX(parent, forward)
        elif last == 's':
            last = 't'
            if (forward):
                    parent = self.GetNextTileX(parent, forward)
        elif last == 't':
            last = 's'
            if (not forward):
                    parent = self.GetNextTileX(parent, forward)
                
        return parent + last


    def GetNextTileY(self, addr, forward):
        "获得下一个纵图块"
        
        if addr == '':
            return addr
            
        parent = addr[:len(addr) - 1]
        last = addr[len(addr) - 1]
        
        if last == 'q':
            last = 't'
            if (not forward):
                    parent = self.GetNextTileY(parent, forward)
        elif last == 'r':
            last = 's'
            if (not forward):
                    parent = self.GetNextTileY(parent, forward)
        elif last == 's':
            last = 'r'
            if (forward):
                    parent = self.GetNextTileY(parent, forward)
        elif last == 't':
            last = 'q'
            if (forward):
                    parent = self.GetNextTileY(parent, forward)
                
        return parent + last


    def GetURL(self, lat, lon):
        """转换经纬度为 URL。
        输入经度、纬度"""
        
        address = []
        addr = self.GetAddress(lon, lat)
        cursor = addr[:self.zoom]
        cursor = self.GetNextTileX(cursor,0)
        cursor = self.GetNextTileY(cursor,0)
        
        for x in range(0, self.nx):
            c2 = cursor
            cursor = self.GetNextTileX(cursor,1)
            for y in range(0, self.ny):
                address.append("/kh?v=3&t=" + c2)
                c2 = self.GetNextTileY(c2,1)
        
        self.imgList = address
        return tuple(address)


    def DownloadImg(self):
        "下载列表中的图片"
        
        files = []
        for imgurl in self.imgList:
            con1 = httplib.HTTPConnection("kh2.google.com")
            con1.request("GET", imgurl)
            r1 = con1.getresponse()
            try:
                if r1.status == 200:
                    data = r1.read()

                    files.append("%s.jpg" % (self.imgList.index(imgurl)))
                    f = open("%s.jpg" % (self.imgList.index(imgurl)),"wb")
                    f.write(data)
                    f.close()
                    print ("%s.jpg OK..." % (self.imgList.index(imgurl)))
                elif r1.status == 404:
                    print ("%s.jpg no found" % (self.imgList.index(imgurl)))
                else:
                    print ("%s.jpg unkown error" % (self.imgList.index(imgurl)))
                
            except:
                print ("img: %s download error" % (self.imgList.index(imgurl)))

        self.imgFiles = tuple(files)
        return self.imgFiles
                

    def Merge(self):
        "合并图片"

        self.w = self.nx * 256
        self.h = self.ny * 256

        img = Image.new("RGB", (self.w, self.h))
        stepX = 0
        stepY = 0

        for i in self.imgFiles:
            im = Image.open(i)
            img.paste(im, (0 + stepX, 0 + stepY, 256 + stepX, 256 + stepY))
            stepY += 256
            if stepY >= self.h:
                stepX += 256
                stepY = 0
        img.save(self.outputImg)
        img.show()
        return self.outputImg



gmap = MapImage(20, 4, 4)
print (" ".join(gmap.GetURL(40.703610, -73.931630)))#这是New York的某个地方
print (" ".join(gmap.DownloadImg()))
print (gmap.Merge())
