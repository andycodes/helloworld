#CFLAGS += -Isrc/utestcase/

#CSRC +=	src/testcase/$(board)/testcase_usagefault.c
#CSRC +=	src/testcase/$(board)/testcase_dfx_fpu.c
#CSRC +=	src/testcase/$(board)/testcase_illegal_instruction_excution.c
#CSRC +=	src/testcase/$(board)/testcase_read_from_bad_address.c
#CSRC +=	src/testcase/$(board)/testcase_kalloc.c
CSRC +=	src/testcase/$(board)/testcase_c.c
#CSRC +=	src/testcase/$(board)/testcase_mve.c