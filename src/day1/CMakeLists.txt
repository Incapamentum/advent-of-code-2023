cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project("AoC 2023 - Day 1"
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(Trebuchet
    trebuchet.cpp
)

file(GLOB PuzzleFiles *input*.txt)

file(COPY ${PuzzleFiles}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)