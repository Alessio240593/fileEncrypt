cmake_minimum_required(VERSION 3.8)

project(fileEncrypt VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -Wpedantic ")
set(BIN "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})

add_executable(fileEncrypt src/fileEncrypt.cpp)