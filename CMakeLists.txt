cmake_minimum_required (VERSION 2.6)
project (fast-tcp-c)

# Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# Set compiler version
set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES "src/*.c")

# Dependencies
find_package(Threads)

# Library
add_library(fasttcp SHARED ${SOURCES})

# Tests
add_executable(benchmark test/benchmark.c)
add_executable(serializer src/ft_serializer.c src/ft_util.c test/serializer.c)
add_executable(reader src/ft_reader.c src/ft_util.c test/reader.c)
add_executable(tcp_socket src/ft_tcp_socket.c src/ft_util.c test/tcp_socket.c)
add_executable(socket src/ft_tcp_socket.c src/ft_socket.c src/ft_reader.c src/ft_serializer.c src/ft_util.c test/socket.c)
add_executable(util src/ft_util.c test/util.c)

target_link_libraries(socket ${CMAKE_THREAD_LIBS_INIT})
