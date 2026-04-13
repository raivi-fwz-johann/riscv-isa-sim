cmake_minimum_required (VERSION 3.20)
project(spikeInterface_V2)
include(GNUInstallDirs)

add_subdirectory(utility)
add_subdirectory(utilityLibs)
option(SPIKE_STATIC_ENV_LIB "Whether to link static libstdc++" OFF)
if(SPIKE_STATIC_ENV_LIB)
  message("-- spike interface link static libstdc++")
endif()

# enable c++17
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-fPIC -Wdeprecated -Werror -Wall -Wextra -Winline
  -Winit-self -Wno-unused-function -Wno-uninitialized -Wno-sequence-point
  -Wno-inline -Wno-unknown-pragmas -Wno-unused-parameter
  -Wno-missing-field-initializers $<$<COMPILE_LANGUAGE:CXX>:-Wno-terminate>)

find_package(Threads REQUIRED)

set(SPIKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SPIKE_INSTALL_DIR ${CMAKE_BINARY_DIR}/thirdparty/riscv-isa-sim)
set(SPIKE_LIB_DIR ${SPIKE_INSTALL_DIR}/lib)
set(SPIKE_BUILD_DIR "${SPIKE_SOURCE_DIR}/build")
set(SPIKE_BUILD_LIB_DIR ${SPIKE_BUILD_DIR})
set(SPIKE_INTF_LIBS
  ${SPIKE_BUILD_LIB_DIR}/libextensions.a
  ${SPIKE_LIB_DIR}/libriscv.so
  ${SPIKE_LIB_DIR}/libsoftfloat.so
  ${SPIKE_LIB_DIR}/libfesvr.a
  ${SPIKE_LIB_DIR}/libdisasm.a
)
file(MAKE_DIRECTORY "${SPIKE_BUILD_DIR}")
file(GLOB_RECURSE SPIKE_SOURCES CONFIGURE_DEPENDS
  ${SPIKE_SOURCE_DIR}/*.[ch]*
  ${SPIKE_SOURCE_DIR}/*.S
  ${SPIKE_SOURCE_DIR}/*.inc
)
list(FILTER SPIKE_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/.*")
set(SPIKE_ARTIFACTS
  ${SPIKE_INSTALL_DIR}/bin/spike
  ${SPIKE_INSTALL_DIR}/include
  ${SPIKE_INTF_LIBS}
)
set(ee env TMPDIR=${SPIKE_BUILD_DIR})
if(SPIKE_STATIC_ENV_LIB)
add_custom_command(
  OUTPUT ${SPIKE_ARTIFACTS}
  COMMAND ${ee} sh ../configure LDFLAGS="-static-libstdc++" --prefix=${SPIKE_INSTALL_DIR} --without-boost --without-boost-asio --without-boost-regex > /dev/null
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SPIKE_BUILD_DIR}/runtime ${SPIKE_BUILD_DIR}/integration
  COMMAND ${ee} make -j4 > make.log 2>&1
  COMMAND ${ee} make install > /dev/null
  WORKING_DIRECTORY ${SPIKE_BUILD_DIR}
  DEPENDS ${SPIKE_SOURCES}
)
else()
add_custom_command(
  OUTPUT ${SPIKE_ARTIFACTS}
  COMMAND ${ee} sh ../configure --prefix=${SPIKE_INSTALL_DIR} --without-boost --without-boost-asio --without-boost-regex > /dev/null
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SPIKE_BUILD_DIR}/runtime ${SPIKE_BUILD_DIR}/integration
  COMMAND ${ee} make -j4 > make.log 2>&1
  COMMAND ${ee} make install > /dev/null
  WORKING_DIRECTORY ${SPIKE_BUILD_DIR}
  DEPENDS ${SPIKE_SOURCES}
)
endif()
add_custom_target(spike DEPENDS ${SPIKE_ARTIFACTS})

file(GLOB_RECURSE SPIKE_INTERFACE_SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(spikeInterface_V2 SHARED
  ${SPIKE_INTERFACE_SRCS}
)
set_target_properties(spikeInterface_V2 PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_dependencies(spikeInterface_V2 spike)
target_include_directories(spikeInterface_V2 PUBLIC
  src
  ${SPIKE_SOURCE_DIR}
  ${SPIKE_SOURCE_DIR}/extensions
  ${SPIKE_SOURCE_DIR}/riscv
  ${SPIKE_SOURCE_DIR}/fesvr
  ${SPIKE_SOURCE_DIR}/fdt
  ${SPIKE_SOURCE_DIR}/softfloat
  ${SPIKE_SOURCE_DIR}/patch
  ${SPIKE_INSTALL_DIR}/include
  ${SPIKE_INSTALL_DIR}/include/riscv
  ${SPIKE_INSTALL_DIR}/include/fesvr
  ${SPIKE_INSTALL_DIR}/include/fdt
  ${SPIKE_INSTALL_DIR}/include/softfloat
)
target_link_libraries(spikeInterface_V2 ${SPIKE_INTF_LIBS} ${CMAKE_THREAD_LIBS_INIT} utility functrace)
if(SPIKE_STATIC_ENV_LIB)
  target_link_options(spikeInterface_V2 PRIVATE -static-libstdc++)
endif()

add_executable(SpikeSimObjTest
  src/SpikeSimObjTest.cc
)
target_link_libraries(SpikeSimObjTest spikeInterface_V2 ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(SimObjTest
  src/SimObjTest.cc
)
target_link_libraries(SimObjTest spikeInterface_V2 ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(MultiThreadRunTest
  src/MultiThreadRunTest.cc
)
target_link_libraries(MultiThreadRunTest spikeInterface_V2 utility functrace ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(SpikeSimObjAsyncTest
  src/SpikeSimObjAsyncTest.cc
)
target_link_libraries(SpikeSimObjAsyncTest spikeInterface_V2 utility functrace ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(SpikeStateExporterTest
  src/SpikeStateExporterTest.cc
)
target_link_libraries(SpikeStateExporterTest spikeInterface_V2 ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(SpikeRoiStateTest
  src/SpikeRoiStateTest.cc
)
target_link_libraries(SpikeRoiStateTest spikeInterface_V2 ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(RawSpikeRuntimeSmokeTest
  src/RawSpikeRuntimeSmokeTest.cc
)
target_link_libraries(RawSpikeRuntimeSmokeTest spikeInterface_V2 ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS spikeInterface_V2)
install(PROGRAMS ${SPIKE_INSTALL_DIR}/bin/spike TYPE BIN)
install(FILES ${SPIKE_INTF_LIBS} TYPE LIB)
