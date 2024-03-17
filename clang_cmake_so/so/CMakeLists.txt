CMAKE_MINIMUM_REQUIRED(VERSION 3.26) 

include(../toolchain.cmake)

PROJECT(LIB_ADD)

AUX_SOURCE_DIRECTORY(. SRC_LIST) 

add_library(add SHARED ${SRC_LIST})
set(LINK_SCRIPTS "-Tplat.lds")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set_target_properties(add PROPERTIES output_name "add")
