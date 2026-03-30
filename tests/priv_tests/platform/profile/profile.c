#include <test_utils.h>

TEST_REGISTER(za64rs);
TEST_REGISTER(svbare);
TEST_REGISTER(sstvecd);

TEST_REGISTER(sstvala_illigal_instruction);
TEST_REGISTER(sstvala_virtual_instruction);
TEST_REGISTER(sstvala_breakpoint);
TEST_REGISTER(sstvala_address_misaligned);
TEST_REGISTER(sstvala_access_fault);
TEST_REGISTER(sstvala_page_fault);

// Spike not support Sscounterenw
//TEST_REGISTER(sscounterenw);

// Spike not support Sscounterenw
//TEST_REGISTER(shcounterenw);

TEST_REGISTER(ssu64xl);

TEST_REGISTER(shvstvala_illigal_instruction);
TEST_REGISTER(shvstvala_breakpoint);
TEST_REGISTER(shvstvala_address_misaligned);
TEST_REGISTER(shvstvala_access_fault);
TEST_REGISTER(shvstvala_page_fault);

TEST_REGISTER(shtvala);
TEST_REGISTER(shvstvecd);

TEST_REGISTER(shvsatpa_sv39);
TEST_REGISTER(shvsatpa_sv48);
TEST_REGISTER(shvsatpa_sv57);

TEST_REGISTER(shgatpa_sv39);
TEST_REGISTER(shgatpa_sv48);
TEST_REGISTER(shgatpa_sv57);

TEST_REGISTER(svade_a);
TEST_REGISTER(svade_a_hgatp);
TEST_REGISTER(svade_a_vsatp);
TEST_REGISTER(svade_d);
TEST_REGISTER(svade_d_hgatp);
TEST_REGISTER(svade_d_vsatp);
