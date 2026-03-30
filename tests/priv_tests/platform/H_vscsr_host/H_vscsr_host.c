#include <test_utils.h>
/*
 *  Init for Hypervisor tests for VS CSRs in host OS. Please don't remove
 */
TEST_REGISTER(init);

// -----  VSSTATUS -----
TEST_REGISTER(vsstatus_sie_host);
TEST_REGISTER(vsstatus_spie_host);
TEST_R_FIELD_REGISTER(vsstatus_ube_host, vsstatus, VSSTATUS_UBE_OFF, VSSTATUS_UBE_LEN, 0);
TEST_REGISTER(vsstatus_spp_host);
TEST_REGISTER(vsstatus_vs_host);
TEST_REGISTER(vsstatus_fs_host);
TEST_R_FIELD_REGISTER(vsstatus_xs_host, vsstatus, VSSTATUS_XS_OFF, VSSTATUS_XS_LEN, 0);

TEST_REGISTER(vsstatus_sum_host);
TEST_REGISTER(vsstatus_mxr_host);

TEST_REGISTER(vsstatus_uxl_host);
TEST_REGISTER(vsstatus_sd_host);

// -----  VSTVEC -----
// TODO: need trampoline with many jumps in handlers.S 
//TEST_REGISTER(vstvec_mode_guest);
TEST_REGISTER(vstvec_base_host);

// -----  VSIE -----
TEST_REGISTER(vsie_ssie_host);

// -----  VSIP -----
// TODO: in spike interrupts are very specific

// ----- VSSCRATCH -----
TEST_REGISTER(vsscratch_host);

// -----  VSEPC -----
TEST_REGISTER(vsepc_host);

// -----  VSCAUSE -----
TEST_REGISTER(vscause_illigal_instruction_host);
TEST_REGISTER(vscause_breakpoint_host);
TEST_REGISTER(vscause_load_address_misaligned_host);
TEST_REGISTER(vscause_store_address_misaligned_host);
TEST_REGISTER(vscause_supervisor_software_interrupt_host);
TEST_REGISTER(vscause_instruction_page_fault_host);
TEST_REGISTER(vscause_load_page_fault_host);
TEST_REGISTER(vscause_store_page_fault_host);
TEST_REGISTER(vscause_instruction_access_fault_host);
TEST_REGISTER(vscause_load_access_fault_host);
TEST_REGISTER(vscause_store_access_fault_host);

// -----  VSTVAL -----
TEST_REGISTER(vstval_breakpoint_host);
TEST_REGISTER(vstval_address_misaligned_host);
TEST_REGISTER(vstval_illigal_instruction_host);
TEST_REGISTER(vstval_page_fault_host);
TEST_REGISTER(vstval_access_fault_host);

// -----  VSATP -----
TEST_REGISTER(vsatp_mode_host);
TEST_REGISTER(vsatp_ppn_host);

// TODO: spike does not have TLB
//TEST_REGISTER(vsatp_asid_host);
