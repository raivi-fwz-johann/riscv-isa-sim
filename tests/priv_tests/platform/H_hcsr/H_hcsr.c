#include <test_utils.h>
/*
 *  Init for Hypervisor tests for H CSRs. Please don't remove
 */
TEST_REGISTER(init);

// -----  HSTATUS -----
TEST_R_FIELD_REGISTER(hstatus_vsbe, hstatus, HSTATUS_VSBE_OFF, HSTATUS_VSBE_LEN, 0);

TEST_REGISTER(hstatus_gva_breakpoint);
TEST_REGISTER(hstatus_gva_load_address_misaligned);
TEST_REGISTER(hstatus_gva_store_address_misaligned);
TEST_REGISTER(hstatus_gva_instruction_page_fault);
TEST_REGISTER(hstatus_gva_load_page_fault);
TEST_REGISTER(hstatus_gva_store_page_fault);
TEST_REGISTER(hstatus_gva_instruction_guest_page_fault);
TEST_REGISTER(hstatus_gva_load_guest_page_fault);
TEST_REGISTER(hstatus_gva_store_guest_page_fault);
TEST_REGISTER(hstatus_gva_instruction_access_fault);
TEST_REGISTER(hstatus_gva_load_access_fault);
TEST_REGISTER(hstatus_gva_store_access_fault);

TEST_REGISTER(hstatus_spv);
TEST_REGISTER(hstatus_spvp);
TEST_REGISTER(hstatus_hu);

//TODO: Spike GEILEN is 0, so test vgein no supported
//TEST_REGISTER(hstatus_vgein);

TEST_REGISTER(hstatus_vtvm);
TEST_REGISTER(hstatus_vtw);
TEST_REGISTER(hstatus_vtsr);
TEST_REGISTER(hstatus_vsxl);

// -----  HEDELEG -----
TEST_REGISTER(hedeleg_breakpoint);
TEST_REGISTER(hedeleg_illigal_instruction);
TEST_REGISTER(hedeleg_load_address_misaligned);
TEST_REGISTER(hedeleg_store_address_misaligned);
TEST_REGISTER(hedeleg_u_call);
TEST_REGISTER(hedeleg_instruction_page_fault);
TEST_REGISTER(hedeleg_load_page_fault);
TEST_REGISTER(hedeleg_store_page_fault);
TEST_REGISTER(hedeleg_instruction_access_fault);
TEST_REGISTER(hedeleg_load_access_fault);
TEST_REGISTER(hedeleg_store_access_fault);

// -----  HIDELEG -----
TEST_REGISTER(hideleg_vssi);

// -----  HVIP -----
TEST_REGISTER(hvip_vssip);
TEST_REGISTER(hvip_vseip);
TEST_REGISTER(hvip_vstip);

// -----  HIP -----
TEST_REGISTER(hip_vssip);
TEST_REGISTER(hip_vseip);
TEST_REGISTER(hip_vstip);
//TODO: Spike hgeip and hgeie are read only zeros
//TEST_REGISTER(hip_sgeip);

// -----  HIE -----
TEST_REGISTER(hie_vssie);
TEST_REGISTER(hie_vseie);
TEST_REGISTER(hie_vstie);
//TODO: Spike hgeip and hgeie are read only zeros
//TEST_REGISTER(hie_sgeie);

// -----  HGEIP -----
//TODO: Spike GEILEN is 0, so test hgeip no supported
//TEST_REGISTER(hgeip);

// -----  HGEIE -----
//TODO: Spike GEILEN is 0, so test hgeie no supported
//TEST_REGISTER(hgeie);
 
// -----  HENVCFG -----
TEST_R_REGISTER(henvcfg, 0);

// -----  HCOUNTEREN -----
//TODO: Test for counters not done in Spike

// -----  HTIMEDELTA -----
//TODO: Test for counters not done in Spike

// -----  HTVAL -----
TEST_REGISTER(htval);

// -----  HTINST -----
//TODO: Need more time to do this test

// -----  HGAPT -----
TEST_REGISTER(hgatp_mode);
TEST_REGISTER(hgatp_ppn);

// TODO: spike does not have TLB
//TEST_REGISTER(hgatp_vmid);

