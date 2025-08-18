cmake_minimum_required(VERSION 4.0.2)
project(pulse64)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(pulse64 PUBLIC include)

add_executable(pulse64 src/main.c)
