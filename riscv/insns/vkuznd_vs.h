#include "xvkgost_common.h"
#include "zvk_ext_macros.h"

require_extension(EXT_XVKGOST);
require_rv64;
require_element_groups_64x2;
require_no_vmask;

const reg_t rd_num = insn.rd();
const reg_t rs1_num = insn.rs1();
const reg_t rs2_num = insn.rs2();
const reg_t sew = P.VU.vsew;
const reg_t vstart_eg = P.VU.vstart->read() / 2;
const reg_t vl_eg = P.VU.vl->read() / 2;
if (vstart_eg < vl_eg) {
  const EGU8x16_t scalar_key = P.VU.elt_group<EGU8x16_t>(rs1_num, 0);
  for (reg_t idx_eg = vstart_eg; idx_eg < vl_eg; ++idx_eg) {
    EGU8x16_t &new_state = P.VU.elt_group<EGU8x16_t>(rd_num, idx_eg, true);
    const EGU8x16_t state = P.VU.elt_group<EGU8x16_t>(rs2_num, idx_eg);
    new_state = xvkgost_kuzL_dec(state);
    GOST_XS_INV(new_state, scalar_key);
  }
}
V_HANDLE_TAIL(VEC_COMMON, VV_PARAMS)