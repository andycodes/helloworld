CFLAGS += -Isrc/utest/

OBJS +=	src/utest/utest.o src/utest/utest_entry.o \
		src/utest/$(board)/test.o