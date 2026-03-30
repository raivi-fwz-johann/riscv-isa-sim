// vrgather.vx vd, vs2, rs1, vm # vd[i] = (rs1 >= VLMAX) ? 0 : vs2[rs1];
require_align(insn.rd(), P.VU.vflmul);
require_align(insn.rs2(), P.VU.vflmul);
require(insn.rd() != insn.rs2());
require_vm;

reg_t rs1 = RS1;

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK
  switch (sew) {
  case e8:
  {
    uint8_t& vd = P.VU.elt<uint8_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) { vd = 0; vd = ~vd; }
    }
    else vd = rs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint8_t>(rs2_num, rs1);
    break;
  }
  case e16:
  {
    uint16_t& vd = P.VU.elt<uint16_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) { vd = 0; vd = ~vd; }
    }
    else vd = rs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint16_t>(rs2_num, rs1);
    break;
  }
  case e32:
  {
    uint32_t& vd = P.VU.elt<uint32_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) { vd = 0; vd = ~vd; }
    }
    else vd = rs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint32_t>(rs2_num, rs1);
    break;
  }
  default:
  {
    uint64_t& vd = P.VU.elt<uint64_t>(rd_num, i, true);
    if (skip)
    {
      if (P.VU.vma) { vd = 0; vd = ~vd; }
    }
    else vd = rs1 >= P.VU.vlmax ? 0 : P.VU.elt<uint64_t>(rs2_num, rs1);
    break;
  }
  }
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
