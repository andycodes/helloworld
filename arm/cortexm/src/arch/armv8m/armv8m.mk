
CFLAGS += -Isrc/arch 
CFLAGS += -Isrc/$(ARCH)

SSRC += src/arch/contex_switch.s

CSRC += src/arch/main.c \
	src/arch/$(ARCH)/dfx.c \
	src/arch/$(ARCH)/mpu.c \
	src/arch/$(ARCH)/arm_mpu.c \
	src/arch/$(ARCH)/dwt_cyccnt.c