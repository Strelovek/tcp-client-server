project(tcp-client-server)

cmake_minimum_required(VERSION 3.10)

add_library(TVLEncoder STATIC libTLV/TVLEncoder.cpp libTLV/TVLEncoder.h libTLV/Socket.cpp libTLV/Socket.h)

add_subdirectory(tests)
add_subdirectory(server)
add_subdirectory(client)
