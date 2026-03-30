#include <test_utils.h>

// -----  MISA -----
TEST_REGISTER(misa_mxl);
TEST_R_FIELD_REGISTER(misa_A, misa, MISA_A_OFF, MISA_A_LEN, 1);
TEST_REGISTER(misa_B);
TEST_REGISTER(misa_C);
TEST_R_FIELD_REGISTER(misa_D, misa, MISA_D_OFF, MISA_D_LEN, 1);
TEST_R_FIELD_REGISTER(misa_F, misa, MISA_F_OFF, MISA_F_LEN, 1);
TEST_REGISTER(misa_H);
TEST_R_FIELD_REGISTER(misa_I, misa, MISA_I_OFF, MISA_I_LEN, 1);
TEST_R_FIELD_REGISTER(misa_K, misa, MISA_K_OFF, MISA_K_LEN, 0);
TEST_REGISTER(misa_M);
TEST_R_FIELD_REGISTER(misa_V, misa, MISA_V_OFF, MISA_V_LEN, 1);

// -----  MVENDORID -----
TEST_R_FIELD_REGISTER(mvendorid_offset, mvendorid, MVENDORID_OFFSET_OFF, MVENDORID_OFFSET_LEN, 0);
TEST_R_FIELD_REGISTER(mvendorid_bank, mvendorid, MVENDORID_BANK_OFF, MVENDORID_BANK_LEN, 0);

// -----  MARCHID -----
TEST_R_REGISTER(marchid, 5);

// -----  MIMPID -----
TEST_R_REGISTER(mimpid, 0);

// -----  MHARTID -----
TEST_R_REGISTER(mhartid, 0);

// -----  MSTATUS -----
TEST_REGISTER(mstatus_sie);
TEST_REGISTER(mstatus_mie);
TEST_REGISTER(mstatus_spie);
TEST_R_FIELD_REGISTER(mstatus_ube, mstatus, MSTATUS_UBE_OFF, MSTATUS_UBE_LEN, 0);
TEST_REGISTER(mstatus_mpie);
TEST_REGISTER(mstatus_spp);
TEST_REGISTER(mstatus_vs);
TEST_REGISTER(mstatus_mpp);
TEST_REGISTER(mstatus_fs);
TEST_R_FIELD_REGISTER(mstatus_xs, mstatus, MSTATUS_XS_OFF, MSTATUS_XS_LEN, 0);

TEST_REGISTER(mstatus_mprv);
TEST_REGISTER(mstatus_sum);
TEST_REGISTER(mstatus_mxr);

TEST_REGISTER(mstatus_tvm);
TEST_REGISTER(mstatus_tw);
TEST_REGISTER(mstatus_tsr);

TEST_REGISTER(mstatus_uxl);
TEST_REGISTER(mstatus_sxl);
TEST_R_FIELD_REGISTER(mstatus_sbe, mstatus, MSTATUS_SBE_OFF, MSTATUS_SBE_LEN, 0);
TEST_R_FIELD_REGISTER(mstatus_mbe, mstatus, MSTATUS_MBE_OFF, MSTATUS_MBE_LEN, 0);
TEST_REGISTER(mstatus_sd);

// -----  MTVEC -----
// TODO: need trampoline with many jumps in handlers.S 
//TEST_REGISTER(mtvec_mode);
TEST_REGISTER(mtvec_base);

// -----  MIDELEG -----
TEST_REGISTER(mideleg_ssi);

// -----  MEDELEG -----
TEST_REGISTER(medeleg_illigal_instruction);
TEST_REGISTER(medeleg_breakpoint);
TEST_REGISTER(medeleg_load_address_misaligned);
TEST_REGISTER(medeleg_store_address_misaligned);
TEST_REGISTER(medeleg_instruction_page_fault);
TEST_REGISTER(medeleg_load_page_fault);
TEST_REGISTER(medeleg_store_page_fault);
TEST_REGISTER(medeleg_instruction_access_fault);
TEST_REGISTER(medeleg_load_access_fault);
TEST_REGISTER(medeleg_store_access_fault);

// -----  MIE -----
TEST_REGISTER(mie_mtie);

// -----  MIP -----
// TODO: in spike interrupts are very specific

// -----  MEPC -----
TEST_REGISTER(mepc);

// ----- MSCRATCH -----
TEST_REGISTER(mscratch);

// -----  MCAUSE -----
TEST_REGISTER(mcause_illigal_instruction);
TEST_REGISTER(mcause_breakpoint);
TEST_REGISTER(mcause_load_address_misaligned);
TEST_REGISTER(mcause_store_address_misaligned);
TEST_REGISTER(mcause_m_mode_ecall);
TEST_REGISTER(mcause_s_mode_ecall);
TEST_REGISTER(mcause_u_mode_ecall);
TEST_REGISTER(mcause_machine_timer_interrupt);
TEST_REGISTER(mcause_instruction_page_fault);
TEST_REGISTER(mcause_load_page_fault);
TEST_REGISTER(mcause_store_page_fault);
TEST_REGISTER(mcause_instruction_access_fault);
TEST_REGISTER(mcause_load_access_fault);
TEST_REGISTER(mcause_store_access_fault);

// -----  MTVAL -----
TEST_REGISTER(mtval_breakpoint);
TEST_REGISTER(mtval_address_misaligned);
TEST_REGISTER(mtval_illigal_instruction);
TEST_REGISTER(mtval_page_fault);
TEST_REGISTER(mtval_access_fault);

// -----  MCONFIGPTR -----
TEST_R_REGISTER(mconfigptr, 0);

// -----  MENVCFG -----
TEST_R_REGISTER(menvcfg, 0);

// -----  MSECCFG -----
TEST_R_REGISTER(mseccfg, 1);
