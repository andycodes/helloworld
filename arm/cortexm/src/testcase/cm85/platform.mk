
CFLAGS += -Isrc/testcase/$(board)

OBJS +=	\
		src/testcase/$(board)/test_mpu.o \
		src/testcase/$(board)/test_systick.o \
		src/testcase/$(board)/test_menu_config.o \
		src/testcase/$(board)/test_os.o \
		src/testcase/$(board)/test_svc.o \
		src/testcase/$(board)/test_cpu.o \
		src/testcase/$(board)/test_exec.o