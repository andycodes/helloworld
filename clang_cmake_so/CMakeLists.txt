CMAKE_MINIMUM_REQUIRED(VERSION 3.8) #cmake最低版本需求，不加入此行会受到警告信息
PROJECT(FRANK) #项目名称　　
AUX_SOURCE_DIRECTORY(. SRC_LIST) #把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
ADD_EXECUTABLE(frank ${SRC_LIST}) #生成应用程序 frank (在windows下会自动生成frank.exe)

add_library(utils SHARED ${SRC_LIST})

set(TOOLSCHAIN_PATH "/project/gcc/arm-gnu-toolchain-13.2.Rel/bin")
set(TOOLCHAIN_HOST "${TOOLSCHAIN_PATH}/arm-none-eabi-")
set(TOOLCHAIN_CC "${TOOLCHAIN_HOST}gcc")


#告诉cmake是进行交叉编译
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER ${TOOLCHAIN_CC})
set(CMAKE_OBJDUMP "${TOOLCHAIN_HOST}objdump")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m55") 

set(LINK_SCRIPTS "-Tplat.lds")

set_target_properties(utils PROPERTIES output_name "utils")



