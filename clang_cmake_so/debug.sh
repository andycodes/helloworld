
OUT_PATH=/project/helloworld/clang_cmake_so/bin/
OBJ=${OUT_PATH}frank
COMPILER_PATH=/project/compiler/llvm_clang/clang/bin/
DUMPTOOL=${COMPILER_PATH}llvm-objdump
READELF=${COMPILER_PATH}llvm-readelf

file ${OBJ}
${DUMPTOOL} -D  --disassemble-zeroes ${OBJ} >${OUT_PATH}frank.dump
${READELF} --all ${OBJ} >${OUT_PATH}frank.readelf