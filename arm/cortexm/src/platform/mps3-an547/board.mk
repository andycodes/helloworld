
CFLAGS += -Isrc/cmsis/Device/ARM/ARMCM55/Include

CSRC += src/cmsis/Device/ARM/ARMCM55/Source/system_ARMCM55.c
CSRC += src/cmsis/Device/ARM/ARMCM55/Source/startup_ARMCM55.c
CSRC += src/$(ARCH)/dfx.c
CSRC += src/platform/$(board)/omain.c
CSRC += src/platform/$(board)/overlay0.c
CSRC += src/platform/$(board)/overlay1.c