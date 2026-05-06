add_executable(SpikeStepTraceTest
  SpikeStepTraceTest.cc
)

target_link_libraries(SpikeStepTraceTest
  PRIVATE
    spikeInterface_V2
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)
