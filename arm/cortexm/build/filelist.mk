CSRC := src/main.c \
		src/platform/$(board)/cmsdk_uart.c \
		src/platform/$(board)/board.c

SSRC := src/contex_switch.s

include src/platform/$(board)/board.mk
include src/cmsis/cmsis.mk
include src/rtos/evolution/evolution.mk
include src/components/components.mk
include src/libs/libs.mk
include src/testcase/$(board)/testcase_plat.mk

CFLAGS += 	-Isrc/include -Isrc/ -Isrc/libs\
			-Isrc/platform/$(board)