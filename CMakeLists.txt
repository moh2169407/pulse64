cmake_minimum_required(VERSION 3.27.0)
project(pulse64)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

# Path to the Python interpreter inside your venv
set(PYTHON_VENV ${CMAKE_SOURCE_DIR}/script/venv/bin/python3)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/src/isa_gen.c
    COMMAND ${PYTHON_VENV} ${CMAKE_SOURCE_DIR}/script/generate_isa_files.py
    DEPENDS ${CMAKE_SOURCE_DIR}/isa.yaml ${CMAKE_SOURCE_DIR}/script/generate_isa_files.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/script
    COMMENT "Generating isa_gen.c from isa.yaml"
)

add_library(log STATIC lib/logger/src/log.c)
target_compile_options(log PRIVATE -D LOG_USE_COLOR)


add_executable(pulse64 src/main.c src/pangea.c src/bus.c src/pulse.c src/registers.c src/ram.c src/alu.c src/isa_gen.c)
target_compile_options(pulse64 PRIVATE -g )#-Wall -Wextra -Werror)
#-Wall -Wextra -Werror)

target_include_directories(pulse64 PUBLIC include)

target_link_libraries(pulse64 PRIVATE log)
target_include_directories(pulse64 PUBLIC lib/logger/src)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/tests/test_alu_gen.c
    COMMAND ${PYTHON_VENV} ${CMAKE_SOURCE_DIR}/script/generate_alu_test_files.py
    DEPENDS ${CMAKE_SOURCE_DIR}/tests/test_alu.yaml ${CMAKE_SOURCE_DIR}/script/generate_alu_test_files.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/script
    COMMENT "Generating alu tests from test_alu.yaml"
)
# Test Executables
add_executable(test_alu tests/test_alu_gen.c src/alu.c)
target_link_libraries(test_alu PRIVATE log)
target_compile_options(test_alu PRIVATE -g )#-Wall -Wextra -Werror)
target_include_directories(test_alu PUBLIC include)
target_include_directories(test_alu PUBLIC lib/logger/src)

add_test(NAME test_alu COMMAND test_alu)
