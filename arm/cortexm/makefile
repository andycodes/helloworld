
$(info "!!!!THE CUR BOARD is $(board)")

include src/platform/$(board)/board_config.mk

ifeq ($(CC),gcc)
include gcc.mk
else
include clang.mk
endif

