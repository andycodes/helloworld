CSRC := src/main.c \
		src/$(ARCH)/cpu.c \
		src/platform/$(board)/cmsdk_uart.c \
		src/platform/$(board)/board.c 

include src/platform/$(board)/board.mk
include src/cmsis/cmsis.mk
include src/components/components.mk
include src/libs/libs.mk
include src/testcase/$(board)/testcase_plat.mk

CFLAGS += 	-Isrc/include \
			-Isrc/$(ARCH)\
			-Isrc/libs\
			-Isrc/platform/$(board)