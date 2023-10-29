

CFLAGS += -Isrc/cmsis/Device/ARM/ARMCM33/Include

OBJS += src/cmsis/Device/ARM/ARMCM33/Source/system_ARMCM33.o 
#OBJS += src/platform/$(board)/system_SSE300MPS3.o
OBJS += src/cmsis/Device/ARM/ARMCM33/Source/startup_ARMCM33.o