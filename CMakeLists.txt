cmake_minimum_required(VERSION 3.27.0)
project(pulse64)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(log STATIC lib/logger/src/log.c)
target_compile_options(log PRIVATE -D LOG_USE_COLOR)

add_executable(pulse64 src/main.c src/pangea.c src/bus.c src/pulse.c src/registers.c src/ram.c src/alu.c src/isa_gen.c)
target_compile_options(pulse64 PRIVATE -g)
#-Wall -Wextra -Werror)

target_include_directories(pulse64 PUBLIC include)

target_link_libraries(pulse64 PRIVATE log)
target_include_directories(pulse64 PUBLIC lib/logger/src)
