#include "xvkgost_common.h"
#include "zvk_ext_macros.h"

require_extension(EXT_XVKGOST);
require_rv64;
require_no_vmask;

const reg_t rd_num = insn.rd();
const reg_t rs2_num = insn.rs2();
const reg_t sew = P.VU.vsew;
const reg_t vstart_eg = P.VU.vstart->read();
const reg_t vl_eg = P.VU.vl->read();
if (vstart_eg < vl_eg) {
  const uint64_t round_keys = RS1;
  const uint32_t round_key1 = bswap32((uint32_t)round_keys);
  const uint32_t round_key2 = bswap32((uint32_t)(round_keys >> 32));
  for (reg_t idx_eg = vstart_eg; idx_eg < vl_eg; ++idx_eg) {
    uint64_t &new_state = P.VU.elt<uint64_t>(rd_num, idx_eg, true);
    uint64_t state = bswap64(P.VU.elt<uint64_t>(rs2_num, idx_eg));
    new_state = magma_round(state, round_key1);
    new_state = bswap64(magma_round(new_state, round_key2));
  }
}
V_HANDLE_TAIL(VEC_COMMON, VX_PARAMS)