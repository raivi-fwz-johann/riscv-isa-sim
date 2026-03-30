// vrgather.vi vd, vs2, zimm5 vm # vd[i] = (zimm5 >= VLMAX) ? 0 : vs2[zimm5];
require_align(insn.rd(), P.VU.vflmul);
require_align(insn.rs2(), P.VU.vflmul);
require(insn.rd() != insn.rs2());
require_vm;

reg_t zimm5 = insn.v_zimm5();

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK

  switch (sew) {
  case e8:
  {
    auto& vd = P.VU.elt<uint8_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint8_t(0); } 
    }
    else vd = zimm5 >= P.VU.vlmax ? 0 : P.VU.elt<uint8_t>(rs2_num, zimm5);
    break;
  }
  case e16:
  {
    auto& vd = P.VU.elt<uint16_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint16_t(0); } 
    }
    else vd = zimm5 >= P.VU.vlmax ? 0 : P.VU.elt<uint16_t>(rs2_num, zimm5);
    break;
  }
  case e32:
  {
    auto& vd = P.VU.elt<uint32_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint32_t(0); } 
    }
    else vd = zimm5 >= P.VU.vlmax ? 0 : P.VU.elt<uint32_t>(rs2_num, zimm5);
    break;
  }
  default:
  {
    auto& vd = P.VU.elt<uint64_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) 
      { vd = ~uint64_t(0); } 
    }
    else vd = zimm5 >= P.VU.vlmax ? 0 : P.VU.elt<uint64_t>(rs2_num, zimm5);
    break;
  }
  }
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
