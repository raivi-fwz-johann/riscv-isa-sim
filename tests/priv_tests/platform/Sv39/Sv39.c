#include <test_utils.h>
/*
 *  Init for virtual memory tests. Please don't remove
 */
TEST_REGISTER(init);

// --- supervisor mode flags ---
TEST_REGISTER(sv39_v);
TEST_REGISTER(sv39_r);
TEST_REGISTER(sv39_w);
TEST_REGISTER(sv39_x);
TEST_REGISTER(sv39_u);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv39_g);

TEST_REGISTER(sv39_a);
TEST_REGISTER(sv39_d);


// --- hypervisor hgatp flags ---
TEST_REGISTER(sv39_v_hgatp);
TEST_REGISTER(sv39_r_hgatp);
TEST_REGISTER(sv39_w_hgatp);
TEST_REGISTER(sv39_x_hgatp);
TEST_REGISTER(sv39_u_hgatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv39_g_hgatp);

TEST_REGISTER(sv39_a_hgatp);
TEST_REGISTER(sv39_d_hgatp);


// --- hypervisor vsatp flags ---
TEST_REGISTER(sv39_v_vsatp);
TEST_REGISTER(sv39_r_vsatp);
TEST_REGISTER(sv39_w_vsatp);
TEST_REGISTER(sv39_x_vsatp);
TEST_REGISTER(sv39_u_vsatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv39_g_vsatp);

TEST_REGISTER(sv39_a_vsatp);
TEST_REGISTER(sv39_d_vsatp);

// --- supervisor mode address translation ---
TEST_REGISTER(sv39_gigapage);
TEST_REGISTER(sv39_megapage);
TEST_REGISTER(sv39_kilopage);

// --- hgatp address translation ---
TEST_REGISTER(sv39_gigapage_hgatp);
TEST_REGISTER(sv39_megapage_hgatp);
TEST_REGISTER(sv39_kilopage_hgatp);

// --- vsatp address translation ---
TEST_REGISTER(sv39_gigapage_vsatp);
TEST_REGISTER(sv39_megapage_vsatp);
TEST_REGISTER(sv39_kilopage_vsatp);

// --- two-stage address translation ---
TEST_REGISTER(sv39_gigapage_two_stage);
TEST_REGISTER(sv39_megapage_two_stage);
TEST_REGISTER(sv39_kilopage_two_stage);
