
CMAKE_MINIMUM_REQUIRED(VERSION 3.26) 

set(CMAKE_C_COMPILER_FORCED ON)
set(CMAKE_CXX_COMPILER_FORCED ON)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

# where is the target environment 
SET(TOOLCHAIN_DIR "/project/compiler/llvm_clang/clang")
# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_DIR}/bin/)
SET(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/clang")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/clang++")
SET (CMAKE_AR      "${TOOLCHAIN_DIR}/bin/llvm-ar")
SET (CMAKE_LINKER  "${TOOLCHAIN_DIR}/bin/llvm-ld")
SET (CMAKE_NM      "${TOOLCHAIN_DIR}/bin/llvm-nm")
SET (CMAKE_OBJDUMP "${TOOLCHAIN_DIR}/bin/llvm-objdump")
SET (CMAKE_RANLIB  "${TOOLCHAIN_DIR}/bin/llvm-ranlib")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a710") 

message("CMAKE_C_COMPILER is: ${CMAKE_C_COMPILER}")
message("CMAKE_C_FLAGS is: ${CMAKE_C_FLAGS}")

