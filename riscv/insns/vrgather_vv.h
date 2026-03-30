// vrgather.vv vd, vs2, vs1, vm # vd[i] = (vs1[i] >= VLMAX) ? 0 : vs2[vs1[i]];
require_align(insn.rd(), P.VU.vflmul);
require_align(insn.rs2(), P.VU.vflmul);
require_align(insn.rs1(), P.VU.vflmul);
require(insn.rd() != insn.rs2() && insn.rd() != insn.rs1());
require_vm;

// VI_LOOP_BASE

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK

  switch (sew) {
  case e8: {
    auto vs1 = P.VU.elt<uint8_t>(rs1_num, i);
    //if (i > 255) continue;
    auto& vd = P.VU.elt<uint8_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint8_t(0); } 
    }
    else vd = (vs1 >= P.VU.vlmax) ? 0 : P.VU.elt<uint8_t>(rs2_num, vs1);
    break;
  }
  case e16: {
    auto vs1 = P.VU.elt<uint16_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint16_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint16_t(0); } 
    }
    else vd = (vs1 >= P.VU.vlmax) ? 0 : P.VU.elt<uint16_t>(rs2_num, vs1);
    break;
  }
  case e32: {
    auto vs1 = P.VU.elt<uint32_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint32_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint32_t(0); } 
    }
    else vd = (vs1 >= P.VU.vlmax) ? 0 : P.VU.elt<uint32_t>(rs2_num, vs1);
    break;
  }
  default: {
    auto vs1 = P.VU.elt<uint64_t>(rs1_num, i);
    auto& vd = P.VU.elt<uint64_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint64_t(0); } 
    }
    else vd = (vs1 >= P.VU.vlmax) ? 0 : P.VU.elt<uint64_t>(rs2_num, vs1);
    break;
  }
  }
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
