# A simple Makefile for lib(libxxx.a)
# By Late Lee(http://www.latelee.org)

AR = ar
ARFLAGS = cr 

LIB = libthread.a

RM = -rm -rf

OBJS := util_thread.o 

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 

clean:
	$(RM) $(OBJS) $(LIB) *.bak *~

.PHONY: all clean