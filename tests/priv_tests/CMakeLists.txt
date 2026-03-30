file(GLOB GLOBBED_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/platform/*")

# Iterate over the list of found items
foreach(item IN LISTS GLOBBED_DIRS)
    # Check if the current item is actually a directory
    if(IS_DIRECTORY "${item}")
      get_filename_component(EXTENSION "${item}" NAME)
      add_test(NAME    "${EXTENSION}"
               COMMAND "bash" "-c" "ISA=${ELF_COMPILER_MARCH} CROSS_COMPILE=${LINUX_CROSS_COMPILE_PREFIX} EXTENSION=${EXTENSION} OUTPUTS_DIR=${CMAKE_BINARY_DIR} make -f ${CMAKE_CURRENT_SOURCE_DIR}/Makefile; ${SPIKE_PATH} --isa=${SPIKE_ISA} -m0x80000000:0x100000000 ${CMAKE_BINARY_DIR}/${EXTENSION}.elf"
               WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
      set_tests_properties("${EXTENSION}" PROPERTIES LABELS "verif_privilege")
    endif()
endforeach()

# disable tests marked with disabled labels
disable_tests("." "${DISABLED_LABELS}")
