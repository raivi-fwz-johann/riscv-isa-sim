//vfslide1up.vf vd, vs2, rs1
VI_CHECK_SLIDE(true);

// VI_VFP_LOOP_BASE
VI_VFP_LOOP_GENERAL_BASE
VI_LOOP_ELEMENT_MASK
if (i != 0) {
  switch (P.VU.vsew) {
    case e16: {
      VI_XI_SLIDEUP_PARAMS(e16, 1);
      if (skip) 
      { 
        if (P.VU.vma) 
        { vs2 = 0; vs2 = ~vs2; } 
        else 
          continue; 
      }
      vd = vs2;
    }
    break;
    case e32: {
      VI_XI_SLIDEUP_PARAMS(e32, 1);
      if (skip) 
      { 
        if (P.VU.vma) 
        { vs2 = 0; vs2 = ~vs2; } 
        else 
          continue; 
      }
      vd = vs2;
    }
    break;
    case e64: {
      VI_XI_SLIDEUP_PARAMS(e64, 1);
      if (skip) 
      {
        if (P.VU.vma) 
        { vs2 = 0; vs2 = ~vs2; } 
        else 
          continue; 
      }
      vd = vs2;
    }
    break;
  }
} else {
  switch (P.VU.vsew) {
    case e16:
      if (skip) 
      { 
        if (P.VU.vma) 
        { 
          float16_t val;
          val.v = 0; 
          val.v = ~val.v;; 
          P.VU.elt<float16_t>(rd_num, 0, true) = val; 
        } 
        else 
          continue; 
      }
      else
        P.VU.elt<float16_t>(rd_num, 0, true) = FRS1_H;
      break;
    case e32:
      if (skip) 
      { 
        if (P.VU.vma) 
        { 
          float32_t val;
          val.v = 0; 
          val.v = ~val.v;; 
          P.VU.elt<float32_t>(rd_num, 0, true) = val; 
        } 
        else 
          continue; 
      }
      else
        P.VU.elt<float32_t>(rd_num, 0, true) = FRS1_F;
      break;
    case e64:
      if (skip) 
      { 
        if (P.VU.vma) 
        { 
          float64_t val;
          val.v = 0; 
          val.v = ~val.v;; 
          P.VU.elt<float64_t>(rd_num, 0, true) = val; 
        } 
        else 
          continue; 
      }
      else
        P.VU.elt<float64_t>(rd_num, 0, true) = FRS1_D;
      break;
  }
}
VI_VFP_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
