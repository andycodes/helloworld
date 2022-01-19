set(CPU "cortex-m33")
# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${CROSS_TARGET_TRIPLET}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_TARGET_TRIPLET}g++")
set(CMAKE_ASM_COMPILER "${CROSS_TARGET_TRIPLET}as")

# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
set(COMMON_COMPILE_FLAGS "-mcpu=${CPU} -nostdlib -nostartfiles -ffreestanding")
set(ASM_COMPILE_FLAGS "-mcpu=${CPU} ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ASM_COMPILE_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )


# 是否使用自己的 MathFunctions 库
option (CONFIG_MEMU
	   "Use provided CONFIG_MEMU" ON)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${DIR_TEST}/config.h.in"
  "${DIR_TEST}/config.h"
  )

# Fill in your source files here (duh).
set(SOURCES_TEST
    "${DIR_TEST}/test_menu_config.c"
)

# 是否加入 MathFunctions 库
if (CONFIG_MEMU)
  set (SOURCES_TEST ${SOURCES_TEST} "${DIR_TEST}/test_menu_config.c")
endif (CONFIG_MEMU)


include_directories(
    "${BASE_DIR}/src/include"
    "${BASE_DIR}/src/components"
    "${BASE_DIR}/src/cmsis"
    "${BASE_DIR}/src/cmsis/CMSIS/Core/Include"
    "${BASE_DIR}/src/cmsis/Device/ARM/ARMCM55/Include"
)




# 生成链接库
add_library (TestFunctions ${SOURCES_TEST})
