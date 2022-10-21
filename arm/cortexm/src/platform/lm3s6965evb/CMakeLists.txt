set(CPU "cortex-m3")
# Prepend the cross-compiler prefix to the used tools.
set(CROSS_TARGET_TRIPLET "/project/gcc/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-")
set(CMAKE_C_COMPILER "${CROSS_TARGET_TRIPLET}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_TARGET_TRIPLET}g++")
set(CMAKE_ASM_COMPILER "${CROSS_TARGET_TRIPLET}as")

# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
set(COMMON_COMPILE_FLAGS "-Wall -g -fno-builtin -gdwarf-2 -gstrict-dwarf -mthumb -nostartfiles  --specs=nosys.specs -std=c11 -O0  -mcpu=${CPU}")
set(ASM_COMPILE_FLAGS "-mcpu=${CPU} ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ASM_COMPILE_FLAGS}")
set(LINKER_SCRIPT "${DIR_PLAT}/plat.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -T ${LINKER_SCRIPT}")
MESSAGE("${LINKER_SCRIPT}")
# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )

# Fill in your source files here (duh).
set(DIR_LIB_SRCS
    "${BASE_DIR}/src/armv7m/int_vector.c"
    "${BASE_DIR}/src/armv7m/cm3.c"
    "${BASE_DIR}/src/armv7m/cm3_s.s"
    "${BASE_DIR}/src/armv7m/main.c"
    "${BASE_DIR}/src/platform/netduinoplus2/cmsdk_uart.c"
)

include_directories(
    "${BASE_DIR}/src/include"
    "${BASE_DIR}/src/armv7m"
    "${BASE_DIR}/src/libs"
    "${BASE_DIR}/src/rtos/evolution/include"
)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
#aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (PlatformFunctions ${DIR_LIB_SRCS})
