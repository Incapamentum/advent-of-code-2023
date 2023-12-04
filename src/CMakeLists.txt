cmake_minimum_required(VERSION 3.25)

# Custom function to copy DLLs post-build
function(copy_helper_dll target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Helpers> $<TARGET_FILE_DIR:${target_name}>
    )
endfunction()

# Library
add_subdirectory(helpers)

# Daily AoC challenges
add_subdirectory(day1)
add_subdirectory(day2)