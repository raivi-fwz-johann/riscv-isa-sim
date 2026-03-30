//vslide1up.vx vd, vs2, rs1
VI_CHECK_SLIDE(true);

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK
if (i != 0) {
  if (sew == e8) {
    VI_XI_SLIDEUP_PARAMS(e8, 1);
    if (skip) 
    {
      if (P.VU.vma) 
      { vd = ~uint8_t(0); } 
      continue; 
    }
    vd = vs2;
  } else if (sew == e16) {
    VI_XI_SLIDEUP_PARAMS(e16, 1);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint16_t(0); } 
      continue; 
    }
    vd = vs2;
  } else if (sew == e32) {
    VI_XI_SLIDEUP_PARAMS(e32, 1);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint32_t(0); } 
      continue; 
    }
    vd = vs2;
  } else if (sew == e64) {
    VI_XI_SLIDEUP_PARAMS(e64, 1);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint64_t(0); } 
      continue; 
    }
    vd = vs2;
  }
} else {
  if (sew == e8) {
    auto& vd = P.VU.elt<uint8_t>(rd_num, 0, true);
    if (skip) 
    {
      if (P.VU.vma) 
      { vd = ~uint8_t(0); } 
      continue; 
    }
    vd = RS1;
  } else if (sew == e16) {
    auto& vd = P.VU.elt<uint16_t>(rd_num, 0, true);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint16_t(0); } 
      continue; 
    }
    vd = RS1;
  } else if (sew == e32) {
    auto& vd = P.VU.elt<uint32_t>(rd_num, 0, true);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint32_t(0); } 
      continue; 
    }
    vd = RS1;
  } else if (sew == e64) {
    auto& vd = P.VU.elt<uint64_t>(rd_num, 0, true);
    if (skip) 
    { 
      if (P.VU.vma) 
      { vd = ~uint64_t(0); } 
      continue; 
    }
    vd = RS1;
  }
}
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
