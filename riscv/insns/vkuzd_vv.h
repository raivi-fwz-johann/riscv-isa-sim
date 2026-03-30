#include "xvcgost_common.h"
#include "zvk_ext_macros.h"

require_extension(EXT_XVCGOST);
require_rv64;
require_element_groups_32x4;
require_no_vmask;

const reg_t vd_num = insn.rd();
const reg_t vs1_num = insn.rs1();
const reg_t vs2_num = insn.rs2();
const reg_t vstart_eg = P.VU.vstart->read() / 4;
const reg_t vl_eg = P.VU.vl->read() / 4;
if (vstart_eg < vl_eg) {
  for (reg_t idx_eg = vstart_eg; idx_eg < vl_eg; ++idx_eg) {
    EGU8x16_t &new_state = P.VU.elt_group<EGU8x16_t>(vd_num, idx_eg, true);
    const EGU8x16_t state = P.VU.elt_group<EGU8x16_t>(vs2_num, idx_eg);
    const EGU8x16_t round_key = P.VU.elt_group<EGU8x16_t>(vs1_num, idx_eg);
    new_state = xvcgost_kuzL_dec(state);
    GOST_XS_INV(new_state, round_key);
  }
}
P.VU.vstart->write(0);
