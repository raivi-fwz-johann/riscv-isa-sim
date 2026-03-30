//vslide1down.vx vd, vs2, rs1
VI_CHECK_SLIDE(false);

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK
if (i != vl - 1) {
  switch (sew) {
  case e8: {
    VI_XI_SLIDEDOWN_PARAMS(e8, 1);
    if (skip) 
    {
      if (P.VU.vma) vd = ~uint8_t(0);
      continue; 
    }
    vd = vs2;
  }
  break;
  case e16: {
    VI_XI_SLIDEDOWN_PARAMS(e16, 1);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint16_t(0);
      continue; 
    }
    vd = vs2;
  }
  break;
  case e32: {
    VI_XI_SLIDEDOWN_PARAMS(e32, 1);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint32_t(0);
      continue; 
    }
    vd = vs2;
  }
  break;
  default: {
    VI_XI_SLIDEDOWN_PARAMS(e64, 1);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint64_t(0);
      continue; 
    }
    vd = vs2;
  }
  break;
  }
} else {
  switch (sew) {
  case e8: {
    auto& vd = P.VU.elt<uint8_t>(rd_num, vl - 1, true);
    if (skip) 
    {
      if (P.VU.vma) vd = ~uint8_t(0);
      continue; 
    }
    vd = RS1;
    break;
  }
  case e16: {
    auto& vd = P.VU.elt<uint16_t>(rd_num, vl - 1, true);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint16_t(0);
      continue; 
    }
    vd = RS1;
    break;
  }
  case e32: {
    auto& vd = P.VU.elt<uint32_t>(rd_num, vl - 1, true);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint32_t(0);
      continue; 
    }
    vd = RS1;
    break;
  }
  default: {
    auto& vd = P.VU.elt<uint64_t>(rd_num, vl - 1, true);
    if (skip) 
    { 
      if (P.VU.vma) vd = ~uint64_t(0);
      continue; 
    }
    vd = RS1;
    break;
  }
  }
}
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
