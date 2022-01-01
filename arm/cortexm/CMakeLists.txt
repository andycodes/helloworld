cmake_minimum_required(VERSION 2.8.12)

project(felix-Template C CXX ASM)
set(TARGET felix)

# General settings {{{

set(CROSS_TARGET_TRIPLET "/project/gcc/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-")
set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PLAT_PATH "${BASE_DIR}/src/platform/${CUR_PLAT}")
MESSAGE("${PLAT_PATH}")
add_subdirectory("${PLAT_PATH}")
set(LINKER_SCRIPT "${PLAT_PATH}/plat.ld")

# Fill in the config for openocd to use.
# E.g. for an felixF4-Discovery dev-board:
#set(OPENOCD_CFG "/usr/share/openocd/scripts/board/felixf4discovery.cfg")

# Definitions {{{

# We're not using add_definitions() here, since this would break the calls to the assembler.
# Some examples:
#set(DEFINITIONS "${DEFINITIONS} -DfelixF40_41xxx")
set(DEFINITIONS "${DEFINITIONS} -DUSE_STDPERIPH_DRIVER")

#}}}

# Compiler settings {{{

# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${CROSS_TARGET_TRIPLET}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_TARGET_TRIPLET}g++")
set(CMAKE_ASM_COMPILER "${CROSS_TARGET_TRIPLET}as")

# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
set(COMMON_COMPILE_FLAGS "-Wall -g -fno-builtin -gdwarf-2 -gstrict-dwarf -mthumb -nostartfiles  --specs=nosys.specs -std=c11 -O0 -mcpu=${CPU}")
set(ASM_COMPILE_FLAGS "-mcpu=${CPU} -Wall -g -fno-builtin -gdwarf-2 -gstrict-dwarf -mthumb -nostartfiles  --specs=nosys.specs -std=c11 -O0")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ASM_COMPILE_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -T ${LINKER_SCRIPT}")

# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )

#}}}

# Source files  {{{
    set(SOURCES
    "${BASE_DIR}/src/stub.c"
)

#}}}

# Header files  {{{

# Fill in your header files here. Not actually required for compiling, but
# some IDEs (e.g. QtCreator) won't list the header files in the project tree
# if they are not explicitly listed.
#set(HEADERS
#    "${BASE_DIR}include/main.h"
#)

#}}}

# Include dirs  {{{

# Fill in the directories of your header files here.
include_directories(
    "${BASE_DIR}/src/include"
    "${BASE_DIR}/src/components"
    "${BASE_DIR}/src/cmsis"
    "${BASE_DIR}/src/cmsis/CMSIS/Core/Include"
)

#}}}

# Build the image {{{

# Compile the sources to an .elf
add_executable(${TARGET}.elf ${SOURCES} ${HEADERS})

# 添加链接库
target_link_libraries(${TARGET}.elf MathFunctions)


# Create a binary from the elf
add_custom_command(TARGET ${TARGET}.elf POST_BUILD
    COMMAND ${CROSS_TARGET_TRIPLET}objcopy -Oihex ${TARGET}.elf ${TARGET}.hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

#}}}

# Targets for debugging/flashing {{{

# Start debugging with GDB (openocd needs to run in background)
add_custom_target(gdb
    COMMAND ${CROSS_TARGET_TRIPLET}gdb -x ${BASE_DIR}/gdb/gdb.cfg ${TARGET}.elf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${TARGET}.elf
)

# Flash the previously built firmware to the target (openocd needs to run in background)
add_custom_target(flash
    COMMAND ${CROSS_TARGET_TRIPLET}gdb --batch -x ${BASE_DIR}/gdb/gdb.cfg -ex 'monitor program ${TARGET}.hex verify reset'
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${TARGET}.elf
)

# Flash the previously built firmware to the target (openocd needs to run in background)
add_custom_target(openocd
    COMMAND openocd -f ${OPENOCD_CFG}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${TARGET}.elf
)

#}}}

# vim: set ts=4 sw=4 sts=4 et smarttab :
