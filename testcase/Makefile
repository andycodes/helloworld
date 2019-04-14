# A simple Makefile for lib(libxxx.a)
# By Late Lee(http://www.latelee.org)

AR = ar
ARFLAGS = cr

LIB = libtestcasemain.a

RM = -rm -rf

OBJS := testcase_main.o

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	$(RM) $(OBJS) $(LIB) *.bak *~

.PHONY: all clean