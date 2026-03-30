#==================== A/amoadd.d-01 ============================================
add_test(NAME    "A/amoadd.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoadd.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoadd.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.d-01/signature.test"
         )
set_tests_properties("A/amoadd.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoadd.w-01 ============================================
add_test(NAME    "A/amoadd.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoadd.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoadd.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoadd.w-01/signature.test"
         )
set_tests_properties("A/amoadd.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoand.d-01 ============================================
add_test(NAME    "A/amoand.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoand.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoand.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.d-01/signature.test"
         )
set_tests_properties("A/amoand.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoand.w-01 ============================================
add_test(NAME    "A/amoand.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoand.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoand.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoand.w-01/signature.test"
         )
set_tests_properties("A/amoand.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomax.d-01 ============================================
add_test(NAME    "A/amomax.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomax.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomax.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.d-01/signature.test"
         )
set_tests_properties("A/amomax.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomax.w-01 ============================================
add_test(NAME    "A/amomax.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomax.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomax.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomax.w-01/signature.test"
         )
set_tests_properties("A/amomax.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomaxu.d-01 ===========================================
add_test(NAME    "A/amomaxu.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomaxu.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomaxu.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.d-01/signature.test"
         )
set_tests_properties("A/amomaxu.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomaxu.w-01 ===========================================
add_test(NAME    "A/amomaxu.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomaxu.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomaxu.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomaxu.w-01/signature.test"
         )
set_tests_properties("A/amomaxu.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomin.d-01 ============================================
add_test(NAME    "A/amomin.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomin.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomin.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.d-01/signature.test"
         )
set_tests_properties("A/amomin.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amomin.w-01 ============================================
add_test(NAME    "A/amomin.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amomin.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amomin.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amomin.w-01/signature.test"
         )
set_tests_properties("A/amomin.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amominu.d-01 ===========================================
add_test(NAME    "A/amominu.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amominu.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amominu.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.d-01/signature.test"
         )
set_tests_properties("A/amominu.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amominu.w-01 ===========================================
add_test(NAME    "A/amominu.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amominu.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amominu.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amominu.w-01/signature.test"
         )
set_tests_properties("A/amominu.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoor.d-01 =============================================
add_test(NAME    "A/amoor.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoor.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoor.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.d-01/signature.test"
         )
set_tests_properties("A/amoor.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoor.w-01 =============================================
add_test(NAME    "A/amoor.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoor.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoor.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoor.w-01/signature.test"
         )
set_tests_properties("A/amoor.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoswap.d-01 ===========================================
add_test(NAME    "A/amoswap.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoswap.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoswap.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.d-01/signature.test"
         )
set_tests_properties("A/amoswap.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoswap.w-01 ===========================================
add_test(NAME    "A/amoswap.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoswap.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoswap.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoswap.w-01/signature.test"
         )
set_tests_properties("A/amoswap.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoxor.d-01 ============================================
add_test(NAME    "A/amoxor.d-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.d-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoxor.d-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.d-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.d-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.d-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoxor.d-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.d-01/signature.test"
         )
set_tests_properties("A/amoxor.d-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== A/amoxor.w-01 ============================================
add_test(NAME    "A/amoxor.w-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.w-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/A/src/amoxor.w-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.w-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.w-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.w-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/A/src/amoxor.w-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/A/amoxor.w-01/signature.test"
         )
set_tests_properties("A/amoxor.w-01" PROPERTIES LABELS "A")
#===============================================================================

#==================== B/add.uw-01 ==============================================
add_test(NAME    "B/add.uw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/add.uw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/add.uw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/add.uw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/add.uw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/add.uw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/add.uw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/add.uw-01/signature.test"
         )
set_tests_properties("B/add.uw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/andn-01 ================================================
add_test(NAME    "B/andn-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/andn-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/andn-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/andn-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/andn-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/andn-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/andn-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/andn-01/signature.test"
         )
set_tests_properties("B/andn-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bclr-01 ================================================
add_test(NAME    "B/bclr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bclr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bclr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclr-01/signature.test"
         )
set_tests_properties("B/bclr-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bclri-01 ===============================================
add_test(NAME    "B/bclri-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclri-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bclri-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclri-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclri-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclri-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bclri-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bclri-01/signature.test"
         )
set_tests_properties("B/bclri-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bext-01 ================================================
add_test(NAME    "B/bext-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bext-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bext-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bext-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bext-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bext-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bext-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bext-01/signature.test"
         )
set_tests_properties("B/bext-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bexti-01 ===============================================
add_test(NAME    "B/bexti-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bexti-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bexti-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bexti-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bexti-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bexti-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bexti-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bexti-01/signature.test"
         )
set_tests_properties("B/bexti-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/binv-01 ================================================
add_test(NAME    "B/binv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/binv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/binv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binv-01/signature.test"
         )
set_tests_properties("B/binv-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/binvi-01 ===============================================
add_test(NAME    "B/binvi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binvi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/binvi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binvi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binvi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binvi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/binvi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/binvi-01/signature.test"
         )
set_tests_properties("B/binvi-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bset-01 ================================================
add_test(NAME    "B/bset-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bset-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bset-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bset-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bset-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bset-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bset-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bset-01/signature.test"
         )
set_tests_properties("B/bset-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/bseti-01 ===============================================
add_test(NAME    "B/bseti-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bseti-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/bseti-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bseti-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bseti-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bseti-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/bseti-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/bseti-01/signature.test"
         )
set_tests_properties("B/bseti-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/clmul-01 ===============================================
add_test(NAME    "B/clmul-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmul-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/clmul-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmul-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmul-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmul-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/clmul-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmul-01/signature.test"
         )
set_tests_properties("B/clmul-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/clmulh-01 ==============================================
add_test(NAME    "B/clmulh-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulh-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/clmulh-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulh-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulh-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulh-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/clmulh-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulh-01/signature.test"
         )
set_tests_properties("B/clmulh-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/clmulr-01 ==============================================
add_test(NAME    "B/clmulr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/clmulr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/clmulr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clmulr-01/signature.test"
         )
set_tests_properties("B/clmulr-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/clz-01 =================================================
add_test(NAME    "B/clz-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clz-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/clz-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clz-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clz-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clz-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/clz-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clz-01/signature.test"
         )
set_tests_properties("B/clz-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/clzw-01 ================================================
add_test(NAME    "B/clzw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clzw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/clzw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clzw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clzw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clzw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/clzw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/clzw-01/signature.test"
         )
set_tests_properties("B/clzw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/cpop-01 ================================================
add_test(NAME    "B/cpop-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpop-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/cpop-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpop-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpop-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpop-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/cpop-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpop-01/signature.test"
         )
set_tests_properties("B/cpop-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/cpopw-01 ===============================================
add_test(NAME    "B/cpopw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpopw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/cpopw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpopw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpopw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpopw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/cpopw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/cpopw-01/signature.test"
         )
set_tests_properties("B/cpopw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/ctz-01 =================================================
add_test(NAME    "B/ctz-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctz-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/ctz-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctz-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctz-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctz-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/ctz-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctz-01/signature.test"
         )
set_tests_properties("B/ctz-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/ctzw-01 ================================================
add_test(NAME    "B/ctzw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctzw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/ctzw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctzw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctzw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctzw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/ctzw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ctzw-01/signature.test"
         )
set_tests_properties("B/ctzw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/max-01 =================================================
add_test(NAME    "B/max-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/max-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/max-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/max-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/max-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/max-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/max-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/max-01/signature.test"
         )
set_tests_properties("B/max-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/maxu-01 ================================================
add_test(NAME    "B/maxu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/maxu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/maxu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/maxu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/maxu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/maxu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/maxu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/maxu-01/signature.test"
         )
set_tests_properties("B/maxu-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/min-01 =================================================
add_test(NAME    "B/min-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/min-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/min-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/min-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/min-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/min-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/min-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/min-01/signature.test"
         )
set_tests_properties("B/min-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/minu-01 ================================================
add_test(NAME    "B/minu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/minu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/minu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/minu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/minu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/minu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/minu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/minu-01/signature.test"
         )
set_tests_properties("B/minu-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/orcb_64-01 =============================================
add_test(NAME    "B/orcb_64-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orcb_64-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/orcb_64-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orcb_64-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orcb_64-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orcb_64-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/orcb_64-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orcb_64-01/signature.test"
         )
set_tests_properties("B/orcb_64-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/orn-01 =================================================
add_test(NAME    "B/orn-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orn-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/orn-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orn-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orn-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orn-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/orn-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/orn-01/signature.test"
         )
set_tests_properties("B/orn-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/rev8-01 ================================================
add_test(NAME    "B/rev8-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rev8-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/rev8-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rev8-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rev8-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rev8-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/rev8-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rev8-01/signature.test"
         )
set_tests_properties("B/rev8-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/rol-01 =================================================
add_test(NAME    "B/rol-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rol-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/rol-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rol-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rol-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rol-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/rol-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rol-01/signature.test"
         )
set_tests_properties("B/rol-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/rolw-01 ================================================
add_test(NAME    "B/rolw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rolw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/rolw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rolw-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rolw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rolw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/rolw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rolw-01/signature.test"
         )
set_tests_properties("B/rolw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/ror-01 =================================================
add_test(NAME    "B/ror-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ror-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/ror-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ror-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ror-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ror-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/ror-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/ror-01/signature.test"
         )
set_tests_properties("B/ror-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/rori-01 ================================================
add_test(NAME    "B/rori-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rori-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/rori-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rori-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rori-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rori-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/rori-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rori-01/signature.test"
         )
set_tests_properties("B/rori-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/roriw-01 ===============================================
add_test(NAME    "B/roriw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/roriw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/roriw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/roriw-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/roriw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/roriw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/roriw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/roriw-01/signature.test"
         )
set_tests_properties("B/roriw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/rorw-01 ================================================
add_test(NAME    "B/rorw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rorw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/rorw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rorw-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rorw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rorw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/rorw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/rorw-01/signature.test"
         )
set_tests_properties("B/rorw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sext.b-01 ==============================================
add_test(NAME    "B/sext.b-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.b-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sext.b-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.b-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.b-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.b-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sext.b-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.b-01/signature.test"
         )
set_tests_properties("B/sext.b-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sext.h-01 ==============================================
add_test(NAME    "B/sext.h-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.h-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sext.h-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.h-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.h-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.h-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sext.h-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sext.h-01/signature.test"
         )
set_tests_properties("B/sext.h-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh1add-01 ==============================================
add_test(NAME    "B/sh1add-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh1add-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh1add-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add-01/signature.test"
         )
set_tests_properties("B/sh1add-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh1add.uw-01 ===========================================
add_test(NAME    "B/sh1add.uw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add.uw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh1add.uw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add.uw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add.uw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add.uw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh1add.uw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh1add.uw-01/signature.test"
         )
set_tests_properties("B/sh1add.uw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh2add-01 ==============================================
add_test(NAME    "B/sh2add-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh2add-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh2add-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add-01/signature.test"
         )
set_tests_properties("B/sh2add-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh2add.uw-01 ===========================================
add_test(NAME    "B/sh2add.uw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add.uw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh2add.uw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add.uw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add.uw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add.uw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh2add.uw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh2add.uw-01/signature.test"
         )
set_tests_properties("B/sh2add.uw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh3add-01 ==============================================
add_test(NAME    "B/sh3add-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh3add-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh3add-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add-01/signature.test"
         )
set_tests_properties("B/sh3add-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/sh3add.uw-01 ===========================================
add_test(NAME    "B/sh3add.uw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add.uw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/sh3add.uw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add.uw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add.uw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add.uw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/sh3add.uw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/sh3add.uw-01/signature.test"
         )
set_tests_properties("B/sh3add.uw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/slli.uw-01 =============================================
add_test(NAME    "B/slli.uw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/slli.uw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/slli.uw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/slli.uw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/slli.uw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/slli.uw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/slli.uw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/slli.uw-01/signature.test"
         )
set_tests_properties("B/slli.uw-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/xnor-01 ================================================
add_test(NAME    "B/xnor-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/xnor-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/xnor-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/xnor-01/test.elf -DTEST_CASE_1=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/xnor-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/xnor-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/xnor-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/xnor-01/signature.test"
         )
set_tests_properties("B/xnor-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== B/zext.h_64-01 ===========================================
add_test(NAME    "B/zext.h_64-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/zext.h_64-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/B/src/zext.h_64-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/zext.h_64-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/B/zext.h_64-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/zext.h_64-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/B/src/zext.h_64-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/B/zext.h_64-01/signature.test"
         )
set_tests_properties("B/zext.h_64-01" PROPERTIES LABELS "B")
#===============================================================================

#==================== C/cadd-01 ================================================
add_test(NAME    "C/cadd-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cadd-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cadd-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cadd-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cadd-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cadd-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cadd-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cadd-01/signature.test"
         )
set_tests_properties("C/cadd-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/caddi-01 ===============================================
add_test(NAME    "C/caddi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/caddi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/caddi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi-01/signature.test"
         )
set_tests_properties("C/caddi-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/caddi16sp-01 ===========================================
add_test(NAME    "C/caddi16sp-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi16sp-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/caddi16sp-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi16sp-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi16sp-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi16sp-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/caddi16sp-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi16sp-01/signature.test"
         )
set_tests_properties("C/caddi16sp-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/caddi4spn-01 ===========================================
add_test(NAME    "C/caddi4spn-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi4spn-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/caddi4spn-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi4spn-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi4spn-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi4spn-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/caddi4spn-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddi4spn-01/signature.test"
         )
set_tests_properties("C/caddi4spn-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/caddiw-01 ==============================================
add_test(NAME    "C/caddiw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddiw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/caddiw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddiw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddiw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddiw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/caddiw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddiw-01/signature.test"
         )
set_tests_properties("C/caddiw-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/caddw-01 ===============================================
add_test(NAME    "C/caddw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/caddw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/caddw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/caddw-01/signature.test"
         )
set_tests_properties("C/caddw-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cand-01 ================================================
add_test(NAME    "C/cand-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cand-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cand-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cand-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cand-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cand-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cand-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cand-01/signature.test"
         )
set_tests_properties("C/cand-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/candi-01 ===============================================
add_test(NAME    "C/candi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/candi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/candi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/candi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/candi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/candi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/candi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/candi-01/signature.test"
         )
set_tests_properties("C/candi-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cbeqz-01 ===============================================
add_test(NAME    "C/cbeqz-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbeqz-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cbeqz-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbeqz-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbeqz-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbeqz-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cbeqz-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbeqz-01/signature.test"
         )
set_tests_properties("C/cbeqz-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cbnez-01 ===============================================
add_test(NAME    "C/cbnez-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbnez-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cbnez-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbnez-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbnez-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbnez-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cbnez-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cbnez-01/signature.test"
         )
set_tests_properties("C/cbnez-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cebreak-01 =============================================
add_test(NAME    "C/cebreak-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cebreak-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cebreak-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cebreak-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cebreak-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cebreak-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cebreak-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cebreak-01/signature.test"
         )
set_tests_properties("C/cebreak-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cj-01 ==================================================
add_test(NAME    "C/cj-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cj-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cj-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cj-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cj-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cj-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cj-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cj-01/signature.test"
         )
set_tests_properties("C/cj-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cjalr-01 ===============================================
add_test(NAME    "C/cjalr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjalr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cjalr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjalr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjalr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjalr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cjalr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjalr-01/signature.test"
         )
set_tests_properties("C/cjalr-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cjr-01 =================================================
add_test(NAME    "C/cjr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cjr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cjr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cjr-01/signature.test"
         )
set_tests_properties("C/cjr-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cld-01 =================================================
add_test(NAME    "C/cld-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cld-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cld-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cld-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cld-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cld-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cld-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cld-01/signature.test"
         )
set_tests_properties("C/cld-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cldsp-01 ===============================================
add_test(NAME    "C/cldsp-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cldsp-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cldsp-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cldsp-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cldsp-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cldsp-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cldsp-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cldsp-01/signature.test"
         )
set_tests_properties("C/cldsp-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cli-01 =================================================
add_test(NAME    "C/cli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cli-01/signature.test"
         )
set_tests_properties("C/cli-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/clui-01 ================================================
add_test(NAME    "C/clui-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clui-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/clui-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clui-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clui-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clui-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/clui-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clui-01/signature.test"
         )
set_tests_properties("C/clui-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/clw-01 =================================================
add_test(NAME    "C/clw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/clw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/clw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clw-01/signature.test"
         )
set_tests_properties("C/clw-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/clwsp-01 ===============================================
add_test(NAME    "C/clwsp-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clwsp-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/clwsp-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clwsp-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clwsp-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clwsp-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/clwsp-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/clwsp-01/signature.test"
         )
set_tests_properties("C/clwsp-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cmv-01 =================================================
add_test(NAME    "C/cmv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cmv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cmv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cmv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cmv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cmv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cmv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cmv-01/signature.test"
         )
set_tests_properties("C/cmv-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cnop-01 ================================================
add_test(NAME    "C/cnop-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cnop-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cnop-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cnop-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cnop-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cnop-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cnop-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cnop-01/signature.test"
         )
set_tests_properties("C/cnop-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cor-01 =================================================
add_test(NAME    "C/cor-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cor-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cor-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cor-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cor-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cor-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cor-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cor-01/signature.test"
         )
set_tests_properties("C/cor-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csd-01 =================================================
add_test(NAME    "C/csd-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csd-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csd-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csd-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csd-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csd-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csd-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csd-01/signature.test"
         )
set_tests_properties("C/csd-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csdsp-01 ===============================================
add_test(NAME    "C/csdsp-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csdsp-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csdsp-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csdsp-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csdsp-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csdsp-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csdsp-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csdsp-01/signature.test"
         )
set_tests_properties("C/csdsp-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cslli-01 ===============================================
add_test(NAME    "C/cslli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cslli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cslli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cslli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cslli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cslli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cslli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cslli-01/signature.test"
         )
set_tests_properties("C/cslli-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csrai-01 ===============================================
add_test(NAME    "C/csrai-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrai-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csrai-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrai-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrai-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrai-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csrai-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrai-01/signature.test"
         )
set_tests_properties("C/csrai-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csrli-01 ===============================================
add_test(NAME    "C/csrli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csrli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csrli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csrli-01/signature.test"
         )
set_tests_properties("C/csrli-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csub-01 ================================================
add_test(NAME    "C/csub-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csub-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csub-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csub-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csub-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csub-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csub-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csub-01/signature.test"
         )
set_tests_properties("C/csub-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csubw-01 ===============================================
add_test(NAME    "C/csubw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csubw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csubw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csubw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csubw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csubw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csubw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csubw-01/signature.test"
         )
set_tests_properties("C/csubw-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/csw-01 =================================================
add_test(NAME    "C/csw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/csw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/csw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/csw-01/signature.test"
         )
set_tests_properties("C/csw-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cswsp-01 ===============================================
add_test(NAME    "C/cswsp-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cswsp-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cswsp-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cswsp-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cswsp-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cswsp-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cswsp-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cswsp-01/signature.test"
         )
set_tests_properties("C/cswsp-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== C/cxor-01 ================================================
add_test(NAME    "C/cxor-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cxor-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/C/src/cxor-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cxor-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cxor-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cxor-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/C/src/cxor-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/C/cxor-01/signature.test"
         )
set_tests_properties("C/cxor-01" PROPERTIES LABELS "C")
#===============================================================================

#==================== CMO/cbo.zero-01 ==========================================
add_test(NAME    "CMO/cbo.zero-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/CMO/cbo.zero-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/CMO/src/cbo.zero-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/CMO/cbo.zero-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/CMO/cbo.zero-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/CMO/cbo.zero-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/CMO/src/cbo.zero-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/CMO/cbo.zero-01/signature.test"
         )
set_tests_properties("CMO/cbo.zero-01" PROPERTIES LABELS "CMO")
#===============================================================================

#==================== D/fcvt.d.l_b25-01 ========================================
add_test(NAME    "D/fcvt.d.l_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.l_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.l_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b25-01/signature.test"
         )
set_tests_properties("D/fcvt.d.l_b25-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.d.l_b26-01 ========================================
add_test(NAME    "D/fcvt.d.l_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.l_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.l_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.l_b26-01/signature.test"
         )
set_tests_properties("D/fcvt.d.l_b26-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.d.lu_b25-01 =======================================
add_test(NAME    "D/fcvt.d.lu_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.lu_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.lu_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b25-01/signature.test"
         )
set_tests_properties("D/fcvt.d.lu_b25-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.d.lu_b26-01 =======================================
add_test(NAME    "D/fcvt.d.lu_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.lu_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.d.lu_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.d.lu_b26-01/signature.test"
         )
set_tests_properties("D/fcvt.d.lu_b26-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b1-01 =========================================
add_test(NAME    "D/fcvt.l.d_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b1-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b1-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b22-01 ========================================
add_test(NAME    "D/fcvt.l.d_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b22-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b22-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b23-01 ========================================
add_test(NAME    "D/fcvt.l.d_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b23-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b23-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b24-01 ========================================
add_test(NAME    "D/fcvt.l.d_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b24-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b24-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b27-01 ========================================
add_test(NAME    "D/fcvt.l.d_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b27-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b27-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b28-01 ========================================
add_test(NAME    "D/fcvt.l.d_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b28-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b28-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.l.d_b29-01 ========================================
add_test(NAME    "D/fcvt.l.d_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.l.d_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.l.d_b29-01/signature.test"
         )
set_tests_properties("D/fcvt.l.d_b29-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b1-01 ========================================
add_test(NAME    "D/fcvt.lu.d_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b1-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b1-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b22-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b22-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b22-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b23-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b23-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b23-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b24-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b24-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b24-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b27-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b27-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b27-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b28-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b28-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b28-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fcvt.lu.d_b29-01 =======================================
add_test(NAME    "D/fcvt.lu.d_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fcvt.lu.d_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fcvt.lu.d_b29-01/signature.test"
         )
set_tests_properties("D/fcvt.lu.d_b29-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.d.x_b25-01 =========================================
add_test(NAME    "D/fmv.d.x_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.d.x_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.d.x_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b25-01/signature.test"
         )
set_tests_properties("D/fmv.d.x_b25-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.d.x_b26-01 =========================================
add_test(NAME    "D/fmv.d.x_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.d.x_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.d.x_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.d.x_b26-01/signature.test"
         )
set_tests_properties("D/fmv.d.x_b26-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b1-01 ==========================================
add_test(NAME    "D/fmv.x.d_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b1-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b1-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b22-01 =========================================
add_test(NAME    "D/fmv.x.d_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b22-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b22-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b23-01 =========================================
add_test(NAME    "D/fmv.x.d_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b23-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b23-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b24-01 =========================================
add_test(NAME    "D/fmv.x.d_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b24-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b24-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b27-01 =========================================
add_test(NAME    "D/fmv.x.d_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b27-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b27-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b28-01 =========================================
add_test(NAME    "D/fmv.x.d_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b28-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b28-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== D/fmv.x.d_b29-01 =========================================
add_test(NAME    "D/fmv.x.d_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/D/src/fmv.x.d_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/D/fmv.x.d_b29-01/signature.test"
         )
set_tests_properties("D/fmv.x.d_b29-01" PROPERTIES LABELS "D")
#===============================================================================

#==================== F/fcvt.l.s_b1-01 =========================================
add_test(NAME    "F/fcvt.l.s_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b1-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b1-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b22-01 ========================================
add_test(NAME    "F/fcvt.l.s_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b22-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b22-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b23-01 ========================================
add_test(NAME    "F/fcvt.l.s_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b23-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b23-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b24-01 ========================================
add_test(NAME    "F/fcvt.l.s_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b24-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b24-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b27-01 ========================================
add_test(NAME    "F/fcvt.l.s_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b27-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b27-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b28-01 ========================================
add_test(NAME    "F/fcvt.l.s_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b28-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b28-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.l.s_b29-01 ========================================
add_test(NAME    "F/fcvt.l.s_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.l.s_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.l.s_b29-01/signature.test"
         )
set_tests_properties("F/fcvt.l.s_b29-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b1-01 ========================================
add_test(NAME    "F/fcvt.lu.s_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b1-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b1-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b22-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b22-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b22-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b23-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b23-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b23-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b24-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b24-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b24-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b27-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b27-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b27-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b28-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b28-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b28-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.lu.s_b29-01 =======================================
add_test(NAME    "F/fcvt.lu.s_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.lu.s_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.lu.s_b29-01/signature.test"
         )
set_tests_properties("F/fcvt.lu.s_b29-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.s.l_b25-01 ========================================
add_test(NAME    "F/fcvt.s.l_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.l_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.l_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b25-01/signature.test"
         )
set_tests_properties("F/fcvt.s.l_b25-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.s.l_b26-01 ========================================
add_test(NAME    "F/fcvt.s.l_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.l_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.l_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.l_b26-01/signature.test"
         )
set_tests_properties("F/fcvt.s.l_b26-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.s.lu_b25-01 =======================================
add_test(NAME    "F/fcvt.s.lu_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.lu_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.lu_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b25-01/signature.test"
         )
set_tests_properties("F/fcvt.s.lu_b25-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== F/fcvt.s.lu_b26-01 =======================================
add_test(NAME    "F/fcvt.s.lu_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.lu_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/F/src/fcvt.s.lu_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/F/fcvt.s.lu_b26-01/signature.test"
         )
set_tests_properties("F/fcvt.s.lu_b26-01" PROPERTIES LABELS "F")
#===============================================================================

#==================== I/add-01 =================================================
add_test(NAME    "I/add-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/add-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/add-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/add-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/add-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/add-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/add-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/add-01/signature.test"
         )
set_tests_properties("I/add-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/addi-01 ================================================
add_test(NAME    "I/addi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/addi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/addi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addi-01/signature.test"
         )
set_tests_properties("I/addi-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/addiw-01 ===============================================
add_test(NAME    "I/addiw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addiw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/addiw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addiw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addiw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addiw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/addiw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addiw-01/signature.test"
         )
set_tests_properties("I/addiw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/addw-01 ================================================
add_test(NAME    "I/addw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/addw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/addw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/addw-01/signature.test"
         )
set_tests_properties("I/addw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/and-01 =================================================
add_test(NAME    "I/and-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/and-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/and-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/and-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/and-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/and-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/and-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/and-01/signature.test"
         )
set_tests_properties("I/and-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/andi-01 ================================================
add_test(NAME    "I/andi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/andi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/andi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/andi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/andi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/andi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/andi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/andi-01/signature.test"
         )
set_tests_properties("I/andi-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/auipc-01 ===============================================
add_test(NAME    "I/auipc-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/auipc-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/auipc-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/auipc-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/auipc-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/auipc-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/auipc-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/auipc-01/signature.test"
         )
set_tests_properties("I/auipc-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/beq-01 =================================================
add_test(NAME    "I/beq-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/beq-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/beq-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/beq-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/beq-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/beq-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/beq-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/beq-01/signature.test"
         )
set_tests_properties("I/beq-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/bge-01 =================================================
add_test(NAME    "I/bge-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bge-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/bge-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bge-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bge-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bge-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/bge-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bge-01/signature.test"
         )
set_tests_properties("I/bge-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/bgeu-01 ================================================
add_test(NAME    "I/bgeu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bgeu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/bgeu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bgeu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bgeu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bgeu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/bgeu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bgeu-01/signature.test"
         )
set_tests_properties("I/bgeu-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/blt-01 =================================================
add_test(NAME    "I/blt-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/blt-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/blt-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/blt-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/blt-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/blt-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/blt-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/blt-01/signature.test"
         )
set_tests_properties("I/blt-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/bltu-01 ================================================
add_test(NAME    "I/bltu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bltu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/bltu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bltu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bltu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bltu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/bltu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bltu-01/signature.test"
         )
set_tests_properties("I/bltu-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/bne-01 =================================================
add_test(NAME    "I/bne-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bne-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/bne-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bne-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bne-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bne-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/bne-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/bne-01/signature.test"
         )
set_tests_properties("I/bne-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/fence-01 ===============================================
add_test(NAME    "I/fence-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/fence-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/fence-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/fence-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/fence-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/fence-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/fence-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/fence-01/signature.test"
         )
set_tests_properties("I/fence-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/jal-01 =================================================
add_test(NAME    "I/jal-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jal-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/jal-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jal-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jal-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jal-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/jal-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jal-01/signature.test"
         )
set_tests_properties("I/jal-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/jalr-01 ================================================
add_test(NAME    "I/jalr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jalr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/jalr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jalr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jalr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jalr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/jalr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/jalr-01/signature.test"
         )
set_tests_properties("I/jalr-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lb-align-01 ============================================
add_test(NAME    "I/lb-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lb-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lb-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lb-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lb-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lb-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lb-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lb-align-01/signature.test"
         )
set_tests_properties("I/lb-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lbu-align-01 ===========================================
add_test(NAME    "I/lbu-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lbu-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lbu-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lbu-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lbu-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lbu-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lbu-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lbu-align-01/signature.test"
         )
set_tests_properties("I/lbu-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/ld-align-01 ============================================
add_test(NAME    "I/ld-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ld-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/ld-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ld-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ld-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ld-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/ld-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ld-align-01/signature.test"
         )
set_tests_properties("I/ld-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lh-align-01 ============================================
add_test(NAME    "I/lh-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lh-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lh-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lh-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lh-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lh-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lh-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lh-align-01/signature.test"
         )
set_tests_properties("I/lh-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lhu-align-01 ===========================================
add_test(NAME    "I/lhu-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lhu-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lhu-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lhu-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lhu-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lhu-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lhu-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lhu-align-01/signature.test"
         )
set_tests_properties("I/lhu-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lui-01 =================================================
add_test(NAME    "I/lui-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lui-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lui-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lui-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lui-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lui-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lui-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lui-01/signature.test"
         )
set_tests_properties("I/lui-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lw-align-01 ============================================
add_test(NAME    "I/lw-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lw-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lw-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lw-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lw-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lw-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lw-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lw-align-01/signature.test"
         )
set_tests_properties("I/lw-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/lwu-align-01 ===========================================
add_test(NAME    "I/lwu-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lwu-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/lwu-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lwu-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lwu-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lwu-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/lwu-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/lwu-align-01/signature.test"
         )
set_tests_properties("I/lwu-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/or-01 ==================================================
add_test(NAME    "I/or-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/or-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/or-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/or-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/or-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/or-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/or-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/or-01/signature.test"
         )
set_tests_properties("I/or-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/ori-01 =================================================
add_test(NAME    "I/ori-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ori-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/ori-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ori-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ori-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ori-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/ori-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/ori-01/signature.test"
         )
set_tests_properties("I/ori-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sb-align-01 ============================================
add_test(NAME    "I/sb-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sb-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sb-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sb-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sb-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sb-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sb-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sb-align-01/signature.test"
         )
set_tests_properties("I/sb-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sd-align-01 ============================================
add_test(NAME    "I/sd-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sd-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sd-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sd-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sd-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sd-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sd-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sd-align-01/signature.test"
         )
set_tests_properties("I/sd-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sh-align-01 ============================================
add_test(NAME    "I/sh-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sh-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sh-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sh-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sh-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sh-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sh-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sh-align-01/signature.test"
         )
set_tests_properties("I/sh-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sll-01 =================================================
add_test(NAME    "I/sll-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sll-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sll-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sll-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sll-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sll-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sll-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sll-01/signature.test"
         )
set_tests_properties("I/sll-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/slli-01 ================================================
add_test(NAME    "I/slli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/slli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/slli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slli-01/signature.test"
         )
set_tests_properties("I/slli-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/slliw-01 ===============================================
add_test(NAME    "I/slliw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slliw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/slliw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slliw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slliw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slliw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/slliw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slliw-01/signature.test"
         )
set_tests_properties("I/slliw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sllw-01 ================================================
add_test(NAME    "I/sllw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sllw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sllw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sllw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sllw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sllw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sllw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sllw-01/signature.test"
         )
set_tests_properties("I/sllw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/slt-01 =================================================
add_test(NAME    "I/slt-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slt-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/slt-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slt-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slt-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slt-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/slt-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slt-01/signature.test"
         )
set_tests_properties("I/slt-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/slti-01 ================================================
add_test(NAME    "I/slti-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slti-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/slti-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slti-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slti-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slti-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/slti-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/slti-01/signature.test"
         )
set_tests_properties("I/slti-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sltiu-01 ===============================================
add_test(NAME    "I/sltiu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltiu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sltiu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltiu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltiu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltiu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sltiu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltiu-01/signature.test"
         )
set_tests_properties("I/sltiu-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sltu-01 ================================================
add_test(NAME    "I/sltu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sltu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sltu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sltu-01/signature.test"
         )
set_tests_properties("I/sltu-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sra-01 =================================================
add_test(NAME    "I/sra-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sra-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sra-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sra-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sra-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sra-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sra-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sra-01/signature.test"
         )
set_tests_properties("I/sra-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/srai-01 ================================================
add_test(NAME    "I/srai-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srai-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/srai-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srai-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srai-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srai-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/srai-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srai-01/signature.test"
         )
set_tests_properties("I/srai-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sraiw-01 ===============================================
add_test(NAME    "I/sraiw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraiw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sraiw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraiw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraiw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraiw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sraiw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraiw-01/signature.test"
         )
set_tests_properties("I/sraiw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sraw-01 ================================================
add_test(NAME    "I/sraw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sraw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sraw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sraw-01/signature.test"
         )
set_tests_properties("I/sraw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/srl-01 =================================================
add_test(NAME    "I/srl-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srl-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/srl-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srl-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srl-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srl-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/srl-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srl-01/signature.test"
         )
set_tests_properties("I/srl-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/srli-01 ================================================
add_test(NAME    "I/srli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/srli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/srli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srli-01/signature.test"
         )
set_tests_properties("I/srli-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/srliw-01 ===============================================
add_test(NAME    "I/srliw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srliw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/srliw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srliw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srliw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srliw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/srliw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srliw-01/signature.test"
         )
set_tests_properties("I/srliw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/srlw-01 ================================================
add_test(NAME    "I/srlw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srlw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/srlw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srlw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srlw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srlw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/srlw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/srlw-01/signature.test"
         )
set_tests_properties("I/srlw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sub-01 =================================================
add_test(NAME    "I/sub-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sub-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sub-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sub-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sub-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sub-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sub-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sub-01/signature.test"
         )
set_tests_properties("I/sub-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/subw-01 ================================================
add_test(NAME    "I/subw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/subw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/subw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/subw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/subw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/subw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/subw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/subw-01/signature.test"
         )
set_tests_properties("I/subw-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/sw-align-01 ============================================
add_test(NAME    "I/sw-align-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sw-align-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/sw-align-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sw-align-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sw-align-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sw-align-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/sw-align-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/sw-align-01/signature.test"
         )
set_tests_properties("I/sw-align-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/xor-01 =================================================
add_test(NAME    "I/xor-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xor-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/xor-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xor-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xor-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xor-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/xor-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xor-01/signature.test"
         )
set_tests_properties("I/xor-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== I/xori-01 ================================================
add_test(NAME    "I/xori-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xori-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/I/src/xori-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xori-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xori-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xori-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/I/src/xori-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/I/xori-01/signature.test"
         )
set_tests_properties("I/xori-01" PROPERTIES LABELS "I")
#===============================================================================

#==================== K/aes64ds-01 =============================================
add_test(NAME    "K/aes64ds-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ds-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64ds-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ds-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ds-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ds-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64ds-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ds-01/signature.test"
         )
set_tests_properties("K/aes64ds-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64dsm-01 ============================================
add_test(NAME    "K/aes64dsm-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64dsm-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64dsm-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64dsm-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64dsm-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64dsm-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64dsm-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64dsm-01/signature.test"
         )
set_tests_properties("K/aes64dsm-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64es-01 =============================================
add_test(NAME    "K/aes64es-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64es-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64es-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64es-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64es-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64es-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64es-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64es-01/signature.test"
         )
set_tests_properties("K/aes64es-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64esm-01 ============================================
add_test(NAME    "K/aes64esm-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64esm-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64esm-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64esm-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64esm-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64esm-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64esm-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64esm-01/signature.test"
         )
set_tests_properties("K/aes64esm-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64im-01 =============================================
add_test(NAME    "K/aes64im-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64im-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64im-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64im-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64im-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64im-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64im-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64im-01/signature.test"
         )
set_tests_properties("K/aes64im-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64ks1i-01 ===========================================
add_test(NAME    "K/aes64ks1i-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks1i-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64ks1i-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks1i-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks1i-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks1i-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64ks1i-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks1i-01/signature.test"
         )
set_tests_properties("K/aes64ks1i-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/aes64ks2-01 ============================================
add_test(NAME    "K/aes64ks2-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks2-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/aes64ks2-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks2-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks2-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks2-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/aes64ks2-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/aes64ks2-01/signature.test"
         )
set_tests_properties("K/aes64ks2-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/brev8-01 ===============================================
add_test(NAME    "K/brev8-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/brev8-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/brev8-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/brev8-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/brev8-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/brev8-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/brev8-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/brev8-01/signature.test"
         )
set_tests_properties("K/brev8-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/pack-01 ================================================
add_test(NAME    "K/pack-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/pack-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/pack-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/pack-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/pack-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/pack-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/pack-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/pack-01/signature.test"
         )
set_tests_properties("K/pack-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/packh-01 ===============================================
add_test(NAME    "K/packh-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packh-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/packh-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packh-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packh-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packh-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/packh-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packh-01/signature.test"
         )
set_tests_properties("K/packh-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/packw-01 ===============================================
add_test(NAME    "K/packw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/packw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/packw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/packw-01/signature.test"
         )
set_tests_properties("K/packw-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha256sig0-01 ==========================================
add_test(NAME    "K/sha256sig0-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig0-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha256sig0-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig0-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig0-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig0-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha256sig0-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig0-01/signature.test"
         )
set_tests_properties("K/sha256sig0-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha256sig1-01 ==========================================
add_test(NAME    "K/sha256sig1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha256sig1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha256sig1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sig1-01/signature.test"
         )
set_tests_properties("K/sha256sig1-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha256sum0-01 ==========================================
add_test(NAME    "K/sha256sum0-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum0-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha256sum0-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum0-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum0-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum0-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha256sum0-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum0-01/signature.test"
         )
set_tests_properties("K/sha256sum0-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha256sum1-01 ==========================================
add_test(NAME    "K/sha256sum1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha256sum1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha256sum1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha256sum1-01/signature.test"
         )
set_tests_properties("K/sha256sum1-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha512sig0-01 ==========================================
add_test(NAME    "K/sha512sig0-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig0-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha512sig0-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig0-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig0-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig0-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha512sig0-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig0-01/signature.test"
         )
set_tests_properties("K/sha512sig0-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha512sig1-01 ==========================================
add_test(NAME    "K/sha512sig1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha512sig1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha512sig1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sig1-01/signature.test"
         )
set_tests_properties("K/sha512sig1-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha512sum0-01 ==========================================
add_test(NAME    "K/sha512sum0-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum0-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha512sum0-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum0-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum0-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum0-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha512sum0-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum0-01/signature.test"
         )
set_tests_properties("K/sha512sum0-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/sha512sum1-01 ==========================================
add_test(NAME    "K/sha512sum1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/sha512sum1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/sha512sum1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/sha512sum1-01/signature.test"
         )
set_tests_properties("K/sha512sum1-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/xperm4-01 ==============================================
add_test(NAME    "K/xperm4-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm4-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/xperm4-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm4-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm4-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm4-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/xperm4-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm4-01/signature.test"
         )
set_tests_properties("K/xperm4-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== K/xperm8-01 ==============================================
add_test(NAME    "K/xperm8-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm8-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/K/src/xperm8-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm8-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm8-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm8-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/K/src/xperm8-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/K/xperm8-01/signature.test"
         )
set_tests_properties("K/xperm8-01" PROPERTIES LABELS "K")
#===============================================================================

#==================== M/div-01 =================================================
add_test(NAME    "M/div-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/div-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/div-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/div-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/div-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/div-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/div-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/div-01/signature.test"
         )
set_tests_properties("M/div-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/divu-01 ================================================
add_test(NAME    "M/divu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/divu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/divu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divu-01/signature.test"
         )
set_tests_properties("M/divu-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/divuw-01 ===============================================
add_test(NAME    "M/divuw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divuw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/divuw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divuw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divuw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divuw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/divuw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divuw-01/signature.test"
         )
set_tests_properties("M/divuw-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/divw-01 ================================================
add_test(NAME    "M/divw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/divw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/divw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/divw-01/signature.test"
         )
set_tests_properties("M/divw-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/mul-01 =================================================
add_test(NAME    "M/mul-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mul-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/mul-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mul-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mul-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mul-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/mul-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mul-01/signature.test"
         )
set_tests_properties("M/mul-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/mulh-01 ================================================
add_test(NAME    "M/mulh-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulh-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/mulh-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulh-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulh-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulh-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/mulh-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulh-01/signature.test"
         )
set_tests_properties("M/mulh-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/mulhsu-01 ==============================================
add_test(NAME    "M/mulhsu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhsu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/mulhsu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhsu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhsu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhsu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/mulhsu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhsu-01/signature.test"
         )
set_tests_properties("M/mulhsu-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/mulhu-01 ===============================================
add_test(NAME    "M/mulhu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/mulhu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/mulhu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulhu-01/signature.test"
         )
set_tests_properties("M/mulhu-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/mulw-01 ================================================
add_test(NAME    "M/mulw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/mulw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/mulw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/mulw-01/signature.test"
         )
set_tests_properties("M/mulw-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/rem-01 =================================================
add_test(NAME    "M/rem-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/rem-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/rem-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/rem-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/rem-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/rem-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/rem-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/rem-01/signature.test"
         )
set_tests_properties("M/rem-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/remu-01 ================================================
add_test(NAME    "M/remu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/remu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/remu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remu-01/signature.test"
         )
set_tests_properties("M/remu-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/remuw-01 ===============================================
add_test(NAME    "M/remuw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remuw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/remuw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remuw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remuw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remuw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/remuw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remuw-01/signature.test"
         )
set_tests_properties("M/remuw-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== M/remw-01 ================================================
add_test(NAME    "M/remw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/M/src/remw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/M/src/remw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/M/remw-01/signature.test"
         )
set_tests_properties("M/remw-01" PROPERTIES LABELS "M")
#===============================================================================

#==================== Zfh/fcvt.h.l_b25-01 ======================================
add_test(NAME    "Zfh/fcvt.h.l_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.l_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.l_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b25-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.h.l_b25-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.h.l_b26-01 ======================================
add_test(NAME    "Zfh/fcvt.h.l_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.l_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.l_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.l_b26-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.h.l_b26-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.h.lu_b25-01 =====================================
add_test(NAME    "Zfh/fcvt.h.lu_b25-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b25-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.lu_b25-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b25-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b25-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b25-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.lu_b25-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b25-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.h.lu_b25-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.h.lu_b26-01 =====================================
add_test(NAME    "Zfh/fcvt.h.lu_b26-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b26-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.lu_b26-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b26-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b26-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b26-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.h.lu_b26-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.h.lu_b26-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.h.lu_b26-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b1-01 =======================================
add_test(NAME    "Zfh/fcvt.l.h_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b1-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b1-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b22-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b22-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b22-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b23-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b23-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b23-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b24-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b24-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b24-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b27-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b27-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b27-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b28-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b28-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b28-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.l.h_b29-01 ======================================
add_test(NAME    "Zfh/fcvt.l.h_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.l.h_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.l.h_b29-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.l.h_b29-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b1-01 ======================================
add_test(NAME    "Zfh/fcvt.lu.h_b1-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b1-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b1-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b1-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b1-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b1-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b1-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b1-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b1-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b22-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b22-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b22-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b22-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b22-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b22-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b22-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b22-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b22-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b22-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b23-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b23-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b23-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b23-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b23-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b23-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b23-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b23-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b23-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b23-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b24-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b24-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b24-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b24-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b24-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b24-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b24-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b24-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b24-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b24-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b27-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b27-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b27-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b27-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b27-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b27-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b27-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b27-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b27-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b27-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b28-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b28-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b28-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b28-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b28-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b28-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b28-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b28-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b28-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b28-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zfh/fcvt.lu.h_b29-01 =====================================
add_test(NAME    "Zfh/fcvt.lu.h_b29-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b29-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b29-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b29-01/test.elf -DTEST_CASE_1=True -DXLEN=64 -DFLEN=32 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b29-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b29-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zfh/src/fcvt.lu.h_b29-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zfh/fcvt.lu.h_b29-01/signature.test"
         )
set_tests_properties("Zfh/fcvt.lu.h_b29-01" PROPERTIES LABELS "Zfh")
#===============================================================================

#==================== Zifencei/Fencei ==========================================
add_test(NAME    "Zifencei/Fencei"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zifencei/Fencei;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zifencei/src/Fencei.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zifencei/Fencei/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zifencei/Fencei/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zifencei/Fencei/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zifencei/src/Fencei.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zifencei/Fencei/signature.test"
         )
set_tests_properties("Zifencei/Fencei" PROPERTIES LABELS "Zifencei")
#===============================================================================

#==================== Zvk/vandn.vv-01 ==========================================
add_test(NAME    "Zvk/vandn.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vandn.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vandn.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vv-01/signature.test"
         )
set_tests_properties("Zvk/vandn.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vandn.vx-01 ==========================================
add_test(NAME    "Zvk/vandn.vx-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vx-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vandn.vx-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vx-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vx-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vx-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vandn.vx-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vandn.vx-01/signature.test"
         )
set_tests_properties("Zvk/vandn.vx-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vbrev8.v-01 ==========================================
add_test(NAME    "Zvk/vbrev8.v-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vbrev8.v-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vbrev8.v-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vbrev8.v-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vbrev8.v-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vbrev8.v-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vbrev8.v-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vbrev8.v-01/signature.test"
         )
set_tests_properties("Zvk/vbrev8.v-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vghsh.vv-01 ==========================================
add_test(NAME    "Zvk/vghsh.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vghsh.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vghsh.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vghsh.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vghsh.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vghsh.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vghsh.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vghsh.vv-01/signature.test"
         )
set_tests_properties("Zvk/vghsh.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vgmul.vv-01 ==========================================
add_test(NAME    "Zvk/vgmul.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vgmul.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vgmul.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vgmul.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vgmul.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vgmul.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vgmul.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vgmul.vv-01/signature.test"
         )
set_tests_properties("Zvk/vgmul.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vrev8.v-01 ===========================================
add_test(NAME    "Zvk/vrev8.v-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrev8.v-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vrev8.v-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrev8.v-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrev8.v-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrev8.v-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vrev8.v-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrev8.v-01/signature.test"
         )
set_tests_properties("Zvk/vrev8.v-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vrol.vv-01 ===========================================
add_test(NAME    "Zvk/vrol.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vrol.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vrol.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vv-01/signature.test"
         )
set_tests_properties("Zvk/vrol.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vrol.vx-01 ===========================================
add_test(NAME    "Zvk/vrol.vx-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vx-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vrol.vx-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vx-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vx-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vx-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vrol.vx-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vrol.vx-01/signature.test"
         )
set_tests_properties("Zvk/vrol.vx-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vror.vi-01 ===========================================
add_test(NAME    "Zvk/vror.vi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vi-01/signature.test"
         )
set_tests_properties("Zvk/vror.vi-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vror.vv-01 ===========================================
add_test(NAME    "Zvk/vror.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vv-01/signature.test"
         )
set_tests_properties("Zvk/vror.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vror.vx-01 ===========================================
add_test(NAME    "Zvk/vror.vx-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vx-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vx-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vx-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vx-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vx-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vror.vx-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vror.vx-01/signature.test"
         )
set_tests_properties("Zvk/vror.vx-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2ch-e32.vv-01 ====================================
add_test(NAME    "Zvk/vsha2ch-e32.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e32.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ch-e32.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e32.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e32.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e32.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ch-e32.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e32.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2ch-e32.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2ch-e64.vv-01 ====================================
add_test(NAME    "Zvk/vsha2ch-e64.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e64.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ch-e64.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e64.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e64.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e64.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ch-e64.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ch-e64.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2ch-e64.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2cl-e32.vv-01 ====================================
add_test(NAME    "Zvk/vsha2cl-e32.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e32.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2cl-e32.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e32.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e32.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e32.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2cl-e32.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e32.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2cl-e32.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2cl-e64.vv-01 ====================================
add_test(NAME    "Zvk/vsha2cl-e64.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e64.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2cl-e64.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e64.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e64.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e64.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2cl-e64.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2cl-e64.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2cl-e64.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2ms-e32.vv-01 ====================================
add_test(NAME    "Zvk/vsha2ms-e32.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e32.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ms-e32.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e32.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e32.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e32.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ms-e32.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e32.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2ms-e32.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== Zvk/vsha2ms-e64.vv-01 ====================================
add_test(NAME    "Zvk/vsha2ms-e64.vv-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e64.vv-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ms-e64.vv-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e64.vv-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e64.vv-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e64.vv-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/Zvk/src/vsha2ms-e64.vv-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/Zvk/vsha2ms-e64.vv-01/signature.test"
         )
set_tests_properties("Zvk/vsha2ms-e64.vv-01" PROPERTIES LABELS "Zvk")
#===============================================================================

#==================== hints/add-01 =============================================
add_test(NAME    "hints/add-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/add-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/add-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/add-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/add-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/add-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/add-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/add-01/signature.test"
         )
set_tests_properties("hints/add-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/addi-01 ============================================
add_test(NAME    "hints/addi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/addi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/addi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addi-01/signature.test"
         )
set_tests_properties("hints/addi-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/addiw-01 ===========================================
add_test(NAME    "hints/addiw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addiw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/addiw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addiw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addiw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addiw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/addiw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addiw-01/signature.test"
         )
set_tests_properties("hints/addiw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/addw-01 ============================================
add_test(NAME    "hints/addw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/addw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/addw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/addw-01/signature.test"
         )
set_tests_properties("hints/addw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/and-01 =============================================
add_test(NAME    "hints/and-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/and-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/and-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/and-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/and-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/and-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/and-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/and-01/signature.test"
         )
set_tests_properties("hints/and-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/andi-01 ============================================
add_test(NAME    "hints/andi-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/andi-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/andi-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/andi-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/andi-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/andi-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/andi-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/andi-01/signature.test"
         )
set_tests_properties("hints/andi-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/auipc-01 ===========================================
add_test(NAME    "hints/auipc-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/auipc-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/auipc-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/auipc-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/auipc-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/auipc-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/auipc-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/auipc-01/signature.test"
         )
set_tests_properties("hints/auipc-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/fence-01 ===========================================
add_test(NAME    "hints/fence-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/fence-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/fence-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/fence-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/fence-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/fence-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/fence-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/fence-01/signature.test"
         )
set_tests_properties("hints/fence-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/lui-01 =============================================
add_test(NAME    "hints/lui-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/lui-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/lui-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/lui-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/lui-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/lui-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/lui-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/lui-01/signature.test"
         )
set_tests_properties("hints/lui-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/or-01 ==============================================
add_test(NAME    "hints/or-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/or-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/or-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/or-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/or-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/or-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/or-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/or-01/signature.test"
         )
set_tests_properties("hints/or-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/ori-01 =============================================
add_test(NAME    "hints/ori-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/ori-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/ori-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/ori-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/ori-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/ori-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/ori-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/ori-01/signature.test"
         )
set_tests_properties("hints/ori-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sll-01 =============================================
add_test(NAME    "hints/sll-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sll-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sll-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sll-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sll-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sll-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sll-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sll-01/signature.test"
         )
set_tests_properties("hints/sll-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/slli-01 ============================================
add_test(NAME    "hints/slli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/slli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/slli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slli-01/signature.test"
         )
set_tests_properties("hints/slli-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/slliw-01 ===========================================
add_test(NAME    "hints/slliw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slliw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/slliw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slliw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slliw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slliw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/slliw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slliw-01/signature.test"
         )
set_tests_properties("hints/slliw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sllw-01 ============================================
add_test(NAME    "hints/sllw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sllw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sllw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sllw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sllw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sllw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sllw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sllw-01/signature.test"
         )
set_tests_properties("hints/sllw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/slt-01 =============================================
add_test(NAME    "hints/slt-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slt-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/slt-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slt-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slt-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slt-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/slt-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slt-01/signature.test"
         )
set_tests_properties("hints/slt-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/slti-01 ============================================
add_test(NAME    "hints/slti-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slti-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/slti-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slti-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slti-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slti-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/slti-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/slti-01/signature.test"
         )
set_tests_properties("hints/slti-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sltiu-01 ===========================================
add_test(NAME    "hints/sltiu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltiu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sltiu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltiu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltiu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltiu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sltiu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltiu-01/signature.test"
         )
set_tests_properties("hints/sltiu-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sltu-01 ============================================
add_test(NAME    "hints/sltu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sltu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltu-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sltu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sltu-01/signature.test"
         )
set_tests_properties("hints/sltu-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sra-01 =============================================
add_test(NAME    "hints/sra-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sra-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sra-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sra-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sra-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sra-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sra-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sra-01/signature.test"
         )
set_tests_properties("hints/sra-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/srai-01 ============================================
add_test(NAME    "hints/srai-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srai-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/srai-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srai-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srai-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srai-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/srai-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srai-01/signature.test"
         )
set_tests_properties("hints/srai-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sraiw-01 ===========================================
add_test(NAME    "hints/sraiw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraiw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sraiw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraiw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraiw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraiw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sraiw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraiw-01/signature.test"
         )
set_tests_properties("hints/sraiw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sraw-01 ============================================
add_test(NAME    "hints/sraw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sraw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sraw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sraw-01/signature.test"
         )
set_tests_properties("hints/sraw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/srl-01 =============================================
add_test(NAME    "hints/srl-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srl-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/srl-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srl-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srl-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srl-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/srl-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srl-01/signature.test"
         )
set_tests_properties("hints/srl-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/srli-01 ============================================
add_test(NAME    "hints/srli-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srli-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/srli-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srli-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srli-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srli-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/srli-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srli-01/signature.test"
         )
set_tests_properties("hints/srli-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/srliw-01 ===========================================
add_test(NAME    "hints/srliw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srliw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/srliw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srliw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srliw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srliw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/srliw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srliw-01/signature.test"
         )
set_tests_properties("hints/srliw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/srlw-01 ============================================
add_test(NAME    "hints/srlw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srlw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/srlw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srlw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srlw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srlw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/srlw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/srlw-01/signature.test"
         )
set_tests_properties("hints/srlw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/sub-01 =============================================
add_test(NAME    "hints/sub-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sub-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/sub-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sub-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sub-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sub-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/sub-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/sub-01/signature.test"
         )
set_tests_properties("hints/sub-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/subw-01 ============================================
add_test(NAME    "hints/subw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/subw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/subw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/subw-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/subw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/subw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/subw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/subw-01/signature.test"
         )
set_tests_properties("hints/subw-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/xor-01 =============================================
add_test(NAME    "hints/xor-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xor-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/xor-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xor-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xor-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xor-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/xor-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xor-01/signature.test"
         )
set_tests_properties("hints/xor-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== hints/xori-01 ============================================
add_test(NAME    "hints/xori-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xori-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/hints/src/xori-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xori-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xori-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xori-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/hints/src/xori-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/hints/xori-01/signature.test"
         )
set_tests_properties("hints/xori-01" PROPERTIES LABELS "hints")
#===============================================================================

#==================== pmp/pmpzicbo_prefetch ====================================
add_test(NAME    "pmp/pmpzicbo_prefetch"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/pmp/pmpzicbo_prefetch;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/pmp/src/pmpzicbo_prefetch.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/pmp/pmpzicbo_prefetch/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/pmp/pmpzicbo_prefetch/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/pmp/pmpzicbo_prefetch/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/pmp/src/pmpzicbo_prefetch.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/pmp/pmpzicbo_prefetch/signature.test"
         )
set_tests_properties("pmp/pmpzicbo_prefetch" PROPERTIES LABELS "pmp")
#===============================================================================

#==================== privilege/ebreak =========================================
add_test(NAME    "privilege/ebreak"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ebreak;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/ebreak.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ebreak/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ebreak/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ebreak/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/ebreak.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ebreak/signature.test"
         )
set_tests_properties("privilege/ebreak" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/ecall ==========================================
add_test(NAME    "privilege/ecall"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ecall;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/ecall.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ecall/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ecall/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ecall/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/ecall.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/ecall/signature.test"
         )
set_tests_properties("privilege/ecall" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-beq-01 ================================
add_test(NAME    "privilege/misalign-beq-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-beq-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-beq-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-beq-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-beq-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-beq-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-beq-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-beq-01/signature.test"
         )
set_tests_properties("privilege/misalign-beq-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-bge-01 ================================
add_test(NAME    "privilege/misalign-bge-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bge-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bge-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bge-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bge-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bge-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bge-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bge-01/signature.test"
         )
set_tests_properties("privilege/misalign-bge-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-bgeu-01 ===============================
add_test(NAME    "privilege/misalign-bgeu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bgeu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bgeu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bgeu-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bgeu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bgeu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bgeu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bgeu-01/signature.test"
         )
set_tests_properties("privilege/misalign-bgeu-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-blt-01 ================================
add_test(NAME    "privilege/misalign-blt-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-blt-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-blt-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-blt-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-blt-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-blt-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-blt-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-blt-01/signature.test"
         )
set_tests_properties("privilege/misalign-blt-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-bltu-01 ===============================
add_test(NAME    "privilege/misalign-bltu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bltu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bltu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bltu-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bltu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bltu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bltu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bltu-01/signature.test"
         )
set_tests_properties("privilege/misalign-bltu-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-bne-01 ================================
add_test(NAME    "privilege/misalign-bne-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bne-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bne-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bne-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bne-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bne-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-bne-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-bne-01/signature.test"
         )
set_tests_properties("privilege/misalign-bne-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-jal-01 ================================
add_test(NAME    "privilege/misalign-jal-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-jal-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-jal-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-jal-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-jal-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-jal-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-jal-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-jal-01/signature.test"
         )
set_tests_properties("privilege/misalign-jal-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-ld-01 =================================
add_test(NAME    "privilege/misalign-ld-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-ld-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-ld-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-ld-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-ld-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-ld-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-ld-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-ld-01/signature.test"
         )
set_tests_properties("privilege/misalign-ld-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-lh-01 =================================
add_test(NAME    "privilege/misalign-lh-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lh-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lh-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lh-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lh-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lh-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lh-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lh-01/signature.test"
         )
set_tests_properties("privilege/misalign-lh-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-lhu-01 ================================
add_test(NAME    "privilege/misalign-lhu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lhu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lhu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lhu-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lhu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lhu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lhu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lhu-01/signature.test"
         )
set_tests_properties("privilege/misalign-lhu-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-lw-01 =================================
add_test(NAME    "privilege/misalign-lw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lw-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lw-01/signature.test"
         )
set_tests_properties("privilege/misalign-lw-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-lwu-01 ================================
add_test(NAME    "privilege/misalign-lwu-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lwu-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lwu-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lwu-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lwu-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lwu-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-lwu-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-lwu-01/signature.test"
         )
set_tests_properties("privilege/misalign-lwu-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-sd-01 =================================
add_test(NAME    "privilege/misalign-sd-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sd-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sd-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sd-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sd-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sd-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sd-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sd-01/signature.test"
         )
set_tests_properties("privilege/misalign-sd-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-sh-01 =================================
add_test(NAME    "privilege/misalign-sh-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sh-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sh-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sh-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sh-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sh-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sh-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sh-01/signature.test"
         )
set_tests_properties("privilege/misalign-sh-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign-sw-01 =================================
add_test(NAME    "privilege/misalign-sw-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sw-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sw-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sw-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sw-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sw-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign-sw-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign-sw-01/signature.test"
         )
set_tests_properties("privilege/misalign-sw-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign1-cjalr-01 =============================
add_test(NAME    "privilege/misalign1-cjalr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjalr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-cjalr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjalr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjalr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjalr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-cjalr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjalr-01/signature.test"
         )
set_tests_properties("privilege/misalign1-cjalr-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign1-cjr-01 ===============================
add_test(NAME    "privilege/misalign1-cjr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-cjr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-cjr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-cjr-01/signature.test"
         )
set_tests_properties("privilege/misalign1-cjr-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign1-jalr-01 ==============================
add_test(NAME    "privilege/misalign1-jalr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-jalr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-jalr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-jalr-01/test.elf -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-jalr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-jalr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign1-jalr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign1-jalr-01/signature.test"
         )
set_tests_properties("privilege/misalign1-jalr-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== privilege/misalign2-jalr-01 ==============================
add_test(NAME    "privilege/misalign2-jalr-01"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign2-jalr-01;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/privilege/src/misalign2-jalr-01.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign2-jalr-01/test.elf -Drvtest_mtrap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign2-jalr-01/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign2-jalr-01/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/privilege/src/misalign2-jalr-01.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/privilege/misalign2-jalr-01/signature.test"
         )
set_tests_properties("privilege/misalign2-jalr-01" PROPERTIES LABELS "privilege")
#===============================================================================

#==================== vm_sv39/vm_A_and_D_S_mode ================================
add_test(NAME    "vm_sv39/vm_A_and_D_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_A_and_D_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_A_and_D_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_A_and_D_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_A_and_D_U_mode ================================
add_test(NAME    "vm_sv39/vm_A_and_D_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_A_and_D_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_A_and_D_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_A_and_D_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_A_and_D_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_VA_all_ones_S_mode ============================
add_test(NAME    "vm_sv39/vm_VA_all_ones_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_ones_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_VA_all_ones_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_ones_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_ones_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_ones_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_VA_all_ones_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_ones_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_VA_all_ones_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_VA_all_zeros_S_mode ===========================
add_test(NAME    "vm_sv39/vm_VA_all_zeros_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_zeros_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_VA_all_zeros_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_zeros_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_zeros_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_zeros_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_VA_all_zeros_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_VA_all_zeros_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_VA_all_zeros_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_canonical_S_mode ==============================
add_test(NAME    "vm_sv39/vm_canonical_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_canonical_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_canonical_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_canonical_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_canonical_U_mode ==============================
add_test(NAME    "vm_sv39/vm_canonical_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_canonical_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_canonical_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_canonical_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_canonical_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_invalid_pte_S_mode ============================
add_test(NAME    "vm_sv39/vm_invalid_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_invalid_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_invalid_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_invalid_pte_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_invalid_pte_U_mode ============================
add_test(NAME    "vm_sv39/vm_invalid_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_invalid_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_invalid_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_invalid_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_invalid_pte_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_misaligned_S_mode =============================
add_test(NAME    "vm_sv39/vm_misaligned_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_misaligned_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_misaligned_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_misaligned_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_misaligned_U_mode =============================
add_test(NAME    "vm_sv39/vm_misaligned_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_misaligned_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_misaligned_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_misaligned_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_misaligned_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mprv_S_mode ===================================
add_test(NAME    "vm_sv39/vm_mprv_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mprv_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mprv_U_mode ===================================
add_test(NAME    "vm_sv39/vm_mprv_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mprv_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mprv_U_set_sum_set_S_mode =====================
add_test(NAME    "vm_sv39/vm_mprv_U_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mprv_U_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mprv_U_set_sum_unset_S_mode ===================
add_test(NAME    "vm_sv39/vm_mprv_U_set_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_set_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_U_set_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_U_set_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mprv_U_set_sum_unset_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mprv_bare_mode ================================
add_test(NAME    "vm_sv39/vm_mprv_bare_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_bare_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_bare_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_bare_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_bare_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_bare_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mprv_bare_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mprv_bare_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mprv_bare_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mstatus_sbe_set_S_mode ========================
add_test(NAME    "vm_sv39/vm_mstatus_sbe_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_sbe_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_sbe_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mstatus_sbe_set_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode ================
add_test(NAME    "vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_sbe_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_sbe_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mstatus_sbe_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mstatus_tvm_test ==============================
add_test(NAME    "vm_sv39/vm_mstatus_tvm_test"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_tvm_test;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_tvm_test.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_tvm_test/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_tvm_test/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_tvm_test/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mstatus_tvm_test.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mstatus_tvm_test/signature.test"
         )
set_tests_properties("vm_sv39/vm_mstatus_tvm_test" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mxr_S_mode ====================================
add_test(NAME    "vm_sv39/vm_mxr_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mxr_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mxr_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mxr_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_mxr_U_mode ====================================
add_test(NAME    "vm_sv39/vm_mxr_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mxr_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_mxr_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_mxr_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_mxr_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_nleaf_pte_level0_S_mode =======================
add_test(NAME    "vm_sv39/vm_nleaf_pte_level0_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_nleaf_pte_level0_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_nleaf_pte_level0_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_nleaf_pte_level0_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_nleaf_pte_level0_U_mode =======================
add_test(NAME    "vm_sv39/vm_nleaf_pte_level0_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_nleaf_pte_level0_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_nleaf_pte_level0_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_nleaf_pte_level0_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_nleaf_pte_level0_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_pte_reserved_field_S_mode =====================
add_test(NAME    "vm_sv39/vm_pte_reserved_field_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_pte_reserved_field_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_pte_reserved_field_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_pte_reserved_field_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_pte_reserved_field_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_pte_reserved_field_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_pte_reserved_field_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_pte_reserved_field_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_pte_reserved_field_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_res_global_pte_S_mode =========================
add_test(NAME    "vm_sv39/vm_res_global_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_res_global_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_res_global_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_res_global_pte_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_res_global_pte_U_mode =========================
add_test(NAME    "vm_sv39/vm_res_global_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_res_global_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_res_global_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_res_global_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_res_global_pte_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_rsw_pte_S_mode =======================
add_test(NAME    "vm_sv39/vm_reserved_rsw_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rsw_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rsw_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_rsw_pte_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_rsw_pte_U_mode =======================
add_test(NAME    "vm_sv39/vm_reserved_rsw_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rsw_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rsw_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rsw_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_rsw_pte_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_rwx_pte_S_mode =======================
add_test(NAME    "vm_sv39/vm_reserved_rwx_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rwx_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rwx_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_rwx_pte_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_rwx_pte_U_mode =======================
add_test(NAME    "vm_sv39/vm_reserved_rwx_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rwx_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_rwx_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_rwx_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_rwx_pte_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_svnapot_S_mode =======================
add_test(NAME    "vm_sv39/vm_reserved_svnapot_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svnapot_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_svnapot_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svnapot_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svnapot_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svnapot_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_svnapot_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svnapot_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_svnapot_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_reserved_svpbmt_S_mode ========================
add_test(NAME    "vm_sv39/vm_reserved_svpbmt_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svpbmt_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_svpbmt_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svpbmt_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svpbmt_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svpbmt_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_reserved_svpbmt_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_reserved_svpbmt_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_reserved_svpbmt_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_satp_access_tests =============================
add_test(NAME    "vm_sv39/vm_satp_access_tests"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_satp_access_tests;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_satp_access_tests.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_satp_access_tests/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_satp_access_tests/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_satp_access_tests/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_satp_access_tests.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_satp_access_tests/signature.test"
         )
set_tests_properties("vm_sv39/vm_satp_access_tests" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_spage_access_U_mode ===========================
add_test(NAME    "vm_sv39/vm_spage_access_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_spage_access_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_spage_access_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_spage_access_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_spage_access_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_spage_access_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_spage_access_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_spage_access_U_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_spage_access_U_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_sum_set_S_mode ================================
add_test(NAME    "vm_sv39/vm_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_sum_set_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_sum_set_U_bit_unset_S_mode ====================
add_test(NAME    "vm_sv39/vm_sum_set_U_bit_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_U_bit_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_set_U_bit_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_U_bit_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_U_bit_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_U_bit_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_set_U_bit_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_set_U_bit_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_sum_set_U_bit_unset_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv39/vm_sum_unset_S_mode ==============================
add_test(NAME    "vm_sv39/vm_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv39/src/vm_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv39/vm_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv39/vm_sum_unset_S_mode" PROPERTIES LABELS "vm_sv39")
#===============================================================================

#==================== vm_sv48/sv48_A_and_D_S_mode ==============================
add_test(NAME    "vm_sv48/sv48_A_and_D_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_A_and_D_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_A_and_D_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_A_and_D_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_A_and_D_U_mode ==============================
add_test(NAME    "vm_sv48/sv48_A_and_D_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_A_and_D_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_A_and_D_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_A_and_D_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_A_and_D_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_VA_all_ones_S_mode ==========================
add_test(NAME    "vm_sv48/sv48_VA_all_ones_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_ones_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_VA_all_ones_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_ones_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_ones_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_ones_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_VA_all_ones_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_ones_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_VA_all_ones_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_VA_all_zeros_S_mode =========================
add_test(NAME    "vm_sv48/sv48_VA_all_zeros_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_zeros_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_VA_all_zeros_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_zeros_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_zeros_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_zeros_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_VA_all_zeros_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_VA_all_zeros_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_VA_all_zeros_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_canonical_S_mode ============================
add_test(NAME    "vm_sv48/sv48_canonical_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_canonical_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_canonical_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_canonical_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_canonical_U_mode ============================
add_test(NAME    "vm_sv48/sv48_canonical_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_canonical_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_canonical_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_canonical_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_canonical_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_invalid_pte_S_mode ==========================
add_test(NAME    "vm_sv48/sv48_invalid_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_invalid_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_invalid_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_invalid_pte_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_invalid_pte_U_mode ==========================
add_test(NAME    "vm_sv48/sv48_invalid_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_invalid_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_invalid_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_invalid_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_invalid_pte_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_misaligned_S_mode ===========================
add_test(NAME    "vm_sv48/sv48_misaligned_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_misaligned_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_misaligned_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_misaligned_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_misaligned_U_mode ===========================
add_test(NAME    "vm_sv48/sv48_misaligned_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_misaligned_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_misaligned_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_misaligned_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_misaligned_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mprv_S_mode =================================
add_test(NAME    "vm_sv48/sv48_mprv_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mprv_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mprv_U_mode =================================
add_test(NAME    "vm_sv48/sv48_mprv_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mprv_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mprv_U_set_sum_set_S_mode ===================
add_test(NAME    "vm_sv48/sv48_mprv_U_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mprv_U_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mprv_U_set_sum_unset_S_mode =================
add_test(NAME    "vm_sv48/sv48_mprv_U_set_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_set_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_U_set_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_U_set_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mprv_U_set_sum_unset_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mprv_bare_mode ==============================
add_test(NAME    "vm_sv48/sv48_mprv_bare_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_bare_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_bare_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_bare_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_bare_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_bare_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mprv_bare_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mprv_bare_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mprv_bare_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mstatus_sbe_set_S_mode ======================
add_test(NAME    "vm_sv48/sv48_mstatus_sbe_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_sbe_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_sbe_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mstatus_sbe_set_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode ==============
add_test(NAME    "vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_sbe_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_sbe_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mstatus_sbe_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mstatus_tvm_test ============================
add_test(NAME    "vm_sv48/sv48_mstatus_tvm_test"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_tvm_test;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_tvm_test.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_tvm_test/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_tvm_test/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_tvm_test/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mstatus_tvm_test.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mstatus_tvm_test/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mstatus_tvm_test" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mxr_S_mode ==================================
add_test(NAME    "vm_sv48/sv48_mxr_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mxr_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mxr_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mxr_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_mxr_U_mode ==================================
add_test(NAME    "vm_sv48/sv48_mxr_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mxr_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_mxr_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_mxr_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_mxr_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_nleaf_pte_level0_S_mode =====================
add_test(NAME    "vm_sv48/sv48_nleaf_pte_level0_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_nleaf_pte_level0_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_nleaf_pte_level0_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_nleaf_pte_level0_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_nleaf_pte_level0_U_mode =====================
add_test(NAME    "vm_sv48/sv48_nleaf_pte_level0_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_nleaf_pte_level0_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_nleaf_pte_level0_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_nleaf_pte_level0_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_nleaf_pte_level0_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_pte_reserved_field_S_mode ===================
add_test(NAME    "vm_sv48/sv48_pte_reserved_field_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_pte_reserved_field_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_pte_reserved_field_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_pte_reserved_field_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_pte_reserved_field_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_pte_reserved_field_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_pte_reserved_field_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_pte_reserved_field_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_pte_reserved_field_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_res_global_pte_S_mode =======================
add_test(NAME    "vm_sv48/sv48_res_global_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_res_global_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_res_global_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_res_global_pte_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_res_global_pte_U_mode =======================
add_test(NAME    "vm_sv48/sv48_res_global_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_res_global_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_res_global_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_res_global_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_res_global_pte_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_rsw_pte_S_mode =====================
add_test(NAME    "vm_sv48/sv48_reserved_rsw_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rsw_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rsw_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_rsw_pte_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_rsw_pte_U_mode =====================
add_test(NAME    "vm_sv48/sv48_reserved_rsw_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rsw_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rsw_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rsw_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_rsw_pte_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_rwx_pte_S_mode =====================
add_test(NAME    "vm_sv48/sv48_reserved_rwx_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rwx_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rwx_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_rwx_pte_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_rwx_pte_U_mode =====================
add_test(NAME    "vm_sv48/sv48_reserved_rwx_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rwx_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_rwx_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_rwx_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_rwx_pte_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_svnapot_S_mode =====================
add_test(NAME    "vm_sv48/sv48_reserved_svnapot_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svnapot_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_svnapot_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svnapot_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svnapot_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svnapot_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_svnapot_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svnapot_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_svnapot_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_reserved_svpbmt_S_mode ======================
add_test(NAME    "vm_sv48/sv48_reserved_svpbmt_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svpbmt_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_svpbmt_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svpbmt_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svpbmt_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svpbmt_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_reserved_svpbmt_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_reserved_svpbmt_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_reserved_svpbmt_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_satp_access_tests ===========================
add_test(NAME    "vm_sv48/sv48_satp_access_tests"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_satp_access_tests;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_satp_access_tests.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_satp_access_tests/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_satp_access_tests/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_satp_access_tests/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_satp_access_tests.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_satp_access_tests/signature.test"
         )
set_tests_properties("vm_sv48/sv48_satp_access_tests" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_spage_access_U_mode =========================
add_test(NAME    "vm_sv48/sv48_spage_access_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_spage_access_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_spage_access_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_spage_access_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_spage_access_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_spage_access_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_spage_access_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_spage_access_U_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_spage_access_U_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_sum_set_S_mode ==============================
add_test(NAME    "vm_sv48/sv48_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_sum_set_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_sum_set_U_bit_unset_S_mode ==================
add_test(NAME    "vm_sv48/sv48_sum_set_U_bit_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_U_bit_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_set_U_bit_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_U_bit_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_U_bit_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_U_bit_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_set_U_bit_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_set_U_bit_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_sum_set_U_bit_unset_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv48/sv48_sum_unset_S_mode ============================
add_test(NAME    "vm_sv48/sv48_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv48/src/sv48_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv48/sv48_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv48/sv48_sum_unset_S_mode" PROPERTIES LABELS "vm_sv48")
#===============================================================================

#==================== vm_sv57/sv57_A_and_D_S_mode ==============================
add_test(NAME    "vm_sv57/sv57_A_and_D_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_A_and_D_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_A_and_D_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_A_and_D_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_A_and_D_U_mode ==============================
add_test(NAME    "vm_sv57/sv57_A_and_D_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_A_and_D_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_A_and_D_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_A_and_D_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_A_and_D_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_VA_all_ones_S_mode ==========================
add_test(NAME    "vm_sv57/sv57_VA_all_ones_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_ones_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_VA_all_ones_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_ones_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_ones_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_ones_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_VA_all_ones_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_ones_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_VA_all_ones_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_VA_all_zeros_S_mode =========================
add_test(NAME    "vm_sv57/sv57_VA_all_zeros_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_zeros_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_VA_all_zeros_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_zeros_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_zeros_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_zeros_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_VA_all_zeros_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_VA_all_zeros_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_VA_all_zeros_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_canonical_S_mode ============================
add_test(NAME    "vm_sv57/sv57_canonical_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_canonical_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_canonical_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_canonical_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_canonical_U_mode ============================
add_test(NAME    "vm_sv57/sv57_canonical_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_canonical_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_canonical_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_canonical_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_canonical_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_global_pte_S_mode ===========================
add_test(NAME    "vm_sv57/sv57_global_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_global_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_global_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_global_pte_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_global_pte_U_mode ===========================
add_test(NAME    "vm_sv57/sv57_global_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_global_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_global_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_global_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_global_pte_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_invalid_pte_S_mode ==========================
add_test(NAME    "vm_sv57/sv57_invalid_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_invalid_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_invalid_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_invalid_pte_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_invalid_pte_U_mode ==========================
add_test(NAME    "vm_sv57/sv57_invalid_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_invalid_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_invalid_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_invalid_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_invalid_pte_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_misaligned_S_mode ===========================
add_test(NAME    "vm_sv57/sv57_misaligned_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_misaligned_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_misaligned_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_misaligned_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_misaligned_U_mode ===========================
add_test(NAME    "vm_sv57/sv57_misaligned_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_misaligned_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_misaligned_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_misaligned_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_misaligned_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mprv_S_mode =================================
add_test(NAME    "vm_sv57/sv57_mprv_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mprv_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mprv_U_mode =================================
add_test(NAME    "vm_sv57/sv57_mprv_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mprv_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mprv_U_set_sum_set_S_mode ===================
add_test(NAME    "vm_sv57/sv57_mprv_U_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mprv_U_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mprv_U_set_sum_unset_S_mode =================
add_test(NAME    "vm_sv57/sv57_mprv_U_set_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_set_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mprv_U_set_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mprv_U_set_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mprv_U_set_sum_unset_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mstatus_sbe_set_S_mode ======================
add_test(NAME    "vm_sv57/sv57_mstatus_sbe_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mstatus_sbe_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mstatus_sbe_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mstatus_sbe_set_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode ==============
add_test(NAME    "vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mstatus_sbe_set_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mstatus_sbe_set_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mstatus_sbe_set_sum_set_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mxr_S_mode ==================================
add_test(NAME    "vm_sv57/sv57_mxr_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mxr_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mxr_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mxr_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_mxr_U_mode ==================================
add_test(NAME    "vm_sv57/sv57_mxr_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mxr_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_mxr_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_mxr_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_mxr_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_nleaf_pte_level0_S_mode =====================
add_test(NAME    "vm_sv57/sv57_nleaf_pte_level0_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_nleaf_pte_level0_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_nleaf_pte_level0_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_nleaf_pte_level0_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_nleaf_pte_level0_U_mode =====================
add_test(NAME    "vm_sv57/sv57_nleaf_pte_level0_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_nleaf_pte_level0_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_nleaf_pte_level0_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_nleaf_pte_level0_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_nleaf_pte_level0_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_pte_reserved_field_S_mode ===================
add_test(NAME    "vm_sv57/sv57_pte_reserved_field_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_pte_reserved_field_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_pte_reserved_field_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_pte_reserved_field_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_pte_reserved_field_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_pte_reserved_field_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_pte_reserved_field_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_pte_reserved_field_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_pte_reserved_field_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_rsw_pte_S_mode =====================
add_test(NAME    "vm_sv57/sv57_reserved_rsw_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rsw_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rsw_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_rsw_pte_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_rsw_pte_U_mode =====================
add_test(NAME    "vm_sv57/sv57_reserved_rsw_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rsw_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rsw_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rsw_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_rsw_pte_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_rwx_pte_S_mode =====================
add_test(NAME    "vm_sv57/sv57_reserved_rwx_pte_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rwx_pte_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rwx_pte_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_rwx_pte_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_rwx_pte_U_mode =====================
add_test(NAME    "vm_sv57/sv57_reserved_rwx_pte_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rwx_pte_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_rwx_pte_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_rwx_pte_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_rwx_pte_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_svnapot_S_mode =====================
add_test(NAME    "vm_sv57/sv57_reserved_svnapot_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svnapot_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_svnapot_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svnapot_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svnapot_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svnapot_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_svnapot_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svnapot_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_svnapot_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_reserved_svpbmt_S_mode ======================
add_test(NAME    "vm_sv57/sv57_reserved_svpbmt_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svpbmt_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_svpbmt_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svpbmt_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svpbmt_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svpbmt_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_reserved_svpbmt_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_reserved_svpbmt_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_reserved_svpbmt_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_satp_access_tests ===========================
add_test(NAME    "vm_sv57/sv57_satp_access_tests"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_satp_access_tests;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_satp_access_tests.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_satp_access_tests/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_satp_access_tests/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_satp_access_tests/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_satp_access_tests.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_satp_access_tests/signature.test"
         )
set_tests_properties("vm_sv57/sv57_satp_access_tests" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_spage_access_U_mode =========================
add_test(NAME    "vm_sv57/sv57_spage_access_U_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_spage_access_U_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_spage_access_U_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_spage_access_U_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_spage_access_U_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_spage_access_U_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_spage_access_U_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_spage_access_U_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_spage_access_U_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_sum_set_S_mode ==============================
add_test(NAME    "vm_sv57/sv57_sum_set_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_set_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_set_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_sum_set_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_sum_set_U_bit_unset_S_mode ==================
add_test(NAME    "vm_sv57/sv57_sum_set_U_bit_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_U_bit_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_set_U_bit_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_U_bit_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_U_bit_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_U_bit_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_set_U_bit_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_set_U_bit_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_sum_set_U_bit_unset_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

#==================== vm_sv57/sv57_sum_unset_S_mode ============================
add_test(NAME    "vm_sv57/sv57_sum_unset_S_mode"
         COMMAND "bash" "-c" "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_unset_S_mode;
                              ${LINUX_CXX_COMPILER} -march=${COMPILER_MARCH} -mabi=lp64 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g -T ${RISCV_ARCH_TESTS}/env/link.ld -I ${RISCV_ARCH_TESTS}/env/ ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_unset_S_mode.S -o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_unset_S_mode/test.elf -Drvtest_mtrap_routine=True -Drvtest_strap_routine=True -DTEST_CASE_1=True -DXLEN=64 ;
                              ${SPIKE_PATH} --isa=${SPIKE_ISA} +signature-granularity=8 +signature=${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_unset_S_mode/signature.test ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_unset_S_mode/test.elf;
                              diff ${RISCV_ARCH_TESTS}/src/vm_sv57/src/sv57_sum_unset_S_mode.gold ${CMAKE_BINARY_DIR}/riscv-arch-tests/vm_sv57/sv57_sum_unset_S_mode/signature.test"
         )
set_tests_properties("vm_sv57/sv57_sum_unset_S_mode" PROPERTIES LABELS "vm_sv57")
#===============================================================================

# disable tests marked with disabled labels
disable_tests("." "${DISABLED_LABELS}")
