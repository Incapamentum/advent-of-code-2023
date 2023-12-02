cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project("AoC 2023 - Day 1"
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(Trebuchet
    trebuchet.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample-puzzle.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input-puzzle.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)