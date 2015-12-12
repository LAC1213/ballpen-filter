cmake_minimum_required(VERSION 2.6)
project(ballpenfilter)

add_executable(ballpenfilter main.cpp)

install(TARGETS ballpenfilter RUNTIME DESTINATION bin)
