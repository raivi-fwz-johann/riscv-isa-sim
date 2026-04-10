if(NOT DEFINED TRACE_LEVEL)
    set(TRACE_LEVEL "FULL_TRACE")
endif()

file(GLOB_RECURSE src
    *.cpp
)

add_library(functrace
    ${src}
)
set_target_properties(functrace PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(functrace PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_compile_definitions(functrace PUBLIC
    ${TRACE_LEVEL}
)
file(GLOB hdrs
    *.hpp
)
install(FILES ${hdrs} DESTINATION include/functrace)
