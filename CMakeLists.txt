cmake_minimum_required(VERSION 3.31.5)
project(Xadrez)
add_executable(Xadrez ../src/main.c ../src/interface.c ../src/input_handler.c ../src/error.c)
target_include_directories(Xadrez PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)