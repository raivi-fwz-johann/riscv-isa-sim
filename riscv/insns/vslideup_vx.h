//vslideup.vx vd, vs2, rs1
VI_CHECK_SLIDE(true);

const reg_t offset = RS1;

VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK
if (P.VU.vstart->read() < offset && i < offset)
  continue;

switch (sew) {
case e8: {
  VI_XI_SLIDEUP_PARAMS(e8, offset);
  if (skip) 
  {
    if (P.VU.vma) 
    { vd = ~uint8_t(0); } 
    continue; 
  }
  vd = vs2;
}
break;
case e16: {
  VI_XI_SLIDEUP_PARAMS(e16, offset);
  if (skip) 
  { 
    if (P.VU.vma) 
    { vd = ~uint16_t(0); } 
    continue; 
  }
  vd = vs2;
}
break;
case e32: {
  VI_XI_SLIDEUP_PARAMS(e32, offset);
  if (skip) 
  { 
    if (P.VU.vma) 
    { vd = ~uint32_t(0); } 
    continue; 
  }
  vd = vs2;
}
break;
default: {
  VI_XI_SLIDEUP_PARAMS(e64, offset);
  if (skip) 
  { 
    if (P.VU.vma) 
    { vd = ~uint64_t(0); } 
    continue; 
  }
  vd = vs2;
}
break;
}
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_AFTER_OFFSET, EXT_GET_VD)
