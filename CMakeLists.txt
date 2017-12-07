cmake_minimum_required (VERSION 2.6)
project (fast-tcp-c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(benchmark test/benchmark.c)
add_executable(serializer src/ft_serializer.c src/ft_util.c test/serializer.c)
add_executable(tcp_client src/ft_tcp_socket.c src/ft_util.c test/tcp_client.c)