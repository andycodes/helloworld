ifeq ($(board),riscv32)
include src/arch/riscv32/riscv.mk
include src/platform/$(board)/board.mk
else ifeq ($(board),riscv64)
include src/arch/riscv64/riscv.mk
include src/platform/$(board)/board.mk
else
include src/arch/arm/arch.mk
include src/platform/$(board)/board.mk
include src/cmsis/cmsis.mk
include src/rtos/rtos.mk
include src/components/components.mk
include src/libs/libs.mk
include src/testcase/$(board)/testcase_plat.mk
endif


CFLAGS += 	-Isrc/include -Isrc/ -Isrc/libs\
			-Isrc/platform/$(board)