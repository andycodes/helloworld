


CFLAGS += -Isrc/cmsis/Device/ARM/ARMCM55/Include
CFLAGS += -Isrc/arch/$(ARCH)

CSRC += src/cmsis/Device/ARM/ARMCM55/Source/system_ARMCM55.c
CSRC += src/cmsis/Device/ARM/ARMCM55/Source/startup_ARMCM55.c
CSRC += src/platform/$(board)/omain.c
CSRC += src/platform/$(board)/overlay0.c
CSRC += src/platform/$(board)/overlay1.c
CSRC += src/platform/$(board)/cmsdk_uart.c 
CSRC += src/platform/$(board)/board.c