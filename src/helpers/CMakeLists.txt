cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project(Helpers
    VERSION 0.1.0
    LANGUAGES CXX
)

add_library(Helpers SHARED
    helpers.cpp
)
target_include_directories(Helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)