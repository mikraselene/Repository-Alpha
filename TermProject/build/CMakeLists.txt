# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project，可以任意指定
project(Project)

# 扫描 src/ 下的所有源文件，并将文件名存入 DIR_SRCS 中
aux_source_directory(src/ DIR_SRCS)

# Add all the source files needed to build the executable
# ${DIR_SRCS}:所有源文件
# main：将生成的可执行文件名
add_executable(main ${DIR_SRCS})
