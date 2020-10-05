project(client)

cmake_minimum_required(VERSION 3.10)

add_executable(client main.cpp)
if(NOT WIN32)
target_link_libraries(client pthread )
endif()
target_link_libraries(client TVLEncoder)