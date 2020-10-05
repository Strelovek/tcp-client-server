project(server)

cmake_minimum_required(VERSION 3.10)

add_executable(server main.cpp Server.h Server.cpp )

if(NOT WIN32)
target_link_libraries(server pthread )
endif()
target_link_libraries(server TVLEncoder)
