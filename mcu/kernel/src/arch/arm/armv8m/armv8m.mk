
ARM_PATH ?= src/arch/arm/

CFLAGS += -I$(ARM_PATH)
CFLAGS += -I$(ARM_PATH)$(ARCH)

SSRC += $(ARM_PATH)/contex_switch.s
CSRC += $(ARM_PATH)/main.c \
	$(ARM_PATH)/$(ARCH)/dfx.c \
	$(ARM_PATH)/$(ARCH)/mpu.c \
	$(ARM_PATH)/$(ARCH)/arm_mpu.c \
	$(ARM_PATH)/$(ARCH)/dwt_cyccnt.c