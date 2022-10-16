OBJS = src/main.o \
		src/$(ARCH)/cpu.o \
		src/$(ARCH)/cpuport.o \
		src/$(ARCH)/context_gcc.o \
		src/platform/$(board)/cmsdk_uart.o \
		src/platform/$(board)/board.o

include src/platform/$(board)/platform.mk
include src/platform/$(board)/menu_config.mk
include src/cmsis/cmsis.mk
include src/components/components.mk
include src/libs/libs.mk
include src/utestcase/utestcase.mk