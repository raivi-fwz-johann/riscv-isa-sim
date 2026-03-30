// vadc.vx vd, vs2, rs1, v0
// /* code ext: always tail-agnostic for vmask instructions */
VI_XI_LOOP_CARRY
({
  res = (((op_mask & rs1) + (op_mask & vs2) + carry) >> sew) & 0x1u;
})
for (reg_t i = vl; i < (P.VU.vstart->read() + P.VU.VLEN); ++i) {
  int midx = i / 64;
  int mpos = i % 64;
  uint64_t &res = P.VU.elt<uint64_t>(insn.rd(), midx, true);
  res = res | (1ULL << mpos);
}
