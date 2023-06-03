CSRC := src/main.c \
		src/$(ARCH)/cpu.c \
		src/$(ARCH)/dfx.c \
		src/platform/$(board)/cmsdk_uart.c \
		src/platform/$(board)/board.c \
		src/platform/$(board)/cpuidle.c \
		src/platform/$(board)/omain.c \
		src/platform/$(board)/overlay0.c \
		src/platform/$(board)/overlay1.c 

include src/platform/$(board)/board.mk
include src/cmsis/cmsis.mk
include src/components/components.mk
include src/libs/libs.mk
include src/utestcase/utestcase.mk

CFLAGS += 	-Isrc/include \
			-Isrc/$(ARCH)\
			-Isrc/libs\
			-Isrc/platform/$(board)