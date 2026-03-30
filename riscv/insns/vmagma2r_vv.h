#include "xvcgost_common.h"
#include "zvk_ext_macros.h"

require_extension(EXT_XVCGOST);
require_rv64;
require_no_vmask;

const reg_t vd_num = insn.rd();
const reg_t vs1_num = insn.rs1();
const reg_t vs2_num = insn.rs2();
const reg_t vstart_eg = P.VU.vstart->read();
const reg_t vl_eg = P.VU.vl->read();
if (vstart_eg < vl_eg) {
  for (reg_t idx_eg = vstart_eg; idx_eg < vl_eg; ++idx_eg) {
    uint64_t &new_state = P.VU.elt<uint64_t>(vd_num, idx_eg, true);
    uint64_t state = bswap64(P.VU.elt<uint64_t>(vs2_num, idx_eg));
    const uint64_t round_keys = P.VU.elt<uint64_t>(vs1_num, idx_eg);
    const uint32_t round_key1 = bswap32((uint32_t)round_keys);
    const uint32_t round_key2 = bswap32((uint32_t)(round_keys >> 32));
    new_state = bswap64(magma_round(magma_round(state, round_key1), round_key2));
  }
}
P.VU.vstart->write(0);

