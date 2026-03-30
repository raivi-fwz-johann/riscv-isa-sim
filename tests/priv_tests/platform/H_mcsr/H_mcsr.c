#include <test_utils.h>

// -----  MSTATUS -----
TEST_REGISTER(mstatus_gva_breakpoint);
TEST_REGISTER(mstatus_gva_load_address_misaligned);
TEST_REGISTER(mstatus_gva_store_address_misaligned);
TEST_REGISTER(mstatus_gva_instruction_page_fault);
TEST_REGISTER(mstatus_gva_load_page_fault);
TEST_REGISTER(mstatus_gva_store_page_fault);
TEST_REGISTER(mstatus_gva_instruction_guest_page_fault);
TEST_REGISTER(mstatus_gva_load_guest_page_fault);
TEST_REGISTER(mstatus_gva_store_guest_page_fault);
TEST_REGISTER(mstatus_gva_instruction_access_fault);
TEST_REGISTER(mstatus_gva_load_access_fault);
TEST_REGISTER(mstatus_gva_store_access_fault);

TEST_REGISTER(mstatus_mpv);
TEST_REGISTER(mstatus_tw);
TEST_REGISTER(mstatus_tsr);
TEST_REGISTER(mstatus_tvm);
TEST_REGISTER(mstatus_mprv);


// -----  MIDELEG -----
TEST_RO_FIELD_REGISTER(mideleg_vssi, mideleg, MIDELEG_VSSI_OFF, MIDELEG_VSSI_LEN, 1);
TEST_RO_FIELD_REGISTER(mideleg_vsti, mideleg, MIDELEG_VSTI_OFF, MIDELEG_VSTI_LEN, 1);
TEST_RO_FIELD_REGISTER(mideleg_vsei, mideleg, MIDELEG_VSEI_OFF, MIDELEG_VSEI_LEN, 1);
TEST_RO_FIELD_REGISTER(mideleg_sgei, mideleg, MIDELEG_SGEI_OFF, MIDELEG_SGEI_LEN, 1);

// -----  MIP -----
TEST_REGISTER(mip_vssip);
TEST_REGISTER(mip_vseip);
TEST_REGISTER(mip_vstip);
//TODO: Spike hgeip and hgeie are read only zeros
//TEST_REGISTER(hip_sgeip);


// -----  MIE -----
TEST_REGISTER(mie_vssie);
TEST_REGISTER(mie_vseie);
TEST_REGISTER(mie_vstie);
TEST_REGISTER(mie_sgeie);


// -----  MTVAL2 -----
TEST_REGISTER(mtval2);

// -----  MTINST -----
//TODO: Need more time to do this test

