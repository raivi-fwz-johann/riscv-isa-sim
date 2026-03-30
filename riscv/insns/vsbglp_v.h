#include "xvkgost_common.h"
#include "zvk_ext_macros.h"

require_extension(EXT_XVKGOST);
require_rv64;
require_no_vmask;
require_element_groups_64x8;

const reg_t rd_num = insn.rd();
const reg_t rs2_num = insn.rs2();
const reg_t sew = P.VU.vsew;
const reg_t vstart_eg = P.VU.vstart->read() / 8;
const reg_t vl_eg = P.VU.vl->read() / 8;
if (vstart_eg < vl_eg) {
  for (reg_t idx_eg = vstart_eg; idx_eg < vl_eg; ++idx_eg) {
    EGU64x8_t &new_state = P.VU.elt_group<EGU64x8_t>(rd_num, idx_eg, true);
    //FIXME: Support new instruction correctly
    const EGU64x8_t &state_full = P.VU.elt_group<EGU64x8_t>(rs2_num, idx_eg);
    new_state = xvkgost_sbg_L(xvkgost_sbg_P(state_full));
  }
}
V_HANDLE_TAIL(VEC_COMMON, V_PARAMS)