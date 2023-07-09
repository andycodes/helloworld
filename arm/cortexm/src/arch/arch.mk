
CFLAGS += -Isrc/arch 
CFLAGS += -Isrc/$(ARCH)
ifeq ($(CPU_TYPE),cortex-m3)
CFLAGS += -Isrc/cmsis/Device/ARM/ARMCM3/Include
endif

SSRC += src/arch/contex_switch.s

CSRC += src/arch/main.c 


CSRC += src/arch/$(ARCH)/dfx.c \
	src/arch/$(ARCH)/mpu.c \
	src/arch/$(ARCH)/arm_mpu.c