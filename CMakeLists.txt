cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project("Advent of Code 2023"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

add_subdirectory(src)