#include <test_utils.h>
/*
 *  Init for Ss1p13 tests. Please don't remove
 */
TEST_REGISTER(init);

// -----  SSTATUS -----
TEST_REGISTER(sstatus_sie);
TEST_REGISTER(sstatus_spie);
TEST_R_FIELD_REGISTER(sstatus_ube, sstatus, SSTATUS_UBE_OFF, SSTATUS_UBE_LEN, 0);
TEST_REGISTER(sstatus_spp);
TEST_REGISTER(sstatus_vs);
TEST_REGISTER(sstatus_fs);
TEST_R_FIELD_REGISTER(sstatus_xs, sstatus, SSTATUS_XS_OFF, SSTATUS_XS_LEN, 0);

TEST_REGISTER(sstatus_sum);
TEST_REGISTER(sstatus_mxr);

TEST_REGISTER(sstatus_uxl);
TEST_REGISTER(sstatus_sd);

// -----  STVEC -----
// TODO: need trampoline with many jumps in handlers.S 
//TEST_REGISTER(stvec_mode);
TEST_REGISTER(stvec_base);

// -----  SIE -----
TEST_REGISTER(sie_ssie);

// -----  SIP -----
// TODO: in spike interrupts are very specific

// ----- SSCRATCH -----
TEST_REGISTER(sscratch);

// -----  SEPC -----
TEST_REGISTER(sepc);

// -----  SCAUSE -----
TEST_REGISTER(scause_illigal_instruction);
TEST_REGISTER(scause_breakpoint);
TEST_REGISTER(scause_load_address_misaligned);
TEST_REGISTER(scause_store_address_misaligned);
TEST_REGISTER(scause_s_mode_ecall);
TEST_REGISTER(scause_u_mode_ecall);
TEST_REGISTER(scause_supervisor_software_interrupt);
TEST_REGISTER(scause_instruction_page_fault);
TEST_REGISTER(scause_load_page_fault);
TEST_REGISTER(scause_store_page_fault);
TEST_REGISTER(scause_instruction_access_fault);
TEST_REGISTER(scause_load_access_fault);
TEST_REGISTER(scause_store_access_fault);

// -----  STVAL -----
TEST_REGISTER(stval_breakpoint);
TEST_REGISTER(stval_address_misaligned);
TEST_REGISTER(stval_illigal_instruction);
TEST_REGISTER(stval_page_fault);
TEST_REGISTER(stval_access_fault);

// -----  SENVCFG -----
TEST_R_REGISTER(senvcfg, 0);

// -----  SATP -----
TEST_REGISTER(satp_mode);
TEST_REGISTER(satp_ppn);

// TODO: spike does not have TLB
//TEST_REGISTER(satp_asid);
