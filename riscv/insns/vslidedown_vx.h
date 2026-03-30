//vslidedown.vx vd, vs2, rs1
VI_CHECK_SLIDE(false);

const uint128_t sh = RS1;
VI_GENERAL_LOOP_BASE
VI_LOOP_ELEMENT_MASK

reg_t offset = 0;
bool is_valid = (i + sh) < P.VU.vlmax;

if (is_valid) {
  offset = sh;
}

switch (sew) {
case e8: {
  VI_XI_SLIDEDOWN_PARAMS(e8, offset);
  if (skip)
  {
    if (P.VU.vma)
    { vd = ~uint8_t(0); }
    continue; 
  }
  vd = is_valid ? vs2 : 0;
}
break;
case e16: {
  VI_XI_SLIDEDOWN_PARAMS(e16, offset);
  if (skip)
  {
    if (P.VU.vma)
    { vd = ~uint16_t(0); }
    continue; 
  }
  vd = is_valid ? vs2 : 0;
}
break;
case e32: {
  VI_XI_SLIDEDOWN_PARAMS(e32, offset);
  if (skip)
  {
    if (P.VU.vma)
    { vd = ~uint32_t(0); }
    continue; 
  }
  vd = is_valid ? vs2 : 0;
}
break;
default: {
  VI_XI_SLIDEDOWN_PARAMS(e64, offset);
  if (skip)
  {
    if (P.VU.vma)
    { vd = ~uint64_t(0); }
    continue; 
  }
  vd = is_valid ? vs2 : 0;
}
break;
}
SE_VI_LOOP_END
V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
// VI_LOOP_END
