cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project("AoC 2023 - Day 2"
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(Cube-Conundrum
    cube-conundrum.cpp
)
target_link_libraries(Cube-Conundrum PRIVATE Helpers)
target_include_directories(Cube-Conundrum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(GLOB InputFiles *input*.txt)

file(COPY ${InputFiles}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

# Copy the 'Helper' DLL ot same directory of executable
copy_helper_dll(Cube-Conundrum)