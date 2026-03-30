// vrgatherei16.vv vd, vs2, vs1, vm # vd[i] = (vs1[i] >= VLMAX) ? 0 : vs2[vs1[i]];
float vemul = (16.0 / P.VU.vsew * P.VU.vflmul);
require(vemul >= 0.125 && vemul <= 8);
require_align(insn.rd(), P.VU.vflmul);
require_align(insn.rs2(), P.VU.vflmul);
require_align(insn.rs1(), vemul);
require_noover(insn.rd(), P.VU.vflmul, insn.rs1(), vemul);
require(insn.rd() != insn.rs2());
require_vm;
bool skip;

VI_GENERAL_LOOP_BASE
  VI_MASK_VARS 
  if (insn.v_vm() == 0) { 
    skip = ((P.VU.elt<uint64_t>(0, midx) >> mpos) & 0x1) == 0; 
  } 
  switch (sew) {
  case e8: {
    auto vs1 = P.VU.elt<uint16_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint8_t>(rd_num, i, true);
    if (skip) 
    { if (P.VU.vma) vd = ~uint8_t(0); }
    else vd = vs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint8_t>(rs2_num, vs1);
    break;
  }
  case e16: {
    auto vs1 = P.VU.elt<uint16_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint16_t>(rd_num, i, true);
    if (skip) 
    { if (P.VU.vma) vd = ~uint16_t(0); }
    else vd = vs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint16_t>(rs2_num, vs1);
    break;
  }
  case e32: {
    auto vs1 = P.VU.elt<uint16_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint32_t>(rd_num, i, true);
    if (skip) 
    { if (P.VU.vma) vd = ~uint32_t(0); }
    else vd = vs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint32_t>(rs2_num, vs1);
    break;
  }
  default: {
    auto vs1 = P.VU.elt<uint16_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint64_t>(rd_num, i, true);
    if (skip) 
    { if (P.VU.vma) vd = ~uint64_t(0); }
    else vd = vs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint64_t>(rs2_num, vs1);
    break;
  }
  }
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
