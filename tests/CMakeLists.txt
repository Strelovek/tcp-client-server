project(test)

cmake_minimum_required(VERSION 3.10)

add_subdirectory(googletest)
add_library(TVLEncoder STATIC ../libTLV/TVLEncoder.cpp ../libTLV/TVLEncoder.h)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(runtests tests.cpp)

target_link_libraries(runtests gtest gtest_main)
target_link_libraries(runtests TVLEncoder)
