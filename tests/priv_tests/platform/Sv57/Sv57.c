#include <test_utils.h>
/*
 *  Init for virtual memory tests. Please don't remove
 */
TEST_REGISTER(init);

// --- supervisor mode flags ---
TEST_REGISTER(sv57_v);
TEST_REGISTER(sv57_r);
TEST_REGISTER(sv57_w);
TEST_REGISTER(sv57_x);
TEST_REGISTER(sv57_u);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv57_g);

TEST_REGISTER(sv57_a);
TEST_REGISTER(sv57_d);


// --- hypervisor hgatp flags ---
TEST_REGISTER(sv57_v_hgatp);
TEST_REGISTER(sv57_r_hgatp);
TEST_REGISTER(sv57_w_hgatp);
TEST_REGISTER(sv57_x_hgatp);
TEST_REGISTER(sv57_u_hgatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv57_g_hgatp);

TEST_REGISTER(sv57_a_hgatp);
TEST_REGISTER(sv57_d_hgatp);


// --- hypervisor vsatp flags ---
TEST_REGISTER(sv57_v_vsatp);
TEST_REGISTER(sv57_r_vsatp);
TEST_REGISTER(sv57_w_vsatp);
TEST_REGISTER(sv57_x_vsatp);
TEST_REGISTER(sv57_u_vsatp);

// TODO: Spike does not have TLB
//TEST_REGISTER(sv57_g_vsatp);

TEST_REGISTER(sv57_a_vsatp);
TEST_REGISTER(sv57_d_vsatp);

// --- supervisor mode address translation ---
TEST_REGISTER(sv57_petapage);
TEST_REGISTER(sv57_terapage);
TEST_REGISTER(sv57_gigapage);
TEST_REGISTER(sv57_megapage);
TEST_REGISTER(sv57_kilopage);

// --- hgatp address translation ---
TEST_REGISTER(sv57_petapage_hgatp);
TEST_REGISTER(sv57_terapage_hgatp);
TEST_REGISTER(sv57_gigapage_hgatp);
TEST_REGISTER(sv57_megapage_hgatp);
TEST_REGISTER(sv57_kilopage_hgatp);

// --- vsatp address translation ---
TEST_REGISTER(sv57_petapage_vsatp);
TEST_REGISTER(sv57_terapage_vsatp);
TEST_REGISTER(sv57_gigapage_vsatp);
TEST_REGISTER(sv57_megapage_vsatp);
TEST_REGISTER(sv57_kilopage_vsatp);

// --- two-stage address translation ---
TEST_REGISTER(sv57_petapage_two_stage);
TEST_REGISTER(sv57_terapage_two_stage);
TEST_REGISTER(sv57_gigapage_two_stage);
TEST_REGISTER(sv57_megapage_two_stage);
TEST_REGISTER(sv57_kilopage_two_stage);
