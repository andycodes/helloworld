
CFLAGS += -Isrc/cmsis/Device/ARM/ARMCM3/Include

CSRC += src/cmsis/Device/ARM/ARMCM3/Source/system_ARMCM3.c 
CSRC += src/cmsis/Device/ARM/ARMCM3/Source/startup_ARMCM3.c
CSRC += src/platform/$(board)/dfx.c