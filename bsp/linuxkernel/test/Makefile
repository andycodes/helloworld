#!/usr/bin/make
#user-space app

CC=gcc

COMMON_FLAGS= -Wall -g #-I/usr/include/ -I/usr/src/linux/include

OBJ = test
SRC=$(OBJ).c




all:
	$(CC) $(COMMON_FLAGS) -o $(OBJ) $(SRC)
.PHONY:clean
clean:
	rm -fr $(OBJ) *.o  *.bak
	
