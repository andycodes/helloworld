ifneq ($(board),riscv)
include src/arch/arm/arch.mk
include src/platform/$(board)/board.mk
include src/cmsis/cmsis.mk
include src/rtos/rtos.mk
include src/components/components.mk
include src/libs/libs.mk
include src/testcase/$(board)/testcase_plat.mk
else
include src/arch/riscv/riscv.mk
include src/platform/$(board)/board.mk
endif
CFLAGS += 	-Isrc/include -Isrc/ -Isrc/libs\
			-Isrc/platform/$(board)