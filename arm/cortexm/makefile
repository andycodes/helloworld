
$(info "!!!!THE CUR BOARD is $(board)")

include src/platform/$(board)/board_config.mk

ifeq ($(CC),gcc)
include build/gcc.mk
else
include build/clang.mk
endif
