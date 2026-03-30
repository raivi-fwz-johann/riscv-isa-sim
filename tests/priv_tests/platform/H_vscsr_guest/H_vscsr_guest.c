#include <test_utils.h>
/*
 *  Init for Hypervisor tests for VS CSRs in guest OS. Please don't remove
 */
TEST_REGISTER(init);

// -----  VSSTATUS -----
TEST_REGISTER(vsstatus_sie_guest);
TEST_REGISTER(vsstatus_spie_guest);
TEST_R_FIELD_REGISTER(vsstatus_ube_guest, sstatus, SSTATUS_UBE_OFF, SSTATUS_UBE_LEN, 0);
TEST_REGISTER(vsstatus_spp_guest);
TEST_REGISTER(vsstatus_vs_guest);
TEST_REGISTER(vsstatus_fs_guest);
TEST_R_FIELD_REGISTER(vsstatus_xs_guest, sstatus, SSTATUS_XS_OFF, SSTATUS_XS_LEN, 0);

TEST_REGISTER(vsstatus_sum_guest);
TEST_REGISTER(vsstatus_mxr_guest);

TEST_REGISTER(vsstatus_uxl_guest);
TEST_REGISTER(vsstatus_sd_guest);

// -----  VSTVEC -----
// TODO: need trampoline with many jumps in handlers.S 
//TEST_REGISTER(vstvec_mode_guest);
TEST_REGISTER(vstvec_base_guest);

// -----  VSIE -----
TEST_REGISTER(vsie_ssie_guest);

// -----  VSIP -----
// TODO: in spike interrupts are very specific

// ----- VSSCRATCH -----
TEST_REGISTER(vsscratch_guest);

// -----  VSEPC -----
TEST_REGISTER(vsepc_guest);

// -----  VSCAUSE -----
TEST_REGISTER(vscause_illigal_instruction_guest);
TEST_REGISTER(vscause_breakpoint_guest);
TEST_REGISTER(vscause_load_address_misaligned_guest);
TEST_REGISTER(vscause_store_address_misaligned_guest);
TEST_REGISTER(vscause_supervisor_software_interrupt_guest);
TEST_REGISTER(vscause_instruction_page_fault_guest);
TEST_REGISTER(vscause_load_page_fault_guest);
TEST_REGISTER(vscause_store_page_fault_guest);
TEST_REGISTER(vscause_instruction_access_fault_guest);
TEST_REGISTER(vscause_load_access_fault_guest);
TEST_REGISTER(vscause_store_access_fault_guest);

// -----  VSTVAL -----
TEST_REGISTER(vstval_breakpoint_guest);
TEST_REGISTER(vstval_address_misaligned_guest);
TEST_REGISTER(vstval_illigal_instruction_guest);
TEST_REGISTER(vstval_page_fault_guest);
TEST_REGISTER(vstval_access_fault_guest);

// -----  VSATP -----
TEST_REGISTER(vsatp_mode_guest);
TEST_REGISTER(vsatp_ppn_guest);

// TODO: spike does not have TLB
//TEST_REGISTER(vsatp_asid_guest);
