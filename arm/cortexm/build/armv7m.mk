
CSRC := src/$(ARCH)/cm3.c \
		src/$(ARCH)/main.c \
		src/platform/$(board)/cmsdk_uart.c

SSRC := src/$(ARCH)/cm3_s.s

include src/platform/$(board)/board.mk
include src/rtos/evolution/evolution.mk
include src/libs/libs.mk
include src/cmsis/cmsis.mk
include src/testcase/$(board)/testcase_plat.mk

CFLAGS += 	-Isrc/include \
			-Isrc/$(ARCH)\
			-Isrc/libs\
			-Isrc/platform/$(board)