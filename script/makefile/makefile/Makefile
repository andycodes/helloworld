#!/usr/bin/make

OBJ = ma

#第一行将得到一个完整路径名.
#第二行通过命令dirname 去掉 Makefile部分.
#第三行得到其父目录.
pes_parent_dir:=$(shell pwd)/$(lastword $(MAKEFILE_LIST))
pes_parent_dir:=$(shell dirname $(pes_parent_dir))
pes_parent_dir:=$(shell dirname $(pes_parent_dir))
pes_parent_dir:=$(subst script/makefile,,$(pes_parent_dir))

#全部重定向
#make >/project/log.txt 2>&1

CC=gcc

#-m32
#apt-get install gcc-multilib  

COMMON_FLAGS= -Wall -ggdb -m32

SRC:= main.c
SRC += fun.c

all:
	$(CC) $(COMMON_FLAGS) -o $(OBJ) $(SRC)
	@echo $(pes_parent_dir)
.PHONY:clean
clean:
	rm -fr $(OBJ) *.o  *.bak
	
