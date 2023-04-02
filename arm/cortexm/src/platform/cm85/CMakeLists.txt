set(CPU "cortex-m85")
# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${CROSS_TARGET_TRIPLET}gcc")
set(CMAKE_ASM_COMPILER "${CROSS_TARGET_TRIPLET}as")

# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
set(COMMON_COMPILE_FLAGS "-mcpu=${CPU} -nostdlib -nostartfiles -ffreestanding")
set(ASM_COMPILE_FLAGS "-mcpu=${CPU} ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ASM_COMPILE_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )

# Fill in your source files here (duh).
set(SOURCES
    "${BASE_DIR}/src/armv8m/cpuport.c"
    "${BASE_DIR}/src/armv8m/context_gcc.S"
    "${BASE_DIR}/src/armv8m/syscall_gcc.S"
    "${BASE_DIR}/src/armv8m/backtrace.c"
    "${BASE_DIR}/src/platform/mps3-an547/cmsdk_uart.c"
    "${BASE_DIR}/src/platform/mps3-an547/board.c"
    "${BASE_DIR}/src/cmsis/Device/ARM/ARMCM55/Source/system_ARMCM55.c"
    "${BASE_DIR}/src/cmsis/Device/ARM/ARMCM55/Source/startup_ARMCM55.c"
    "${BASE_DIR}/src/libs/printk.c"
    "${BASE_DIR}/src/components/module.c"
)

include_directories(
    "${BASE_DIR}/src/include"
    "${BASE_DIR}/src/components"
    "${BASE_DIR}/src/cmsis"
    "${BASE_DIR}/src/cmsis/CMSIS/Core/Include"
    "${BASE_DIR}/src/cmsis/Device/ARM/ARMCM55/Include"
)




# 生成链接库
add_library (PlatformFunctions ${SOURCES})
