#include <test_utils.h>
/*
 *  Init for virtual memory tests. Please don't remove
 */
TEST_REGISTER(init);

// --- supervisor mode flags ---
TEST_REGISTER(sv48_v);
TEST_REGISTER(sv48_r);
TEST_REGISTER(sv48_w);
TEST_REGISTER(sv48_x);
TEST_REGISTER(sv48_u);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv48_g);

TEST_REGISTER(sv48_a);
TEST_REGISTER(sv48_d);


// --- hypervisor hgatp flags ---
TEST_REGISTER(sv48_v_hgatp);
TEST_REGISTER(sv48_r_hgatp);
TEST_REGISTER(sv48_w_hgatp);
TEST_REGISTER(sv48_x_hgatp);
TEST_REGISTER(sv48_u_hgatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv48_g_hgatp);

TEST_REGISTER(sv48_a_hgatp);
TEST_REGISTER(sv48_d_hgatp);


// --- hypervisor vsatp flags ---
TEST_REGISTER(sv48_v_vsatp);
TEST_REGISTER(sv48_r_vsatp);
TEST_REGISTER(sv48_w_vsatp);
TEST_REGISTER(sv48_x_vsatp);
TEST_REGISTER(sv48_u_vsatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv48_g_vsatp);

TEST_REGISTER(sv48_a_vsatp);
TEST_REGISTER(sv48_d_vsatp);

// --- supervisor mode address translation ---
TEST_REGISTER(sv48_terapage);
TEST_REGISTER(sv48_gigapage);
TEST_REGISTER(sv48_megapage);
TEST_REGISTER(sv48_kilopage);

// --- hgatp address translation ---
TEST_REGISTER(sv48_terapage_hgatp);
TEST_REGISTER(sv48_gigapage_hgatp);
TEST_REGISTER(sv48_megapage_hgatp);
TEST_REGISTER(sv48_kilopage_hgatp);

// --- vsatp address translation ---
TEST_REGISTER(sv48_terapage_vsatp);
TEST_REGISTER(sv48_gigapage_vsatp);
TEST_REGISTER(sv48_megapage_vsatp);
TEST_REGISTER(sv48_kilopage_vsatp);

// --- two-stage address translation ---
TEST_REGISTER(sv48_terapage_two_stage);
TEST_REGISTER(sv48_gigapage_two_stage);
TEST_REGISTER(sv48_megapage_two_stage);
TEST_REGISTER(sv48_kilopage_two_stage);
