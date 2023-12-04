cmake_minimum_required(VERSION 3.25)
cmake_policy(SET CMP0048 NEW)

project("AoC 2023 - Day 1"
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(Trebuchet
    trebuchet.cpp
)
target_link_libraries(Trebuchet PRIVATE Helpers)
target_include_directories(Trebuchet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(GLOB PuzzleFiles *input*.txt)

file(COPY ${PuzzleFiles}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

# Copy the 'Helper' DLL to same directory of executable
copy_helper_dll(Trebuchet)