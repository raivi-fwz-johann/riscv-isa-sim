file(GLOB_RECURSE srcs "*.cpp")

add_library(utility
    ${srcs}
)
target_include_directories(utility PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)