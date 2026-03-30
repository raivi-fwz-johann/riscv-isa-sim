// vmpopc rd, vs2, vm
require(P.VU.vsew >= e8 && P.VU.vsew <= e64);
require_vector(true);
reg_t vl = P.VU.vl->read();
reg_t sew = P.VU.vsew;
reg_t rd_num = insn.rd();
reg_t rs2_num = insn.rs2();
require(P.VU.vstart->read() == 0);
require_vm;
require_align(rd_num, P.VU.vflmul);
require_noover(rd_num, P.VU.vflmul, rs2_num, 1);

int cnt = 0;
for (reg_t i = 0; i < vl; ++i) {
  VI_LOOP_ELEMENT_MASK 
  bool do_mask = P.VU.mask_elt(0, i);

  bool has_one = false;
  if (insn.v_vm() == 1 || (insn.v_vm() == 0 && do_mask)) {
    if (P.VU.mask_elt(rs2_num, i)) {
      has_one = true;
    }
  }

  bool use_ori = (insn.v_vm() == 0) && !do_mask;
  switch (sew) {
  case e8: {
    auto& vd = P.VU.elt<uint8_t>(rd_num, i, true);
    if (skip) { if (P.VU.vma) vd = ~uint8_t(0); else continue; }
    vd = use_ori ? P.VU.elt<uint8_t>(rd_num, i) : cnt;
    break;
  }
  case e16: {
    auto& vd = P.VU.elt<uint16_t>(rd_num, i, true);
    if (skip) { if (P.VU.vma) vd = ~uint16_t(0); else continue; }
    vd = use_ori ? P.VU.elt<uint16_t>(rd_num, i) : cnt;
    break;
  }
  case e32: {
    auto& vd = P.VU.elt<uint32_t>(rd_num, i, true);
    if (skip) { if (P.VU.vma) vd = ~uint32_t(0); else continue; }
    vd = use_ori ? P.VU.elt<uint32_t>(rd_num, i) : cnt;
    break;
  }
  default: {
    auto& vd = P.VU.elt<uint64_t>(rd_num, i, true);
    if (skip) { if (P.VU.vma) vd = ~uint64_t(0); else continue; }
    vd = use_ori ? P.VU.elt<uint64_t>(rd_num, i) : cnt;
    break;
  }
  }

  if (has_one) {
    cnt++;
  }
}
V_HANDLE_TAIL(VEC_COMMON, SE_GET_VD)

