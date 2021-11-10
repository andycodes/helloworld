cmake_minimum_required(VERSION 3.10)

# set the project name
project(HelloWorld)

SET(SRC_LIST main.c)

MESSAGE(STATUS “This is BINARY dir” ${HELLO_BINARY_DIR})

# add the executable
#add_executable(HelloWorld main.c)
ADD_EXECUTABLE(hello ${SRC_LIST})

#
#out-of-source build
#mkdir build
#cd build
#cmake ..
#

