
MAIN_PATH=/project/helloworld/clang_cmake_so/
COMPILER_PATH=/project/compiler/llvm_clang/clang/bin/
DUMPTOOL=${COMPILER_PATH}llvm-objdump
READELF=${COMPILER_PATH}llvm-readelf

BIN_PATH=${MAIN_PATH}bin/
OBJ=${BIN_PATH}frank
file ${OBJ}
${DUMPTOOL} -D  --disassemble-zeroes ${OBJ} >${BIN_PATH}frank.dump
${READELF} --all ${OBJ} >${BIN_PATH}frank.readelf

LIB_PATH=${MAIN_PATH}lib/
LIB=${LIB_PATH}libadd.a
file ${LIB}
${DUMPTOOL} -D  --disassemble-zeroes ${LIB} >${LIB_PATH}add.dump
${READELF} --all ${LIB} >${LIB_PATH}add.readelf