cmake_minimum_required(VERSION 3.26)
project("Spike testing")

enable_testing()

# list of all available test
set(TESTS_ADDED "")

# list of test labes to disable
set(DISABLED_LABELS "Zvk;")

# set or override linux compiler prefix
set(LINUX_CROSS_COMPILE_PREFIX
  "/work/tools/rvv-gcc/gcc14-linux/bin/riscv64-unknown-linux-gnu-"
  CACHE STRING
  "linux cross-compiler prefix")
set(LINUX_C_COMPILER   "${LINUX_CROSS_COMPILE_PREFIX}gcc")
set(LINUX_CXX_COMPILER "${LINUX_CROSS_COMPILE_PREFIX}g++")

# set or override compiler march flags
set(COMPILER_MARCH
  "rv64imafdcvhzicntr_zicbom_zicbop_zicboz_zicsr_zifencei_zihpm_zba_zbb_zbc_zbs_zk_zfa_zfh_zfhmin_zvfhmin_zvkb_zvkg_zvknha_zvknhb_zvl512b_svnapot"
  CACHE STRING
  "compiler march flags")

set(ELF_COMPILER_MARCH
  "rv64imafdcvhzicntr_zicbom_zicbop_zicboz_zicsr_zifencei_zihpm_zba_zbb_zbc_zbs_zk_zfa_zfh_zfhmin_zvfhmin_zvkb_zvkg_zvknha_zvknhb_zvl512b"
  CACHE STRING
  "compiler march flags")

# set or override spike isa flags
set(SPIKE_ISA
  "rv64imafdcvh_Zicbom_Zicbop_Zicboz_Zicsr_Zifencei_Zihpm_Zmmul_Zfh_Zba_Zbb_Zbc_Zbs_Zk_zfa_zfh_zfhmin_zvfhmin_Zvbb_Zvkg_Zvknha_Zvknhb_Zvl512b_Svnapot"
  CACHE STRING
  "spike isa flags")

# set or override spike-under-test
set(SPIKE_PATH
  "${PROJECT_BINARY_DIR}/../../release/thirdparty/riscv-isa-sim/bin/spike"
  CACHE STRING
  "")

# function to disable test by labels in given directory
function(disable_tests DIR DISABLED_LABELS)
  get_property(TEST_NAMES DIRECTORY ${DIR} PROPERTY TESTS)
  foreach(TEST_NAME ${TEST_NAMES})
    get_test_property(${TEST_NAME} LABELS TEST_LABELS)
    foreach(TEST_LABEL ${TEST_LABELS})
      list(FIND "DISABLED_LABELS" "${TEST_LABEL}" INDEX)
      if(INDEX GREATER -1)
        set_tests_properties(${TEST_NAME} PROPERTIES DISABLED True)
      endif()
    endforeach()
  endforeach()
endfunction()

# riscv-arch-tests suite 
set("RISCV_ARCH_TESTS" "${CMAKE_CURRENT_SOURCE_DIR}/tests/riscv-arch-tests")
add_subdirectory("${RISCV_ARCH_TESTS}")

# Verification team priv tests suite
set("PRIVILEGE_TESTS" "${CMAKE_CURRENT_SOURCE_DIR}/tests/priv_tests")
add_subdirectory("${PRIVILEGE_TESTS}")
