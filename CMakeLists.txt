cmake_minimum_required(VERSION 3.7)

project(c_util)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")


include_directories(include)




add_library(c_util STATIC read_write_file.c  encoding.c print.c)

#add_executable(test_c_util    main.cpp print.c)

#target_link_libraries(test_c_util c_util gtest  gtest_main pthread)


