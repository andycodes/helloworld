
OBJS := src/$(ARCH)/cm3.o \
		src/$(ARCH)/cm3_s.o \
		src/$(ARCH)/main.o \
		src/platform/$(board)/cmsdk_uart.o 

include src/platform/$(board)/platform.mk
include src/rtos/evolution/evolution.mk
include src/libs/libs.mk
include src/cmsis/cmsis.mk