cmake_minimum_required(VERSION 2.8.3)
project (TermProject2020)
# Add header file include directories
include_directories(./inc ./src)

aux_source_directory(./src SRC_LIST)
# Add block directories
set(SRC ${SRC_LIST})
# Target
add_executable(build main.cpp ${SRC})