#ifndef _RISCV_V_EXT_MACROS_EXTENSION_H
#define _RISCV_V_EXT_MACROS_EXTENSION_H

#include "v_ext_macros.h"

#include <limits>



#define MAX(x, y) (x >= y ? x : y)

#define SAVE_VMA_VTA bool vma__ = P.VU.vma; bool vta__ = P.VU.vta;
#define SET_VMA_VTA_FOR_VS_VD_OVERLAP if (insn.rd()==insn.rs2()) {P.VU.vma=true; P.VU.vta=true;}
#define RESTORE_VMA_VTA P.VU.vma=vma__; P.VU.vta=vta__;

// #define V_FILL_ONE (vd |= std::numeric_limits<uint64_t>::max());
#define V_FILL_ONE {vd=0; vd=~vd;}

#define VF_FILL_ONE \
  switch (sizeof(vd)*8) { \
    case 8: \
    *(uint8_t*)&vd |= std::numeric_limits<uint8_t>::max(); \
    break; \
    case 16: \
    *(uint16_t*)&vd |= std::numeric_limits<uint16_t>::max(); \
    break; \
    case 32: \
    *(uint32_t*)&vd |= std::numeric_limits<uint32_t>::max(); \
    break; \
    case 64: \
    default: \
    *(uint64_t*)&vd |= std::numeric_limits<uint64_t>::max(); \
    break; \
  }

#define VEC_VLS(OP, elt_type) \
  OP(elt_type); \
  V_FILL_ONE 

#define VEC_COMMON(BODY) \
  if (sew == e8) { \
    BODY(e8); \
    V_FILL_ONE \
  } else if (sew == e16) { \
    BODY(e16); \
    V_FILL_ONE \
  } else if (sew == e32) { \
    BODY(e32); \
    V_FILL_ONE \
  } else if (sew == e64) { \
    BODY(e64); \
    V_FILL_ONE \
  }

#define VEC_AFTER_OFFSET(BODY) \
  if (i<offset && i<P.VU.vl->read()) continue; \
  if (sew == e8) { \
    BODY(e8); \
    V_FILL_ONE \
  } else if (sew == e16) { \
    BODY(e16); \
    V_FILL_ONE \
  } else if (sew == e32) { \
    BODY(e32); \
    V_FILL_ONE \
  } else if (sew == e64) { \
    BODY(e64); \
    V_FILL_ONE \
  }

#define VEC_NARROW(BODY) \
  if (sew == e8) { \
    BODY(e8, e16); \
    V_FILL_ONE \
  } else if (sew == e16) { \
    BODY(e16, e32); \
    V_FILL_ONE \
  } else if (sew == e32) { \
    BODY(e32, e64); \
    V_FILL_ONE \
  }

#define VEC_WIDEN(BODY) \
  if (sew == e8) { \
    BODY(e8); \
    V_FILL_ONE \
  } else if (sew == e16) { \
    BODY(e16); \
    V_FILL_ONE \
  } else if (sew == e32) { \
    BODY(e32); \
    V_FILL_ONE \
  }

#define VEC_WIDEN_TRUE(BODY) \
  if (sew == e8) { \
    BODY(e16); \
    V_FILL_ONE \
  } else if (sew == e32) { \
    BODY(e64); \
    V_FILL_ONE \
  } 

#define VEC_VF_MERGE(BODY) \
  if (P.VU.vsew == e16) { \
    BODY(16); \
    VF_FILL_ONE \
  } else if (P.VU.vsew == e32) { \
    BODY(32); \
    VF_FILL_ONE \
  } else if (P.VU.vsew == e64) { \
    BODY(64); \
    VF_FILL_ONE \
  }

#define V_HANDLE_MASK(BODY1, BODY2) \
  if (P.VU.vma) { \
    BODY1(BODY2); \
  }

#define SE_VI_LOOP_ELEMENT_SKIP(BODY1, BODY2) \
  VI_MASK_VARS \
  if (insn.v_vm() == 0) { \
    BODY1; \
    bool skip = ((P.VU.elt<uint64_t>(0, midx) >> mpos) & 0x1) == 0; \
    if (skip) { \
        BODY2; \
        continue; \
    } \
  }

#define SE_VI_LOOP_CMP_BASE \
  require(P.VU.vsew >= e8 && P.VU.vsew <= e64); \
  require_vector(true); \
  reg_t vl = P.VU.vl->read(); \
  reg_t sew = P.VU.vsew; \
  reg_t UNUSED rd_num = insn.rd(); \
  reg_t UNUSED rs1_num = insn.rs1(); \
  reg_t rs2_num = insn.rs2(); \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) { \
    VI_LOOP_ELEMENT_MASK; \
    uint64_t mmask = UINT64_C(1) << mpos; \
    uint64_t &vdi = P.VU.elt<uint64_t>(insn.rd(), midx, true); \
    uint64_t res = 0;

#define SE_VI_LOOP_CMP_END \
    vdi = (vdi & ~mmask) | (((res) << mpos) & mmask); \
  } \
  /*code ext: always tail-agnostic for vmask instructions */ \
  if (vl>0) \
  { \
      for (reg_t i = vl; i < (P.VU.vstart->read() + P.VU.VLEN); ++i) { \
        int midx = i / 64; \
        int mpos = i % 64; \
        uint64_t &res = P.VU.elt<uint64_t>(insn.rd(), midx, true); \
        res = res | (1ULL << mpos); \
      } \
  } \
  P.VU.vstart->write(0);

// comparison result to masking register
#ifdef VI_LOOP_CMP_BODY
#undef VI_LOOP_CMP_BODY
#define VI_LOOP_CMP_BODY(PARAMS, BODY) \
  SE_VI_LOOP_CMP_BASE \
  INSNS_BASE(PARAMS, BODY) \
  if (skip) { if (P.VU.vma) res=1; else continue; } \
  SE_VI_LOOP_CMP_END
#endif

#ifdef VI_VX_ULOOP_CMP
#undef VI_VX_ULOOP_CMP
#define VI_VX_ULOOP_CMP(BODY) \
  VI_CHECK_MSS(false); \
  VI_LOOP_CMP_BODY(VX_UCMP_PARAMS, BODY)
#endif

#define SE_VI_LOOP_BASE(BODY1, BODY2) \
  VI_GENERAL_LOOP_BASE \
  SE_VI_LOOP_ELEMENT_SKIP({}, V_HANDLE_MASK(BODY1, BODY2));

#define SE_VI_LOOP_NSHIFT_BASE(BODY1, BODY2) \
  VI_GENERAL_LOOP_BASE; \
  SE_VI_LOOP_ELEMENT_SKIP({ \
    require(!(insn.rd() == 0 && P.VU.vflmul > 1)); \
  }, V_HANDLE_MASK(BODY1, BODY2));

#define SE_VI_LOOP_END \
  VI_LOOP_END_BASE

#define V_HANDLE_TAIL_MASK_OPERATION_EEW_TA_NOVL(PER_ELEM_OP, EEW) \
  if (P.VU.vstart->read() < P.VU.vl->read() && P.VU.vl->read()>0 ) { \
    for (reg_t i = (P.VU.vl->read()+7)/EEW; i < P.VU.VLEN/EEW; ++i) { \
      PER_ELEM_OP \
    } \
    P.VU.vstart->write(0); \
  }

#define V_HANDLE_TAIL_MASK_OPERATION_EEW_TA_NOVL_M(PER_ELEM_OP, EEW) \
  if (P.VU.vstart->read() < P.VU.vl->read()) { \
    if (vl%8!=0) { \
      auto& vd = P.VU.elt<uint8_t>(rd_num, vl/8, true); \
      vd |= ~((uint8_t(0x01)<<(vl%8))-1); \
    } \
    for (reg_t i = (P.VU.vl->read()+7)/EEW; i < P.VU.VLEN/EEW; ++i) { \
      PER_ELEM_OP \
    } \
    P.VU.vstart->write(0); \
  }

#define V_HANDLE_TAIL_MASK_OPERATION(PER_ELEM_OP) \
  if (P.VU.vta&& P.VU.vstart->read() < P.VU.vl->read()) { \
    for (reg_t i = (P.VU.vl->read()+7)/8; i < MAX(P.VU.vlmax, P.VU.VLEN / 8); ++i) { \
      PER_ELEM_OP \
    } \
    P.VU.vstart->write(0); \
  }

#define V_HANDLE_TAIL_OPERATION_EEW_SINGLE_TA_NOVL(PER_ELEM_OP, EEW) \
  if (P.VU.vta&& P.VU.vstart->read() < P.VU.vl->read()) { \
    for (reg_t i = 1; i < P.VU.VLEN/EEW; ++i) { \
      PER_ELEM_OP \
    } \
  } \
  P.VU.vstart->write(0);

#define V_HANDLE_TAIL_OPERATION_EEW(PER_ELEM_OP, EEW) \
  if (P.VU.vta&& P.VU.vstart->read() < P.VU.vl->read()) { \
    reg_t vl = P.VU.vl->read(); \
    for (reg_t i = vl; i < MAX(P.VU.vlmax, P.VU.VLEN / EEW); ++i) { \
      PER_ELEM_OP \
    } \
  } \
  P.VU.vstart->write(0);

#define V_HANDLE_TAIL(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    reg_t vl = P.VU.vl->read(); \
    for (reg_t i = vl; i < MAX(P.VU.vlmax, P.VU.VLEN / P.VU.vsew); ++i) { \
      BODY1(BODY2) \
    } \
  } \
  P.VU.vstart->write(0);

#define V_HANDLE_TAIL_REDUCTION(BODY1, BODY2) \
  if (P.VU.vta&& P.VU.vstart->read() < P.VU.vl->read()) { \
    for (reg_t i = 1; i < P.VU.VLEN / P.VU.vsew; ++i) { \
      BODY1(BODY2) \
    } \
    P.VU.vstart->write(0); \
  }

#define V_HANDLE_TAIL_REDUCTION_WIDEN(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    for (reg_t i = 2; i < P.VU.VLEN / P.VU.vsew; ++i) { \
      BODY1(BODY2) \
    } \
  } \
  P.VU.vstart->write(0); 

#define V_HANDLE_TAIL_VCOMPRESS(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    reg_t vl = pos; \
    for (reg_t i = vl; i < MAX(P.VU.vlmax, P.VU.VLEN / P.VU.vsew); ++i) { \
      BODY1(BODY2) \
    } \
  } \
  P.VU.vstart->write(0);

#define V_HANDLE_TAIL_OFFSET(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    reg_t vl = P.VU.vl->read(); \
    for (reg_t i = vl; i < MAX(P.VU.vlmax, P.VU.VLEN / P.VU.vsew); ++i) { \
      BODY1(BODY2) \
    } \
  } \
  P.VU.vstart->write(0);
      
#define V_HANDLE_TAIL_WIDEN(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    reg_t vl = P.VU.vl->read(); \
    for (reg_t i = vl*2; i < MAX(2*P.VU.vlmax, P.VU.VLEN/P.VU.vsew); ++i) { \
      BODY1(BODY2) \
    } \
  } \
  P.VU.vstart->write(0); 

#define V_HANDLE_TAIL_VMV_S_X(BODY1, BODY2) \
  if (P.VU.vta && P.VU.vstart->read() < P.VU.vl->read()) { \
    auto rd_num = insn.rd(); \
    reg_t vl = P.VU.vl->read(); \
    auto sew = P.VU.vsew; \
    if (vl > 0 && P.VU.vstart->read() < vl) { \
      for (reg_t i = 1; i < P.VU.VLEN / P.VU.vsew; ++i) { \
        BODY1(BODY2) \
      } \
    } \
  }

// genearl VXI signed/unsigned loop
#ifdef VI_VV_ULOOP
#undef VI_VV_ULOOP
#define VI_VV_ULOOP(BODY) \
  VI_CHECK_SSS(true) \
  SE_VI_LOOP_BASE(VEC_COMMON, VV_U_PARAMS) \
  if (sew == e8) { \
    VV_U_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VV_U_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VV_U_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VV_U_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VV_U_PARAMS)
#endif

#ifdef VI_VV_LOOP
#undef VI_VV_LOOP
#define VI_VV_LOOP(BODY) \
  VI_CHECK_SSS(true) \
  SE_VI_LOOP_BASE(VEC_COMMON, VV_PARAMS) \
  if (sew == e8) { \
    VV_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VV_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VV_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VV_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VV_PARAMS)
#endif

#ifdef VI_V_ULOOP
#undef VI_V_ULOOP
#define VI_V_ULOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, V_U_PARAMS) \
  if (sew == e8) { \
    V_U_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    V_U_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    V_U_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    V_U_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, V_U_PARAMS)
#endif

#ifdef VI_VX_ULOOP
#undef VI_VX_ULOOP
#define VI_VX_ULOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, VX_U_PARAMS) \
  if (sew == e8) { \
    VX_U_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VX_U_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VX_U_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VX_U_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VX_U_PARAMS)
#endif

#ifdef VI_VX_LOOP
#undef VI_VX_LOOP
#define VI_VX_LOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, VX_PARAMS) \
  if (sew == e8) { \
    VX_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VX_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VX_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VX_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VX_PARAMS)
#endif

#ifdef VI_VI_ULOOP
#undef VI_VI_ULOOP
#define VI_VI_ULOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, VI_U_PARAMS) \
  if (sew == e8) { \
    VI_U_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VI_U_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VI_U_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VI_U_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VI_U_PARAMS)
#endif

#ifdef VI_VI_LOOP
#undef VI_VI_LOOP
#define VI_VI_LOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, VI_PARAMS) \
  if (sew == e8) { \
    VI_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VI_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VI_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VI_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VI_PARAMS)
#endif

// signed unsigned operation loop (e.g. mulhsu)
#ifdef VI_VV_SU_LOOP
#undef VI_VV_SU_LOOP
#define VI_VV_SU_LOOP(BODY) \
  VI_CHECK_SSS(true) \
  SE_VI_LOOP_BASE(VEC_COMMON, VV_SU_PARAMS) \
  if (sew == e8) { \
    VV_SU_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VV_SU_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VV_SU_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VV_SU_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VV_SU_PARAMS)
#endif

#ifdef VI_VX_SU_LOOP
#undef VI_VX_SU_LOOP
#define VI_VX_SU_LOOP(BODY) \
  VI_CHECK_SSS(false) \
  SE_VI_LOOP_BASE(VEC_COMMON, VX_SU_PARAMS) \
  if (sew == e8) { \
    VX_SU_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VX_SU_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VX_SU_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VX_SU_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VX_SU_PARAMS)
#endif

// narrow operation loop
#ifdef VI_VV_LOOP_NARROW
#undef VI_VV_LOOP_NARROW
#define VI_VV_LOOP_NARROW(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(true); \
  SE_VI_LOOP_BASE(VEC_NARROW, VV_NARROW_PARAMS) \
  if (sew == e8) { \
    VV_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VV_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VV_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VV_NARROW_PARAMS) \
  RESTORE_VMA_VTA
#endif

#ifdef VI_VX_LOOP_NARROW
#undef VI_VX_LOOP_NARROW
#define VI_VX_LOOP_NARROW(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  SE_VI_LOOP_BASE(VEC_NARROW, VX_NARROW_PARAMS) \
  if (sew == e8) { \
    VX_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VX_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VX_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VX_NARROW_PARAMS) \
  RESTORE_VMA_VTA 
#endif

#ifdef VI_VI_LOOP_NARROW
#undef VI_VI_LOOP_NARROW
#define VI_VI_LOOP_NARROW(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  SE_VI_LOOP_BASE(VEC_NARROW, VI_NARROW_PARAMS) \
  if (sew == e8) { \
    VI_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VI_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VI_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VI_NARROW_PARAMS) \
  RESTORE_VMA_VTA 
#endif

#ifdef VI_VI_LOOP_NSHIFT
#undef VI_VI_LOOP_NSHIFT
#define VI_VI_LOOP_NSHIFT(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  SE_VI_LOOP_NSHIFT_BASE(VEC_NARROW, VI_NARROW_PARAMS) \
  if (sew == e8) { \
    VI_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VI_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VI_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VI_NARROW_PARAMS) \
  RESTORE_VMA_VTA
#endif

#ifdef VI_VX_LOOP_NSHIFT
#undef VI_VX_LOOP_NSHIFT
#define VI_VX_LOOP_NSHIFT(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  SE_VI_LOOP_NSHIFT_BASE(VEC_NARROW, VX_NARROW_PARAMS) \
  if (sew == e8) { \
    VX_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VX_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VX_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VX_NARROW_PARAMS) \
  RESTORE_VMA_VTA
#endif

#ifdef VI_VV_LOOP_NSHIFT
#undef VI_VV_LOOP_NSHIFT
#define VI_VV_LOOP_NSHIFT(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(true); \
  SE_VI_LOOP_NSHIFT_BASE(VEC_NARROW, VV_NARROW_PARAMS) \
  if (sew == e8) { \
    VV_NARROW_PARAMS(e8, e16) \
    BODY; \
  } else if (sew == e16) { \
    VV_NARROW_PARAMS(e16, e32) \
    BODY; \
  } else if (sew == e32) { \
    VV_NARROW_PARAMS(e32, e64) \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_NARROW, VV_NARROW_PARAMS) \
  RESTORE_VMA_VTA
#endif

// widen operation loop
#ifdef VI_VV_LOOP_WIDEN
#undef VI_VV_LOOP_WIDEN
#define VI_VV_LOOP_WIDEN(BODY) \
SAVE_VMA_VTA \
SET_VMA_VTA_FOR_VS_VD_OVERLAP \
VI_GENERAL_LOOP_BASE \
VI_LOOP_ELEMENT_MASK \
  if (sew == e8) { \
    uint16_t& vd_w = P.VU.elt<uint16_t>(rd_num, i, true); \
    if (skip) \
    { \
      if (P.VU.vma) { vd_w = 0; vd_w = ~vd_w; } \
      continue; \
    } \
    VV_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    uint32_t& vd_w = P.VU.elt<uint32_t>(rd_num, i, true); \
    if (skip) \
    { \
      if (P.VU.vma) { vd_w = 0; vd_w = ~vd_w; } \
      continue; \
    } \
    VV_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    uint64_t& vd_w = P.VU.elt<uint64_t>(rd_num, i, true); \
    if (skip) \
    { \
      if (P.VU.vma) { vd_w = 0; vd_w = ~vd_w; } \
      continue; \
    } \
    VV_PARAMS(e32); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL_WIDEN(VEC_WIDEN, VV_PARAMS) \
  RESTORE_VMA_VTA
#endif

#ifdef VI_VX_LOOP_WIDEN
#undef VI_VX_LOOP_WIDEN
#define VI_VX_LOOP_WIDEN(BODY) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_GENERAL_LOOP_BASE \
  VI_LOOP_ELEMENT_MASK \
  if (sew == e8) { \
    auto& vd_w1 = P.VU.elt<uint16_t>(rd_num, i, true); \
    if (skip) \
    { if (P.VU.vma) \
      { vd_w1=0; vd_w1=~vd_w1; } \
      continue; \
    } \
    VX_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    auto& vd_w1 = P.VU.elt<uint32_t>(rd_num, i, true); \
    if (skip) \
    { if (P.VU.vma) \
      { vd_w1=0; vd_w1=~vd_w1; } \
      continue; \
    } \
    VX_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    auto& vd_w1 = P.VU.elt<uint64_t>(rd_num, i, true); \
    if (skip) \
    { if (P.VU.vma) \
      { vd_w1=0; vd_w1=~vd_w1; } \
      continue; \
    } \
    VX_PARAMS(e32); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL_WIDEN(VEC_WIDEN, VX_PARAMS) \
  RESTORE_VMA_VTA
#endif


#ifdef VI_VV_MERGE_LOOP
#undef VI_VV_MERGE_LOOP
#define VI_VV_MERGE_LOOP(BODY) \
  VI_CHECK_SSS(true); \
  VI_MERGE_LOOP_BASE \
  if (sew == e8) { \
    VV_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VV_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VV_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VV_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VV_PARAMS)
#endif

#ifdef VI_VX_MERGE_LOOP
#undef VI_VX_MERGE_LOOP
#define VI_VX_MERGE_LOOP(BODY) \
  VI_CHECK_SSS(false); \
  VI_MERGE_LOOP_BASE \
  if (sew == e8) { \
    VX_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VX_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VX_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VX_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VX_PARAMS)
#endif

#ifdef VI_VI_MERGE_LOOP
#undef VI_VI_MERGE_LOOP
#define VI_VI_MERGE_LOOP(BODY) \
  VI_CHECK_SSS(false); \
  VI_MERGE_LOOP_BASE \
  if (sew == e8) { \
    VI_PARAMS(e8); \
    BODY; \
  } else if (sew == e16) { \
    VI_PARAMS(e16); \
    BODY; \
  } else if (sew == e32) { \
    VI_PARAMS(e32); \
    BODY; \
  } else if (sew == e64) { \
    VI_PARAMS(e64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, VI_PARAMS)
#endif

#ifdef VI_VF_MERGE_LOOP
#undef VI_VF_MERGE_LOOP
#define VI_VF_MERGE_LOOP(BODY) \
  VI_CHECK_SSS(false); \
  VI_VFP_COMMON \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) { \
  VI_MERGE_VARS \
  if (P.VU.vsew == e16) { \
    VFP_VF_PARAMS(16); \
    BODY; \
  } else if (P.VU.vsew == e32) { \
    VFP_VF_PARAMS(32); \
    BODY; \
  } else if (P.VU.vsew == e64) { \
    VFP_VF_PARAMS(64); \
    BODY; \
  } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_VF_MERGE, VFP_VF_PARAMS)
#endif

#define SE_VI_LOOP_CARRY_END \
    vd = (vd & ~mmask) | (((res) << mpos) & mmask); \
  } \
  /*code ext: always tail-agnostic for vmask instructions */ \
  if (vl>0) { \
      for (reg_t i = vl; i < (P.VU.vstart->read() + P.VU.VLEN); ++i) { \
        int midx = i / 64; \
        int mpos = i % 64; \
        uint64_t &res = P.VU.elt<uint64_t>(insn.rd(), midx, true); \
        res = res | (1ULL << mpos); \
      } \
  }\
  P.VU.vstart->write(0);

#define SE_GET_VD(x) \
  auto &vd = (*p).VU.elt<type_sew_t<x>::type>(rd_num, i, true);

#define SE_GET_VLS_VD(type) \
  auto &vd = (*p).VU.elt<type>(rd_num, i, true);

// carry/borrow bit loop
#ifdef VI_VV_LOOP_CARRY
#undef VI_VV_LOOP_CARRY
#define VI_VV_LOOP_CARRY(BODY) \
  VI_CHECK_MSS(true); \
  VI_LOOP_CARRY_BASE \
    if (sew == e8) { \
      VV_CARRY_PARAMS(e8) \
      BODY; \
    } else if (sew == e16) { \
      VV_CARRY_PARAMS(e16) \
      BODY; \
    } else if (sew == e32) { \
      VV_CARRY_PARAMS(e32) \
      BODY; \
    } else if (sew == e64) { \
      VV_CARRY_PARAMS(e64) \
      BODY; \
    } \
  SE_VI_LOOP_CARRY_END
#endif

#ifdef VI_XI_LOOP_CARRY
#undef VI_XI_LOOP_CARRY
#define VI_XI_LOOP_CARRY(BODY) \
  VI_CHECK_MSS(false); \
  VI_LOOP_CARRY_BASE \
    if (sew == e8) { \
      XI_CARRY_PARAMS(e8) \
      BODY; \
    } else if (sew == e16) { \
      XI_CARRY_PARAMS(e16) \
      BODY; \
    } else if (sew == e32) { \
      XI_CARRY_PARAMS(e32) \
      BODY; \
    } else if (sew == e64) { \
      XI_CARRY_PARAMS(e64) \
      BODY; \
    } \
  SE_VI_LOOP_CARRY_END 
#endif

#ifdef VI_VV_LOOP_WITH_CARRY
#undef VI_VV_LOOP_WITH_CARRY
#define VI_VV_LOOP_WITH_CARRY(BODY) \
  VI_CHECK_SSS(true); \
  VI_LOOP_WITH_CARRY_BASE \
    if (sew == e8) { \
      VV_WITH_CARRY_PARAMS(e8) \
      BODY; \
    } else if (sew == e16) { \
      VV_WITH_CARRY_PARAMS(e16) \
      BODY; \
    } else if (sew == e32) { \
      VV_WITH_CARRY_PARAMS(e32) \
      BODY; \
    } else if (sew == e64) { \
      VV_WITH_CARRY_PARAMS(e64) \
      BODY; \
    } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, SE_GET_VD)
#endif

#ifdef VI_XI_LOOP_WITH_CARRY
#undef VI_XI_LOOP_WITH_CARRY
#define VI_XI_LOOP_WITH_CARRY(BODY) \
  VI_CHECK_SSS(false); \
  VI_LOOP_WITH_CARRY_BASE \
    if (sew == e8) { \
      XI_WITH_CARRY_PARAMS(e8) \
      BODY; \
    } else if (sew == e16) { \
      XI_WITH_CARRY_PARAMS(e16) \
      BODY; \
    } else if (sew == e32) { \
      XI_WITH_CARRY_PARAMS(e32) \
      BODY; \
    } else if (sew == e64) { \
      XI_WITH_CARRY_PARAMS(e64) \
      BODY; \
    } \
  SE_VI_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, SE_GET_VD)
#endif

#define ELEMENT_SKIP ((insn.v_vm() == 0) && (((P.VU.elt<uint64_t>(0, i / 64) >> (i % 64)) & 0x1) == 0))

#ifdef VI_LD
#undef VI_LD
#define VI_LD(stride, offset, elt_width, is_mask_ldst)                                             \
  const reg_t nf = insn.v_nf() + 1;                                                                \
  reg_t UNUSED sew = P.VU.vsew;                                                                    \
  reg_t UNUSED eew = sizeof(elt_width##_t)*8;                                                      \
  reg_t rd_num = insn.rd();                                                                        \
  reg_t i;                                                                                         \
  VI_CHECK_LOAD(elt_width, is_mask_ldst);                                                          \
  const reg_t vl = is_mask_ldst ? ((P.VU.vl->read() + 7) / 8) : P.VU.vl->read();                   \
  const reg_t baseAddr = RS1;                                                                      \
  const reg_t vd = insn.rd();                                                                      \
  if (P.VU.vstart->read()<vl) {                                                                    \
    for (i = P.VU.vstart->read(); i < vl; ++i) {                                                   \
      P.VU.vstart->write(i);                                                                       \
      VI_LOOP_ELEMENT_MASK                                                                         \
      for (reg_t fn = 0; fn < nf; ++fn) {                                                          \
        if (i >= vl || i < P.VU.vstart->read() ) continue;                                         \
        elt_width##_t val;                                                                         \
        if (skip) { if (P.VU.vma) { val = 0; val = ~val; } else continue; }                        \
        else val = MMU.load<elt_width##_t>(baseAddr + (stride) + (offset) * sizeof(elt_width##_t), \
          xlate_flags_t{enable_misalign : MMU.is_vector_misaligned_enabled(), enable_16B_check : MMU.is_vector_16B_check()});                    \
        VI_STRIP(i);                                                                               \
        P.VU.elt<elt_width##_t>(vd + fn * emul, vreg_inx, true) = val;                             \
      }                                                                                            \
    }                                                                                              \
    if (is_mask_ldst) {                                                                            \
        V_HANDLE_TAIL_MASK_OPERATION_EEW_TA_NOVL(VEC_VLS(SE_GET_VLS_VD,elt_width##_t), 8)          \
    } else {                                                                                       \
      for (reg_t fn = 0; fn < nf; ++fn) {                                                          \
        V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,elt_width##_t), eew)                     \
        rd_num = (rd_num+emul) % 32;                                                               \
      }                                                                                            \
    }                                                                                              \
  }
#endif

/*
  float vemul = ((float)veew / P.VU.vsew * P.VU.vflmul);                 
  reg_t UNUSED emul = vemul < 1 ? 1 : vemul;                             
  */

#ifdef VI_LD_INDEX
#undef VI_LD_INDEX
#define VI_LD_INDEX(elt_width, is_seg)                                   \
  const reg_t nf = insn.v_nf() + 1;                                      \
  VI_CHECK_LD_INDEX(elt_width);                                          \
  const reg_t vl = P.VU.vl->read();                                      \
  const reg_t baseAddr = RS1;                                            \
  const reg_t vd = insn.rd();                                            \
  reg_t rd_num = insn.rd();                                              \
  reg_t sew = P.VU.vsew;                                                 \
  reg_t lmul = P.VU.vflmul < 1? 1.0: P.VU.vflmul;                        \
  if (!is_seg)                                                           \
    require(nf == 1);                                                    \
  VI_DUPLICATE_VREG(insn.rs2(), elt_width);                              \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) {                     \
    P.VU.vstart->write(i);                                               \
    VI_LOOP_ELEMENT_MASK                                                 \
    for (reg_t fn = 0; fn < nf; ++fn) {                                  \
      if (P.VU.vsew == e8) {                                             \
        uint8_t val;                                                     \
        if (skip) {                                                      \
          if (P.VU.vma) {                                                \
            val  = 0xff;                                                 \
          }                                                              \
          else continue;                                                 \
        }                                                                \
        else {                                                           \
          val = MMU.load<uint8_t>(baseAddr + index[i] + fn * 1);         \
        }                                                                \
        VI_STRIP(i);                                                     \
        P.VU.elt<uint8_t>(vd + fn * flmul, vreg_inx, true) = val;        \
      }                                                                  \
      if (P.VU.vsew == e16) {                                            \
        uint16_t val;                                                    \
        if (skip) {                                                      \
          if (P.VU.vma) {                                                \
            val = 0xffff;                                                \
          }                                                              \
          else continue;                                                 \
        }                                                                \
        else {                                                           \
          val = MMU.load<uint16_t>(baseAddr + index[i] + fn * 2);        \
        }                                                                \
        VI_STRIP(i);                                                     \
        P.VU.elt<uint16_t>(vd + fn * flmul, vreg_inx, true) = val;       \
      }                                                                  \
      if (P.VU.vsew == e32) {                                            \
        uint32_t val;                                                    \
        if (skip) {                                                      \
          if (P.VU.vma) {                                                \
            val = 0xffffffff;                                            \
          }                                                              \
          else continue;                                                 \
        }                                                                \
        else {                                                           \
          val = MMU.load<uint32_t>(baseAddr + index[i] + fn * 4);        \
        }                                                                \
        VI_STRIP(i);                                                     \
        P.VU.elt<uint32_t>(vd + fn * flmul, vreg_inx, true) = val;       \
      }                                                                  \
      if (P.VU.vsew == e64) {                                            \
        uint64_t val;                                                    \
        if (skip) {                                                      \
          if (P.VU.vma) {                                                \
            val = 0xffffffffffffffff;                                    \
          }                                                              \
          else continue;                                                 \
        }                                                                \
        else {                                                           \
          val = MMU.load<uint64_t>(baseAddr + index[i] + fn * 8);        \
        }                                                                \
        VI_STRIP(i);                                                     \
        P.VU.elt<uint64_t>(vd + fn * flmul, vreg_inx, true) = val;       \
      }                                                                  \
    }                                                                    \
  }                                                                      \
  for (reg_t fn = 0; fn < nf; ++fn) {                                    \
    if (P.VU.vsew == e8) {                                               \
      V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,int8_t), sew);   \
    }                                                                    \
    else if (P.VU.vsew == e16) {                                         \
      V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,int16_t), sew);  \
    }                                                                    \
    else if (P.VU.vsew == e32) {                                         \
      V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,int32_t), sew);  \
    }                                                                    \
    else if (P.VU.vsew == e64) {                                         \
      V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,int64_t), sew);  \
    }                                                                    \
    rd_num = (rd_num + lmul) % 32;                                       \
  }                                                                      \
  P.VU.vstart->write(0);
#endif

#ifdef VI_ST
#undef VI_ST
#define VI_ST(stride, offset, elt_width, is_mask_ldst)                                      \
  const reg_t nf = insn.v_nf() + 1;                                                         \
  VI_CHECK_STORE(elt_width, is_mask_ldst);                                                  \
  const reg_t vl = is_mask_ldst ? ((P.VU.vl->read() + 7) / 8) : P.VU.vl->read();            \
  const reg_t baseAddr = RS1;                                                               \
  const reg_t vs3 = insn.rd();                                                              \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) {                                        \
    VI_STRIP(i)                                                                             \
    P.VU.vstart->write(i);                                                                  \
    for (reg_t fn = 0; fn < nf; ++fn) {                                                     \
      elt_width##_t val = P.VU.elt<elt_width##_t>(vs3 + fn * emul, vreg_inx);               \
      MMU.store<elt_width##_t>(baseAddr + (stride) + (offset) * sizeof(elt_width##_t), val, \
        xlate_flags_t{enable_misalign : MMU.is_vector_misaligned_enabled(), enable_16B_check : MMU.is_vector_16B_check()}, ELEMENT_SKIP); \
    }                                                                                       \
  }                                                                                         \
  P.VU.vstart->write(0);
#endif

#ifdef VI_ST_INDEX
#undef VI_ST_INDEX
#define VI_ST_INDEX(elt_width, is_seg)                                                                                 \
  const reg_t nf = insn.v_nf() + 1;                                                                                    \
  VI_CHECK_ST_INDEX(elt_width);                                                                                        \
  const reg_t vl = P.VU.vl->read();                                                                                    \
  const reg_t baseAddr = RS1;                                                                                          \
  const reg_t vs3 = insn.rd();                                                                                         \
  if (!is_seg)                                                                                                         \
    require(nf == 1);                                                                                                  \
  VI_DUPLICATE_VREG(insn.rs2(), elt_width);                                                                            \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) {                                                                   \
    VI_STRIP(i)                                                                                                        \
    P.VU.vstart->write(i);                                                                                             \
    for (reg_t fn = 0; fn < nf; ++fn) {                                                                                \
      switch (P.VU.vsew) {                                                                                             \
      case e8:                                                                                                         \
        MMU.store<uint8_t>(baseAddr + index[i] + fn * 1, P.VU.elt<uint8_t>(vs3 + fn * flmul, vreg_inx),                \
                           xlate_flags_t(), ELEMENT_SKIP);                                                             \
        break;                                                                                                         \
      case e16:                                                                                                        \
        MMU.store<uint16_t>(baseAddr + index[i] + fn * 2, P.VU.elt<uint16_t>(vs3 + fn * flmul, vreg_inx),              \
                            xlate_flags_t(), ELEMENT_SKIP);                                                            \
        break;                                                                                                         \
      case e32:                                                                                                        \
        MMU.store<uint32_t>(baseAddr + index[i] + fn * 4, P.VU.elt<uint32_t>(vs3 + fn * flmul, vreg_inx),              \
                            xlate_flags_t(), ELEMENT_SKIP);                                                            \
        break;                                                                                                         \
      default:                                                                                                         \
        MMU.store<uint64_t>(baseAddr + index[i] + fn * 8, P.VU.elt<uint64_t>(vs3 + fn * flmul, vreg_inx),              \
                            xlate_flags_t(), ELEMENT_SKIP);                                                            \
        break;                                                                                                         \
      }                                                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
  P.VU.vstart->write(0);
#endif

#ifdef VI_LDST_FF
#undef VI_LDST_FF
#define VI_LDST_FF(elt_width)                                                                      \
  const reg_t nf = insn.v_nf() + 1;                                                                \
  VI_CHECK_LOAD(elt_width, false);                                                                 \
  const reg_t vl = p->VU.vl->read();                                                               \
  const reg_t baseAddr = RS1;                                                                      \
  reg_t rd_num = insn.rd();                                                                        \
  const reg_t sew = P.VU.vsew;                                                                     \
  const reg_t eew = sizeof(elt_width##_t)*8;                                                       \
  bool early_stop = false;                                                                         \
  for (reg_t i = p->VU.vstart->read(); i < vl; ++i) {                                              \
    VI_STRIP(i);                                                                                   \
    VI_LOOP_ELEMENT_MASK                                                                           \
    for (reg_t fn = 0; fn < nf; ++fn) {                                                            \
      uint64_t val;                                                                                \
      try {                                                                                        \
        if (skip) { if (P.VU.vma) { val = 0; val = ~val; } else continue; }                        \
        else val = MMU.load<elt_width##_t>(baseAddr + (i * nf + fn) * sizeof(elt_width##_t));      \
      } catch (trap_t & t) {                                                                       \
        if (i == 0)                                                                                \
          throw; /* Only take exception on zeroth element */                                       \
        /* Reduce VL if an exception occurs on a later element */                                  \
        early_stop = true;                                                                         \
        P.VU.vl->write_raw(i);                                                                     \
        break;                                                                                     \
      }                                                                                            \
      p->VU.elt<elt_width##_t>(rd_num + fn * emul, vreg_inx, true) = val;                          \
    }                                                                                              \
    if (early_stop) {                                                                              \
      break;                                                                                       \
    }                                                                                              \
  }                                                                                                \
  for (reg_t fn = 0; fn < nf; ++fn) {                                                              \
    V_HANDLE_TAIL_OPERATION_EEW(VEC_VLS(SE_GET_VLS_VD,elt_width##_t), eew)                         \
    rd_num = (rd_num + emul) % 32;                                                                      \
  }    
#endif

#ifdef VI_ST_WHOLE
#undef VI_ST_WHOLE
#define VI_ST_WHOLE                                                                                                    \
  require_vector_novtype(true);                                                                                        \
  const reg_t baseAddr = RS1;                                                                                          \
  const reg_t vs3 = insn.rd();                                                                                         \
  const reg_t len = insn.v_nf() + 1;                                                                                   \
  require_align(vs3, len);                                                                                             \
  const reg_t size = len * P.VU.vlenb;                                                                                 \
                                                                                                                       \
  if (P.VU.vstart->read() < size) {                                                                                    \
    reg_t i = P.VU.vstart->read() / P.VU.vlenb;                                                                        \
    reg_t off = P.VU.vstart->read() % P.VU.vlenb;                                                                      \
    if (off) {                                                                                                         \
      for (reg_t pos = off; pos < P.VU.vlenb; ++pos) {                                                                 \
        auto val = P.VU.elt<uint8_t>(vs3 + i, pos);                                                                    \
        MMU.store<uint8_t>(baseAddr + P.VU.vstart->read(), val, xlate_flags_t(), ELEMENT_SKIP);                        \
        P.VU.vstart->write(P.VU.vstart->read() + 1);                                                                   \
      }                                                                                                                \
      i++;                                                                                                             \
    }                                                                                                                  \
    for (; i < len; ++i) {                                                                                             \
      for (reg_t pos = 0; pos < P.VU.vlenb; ++pos) {                                                                   \
        auto val = P.VU.elt<uint8_t>(vs3 + i, pos);                                                                    \
        MMU.store<uint8_t>(baseAddr + P.VU.vstart->read(), val, xlate_flags_t(), ELEMENT_SKIP);                        \
        P.VU.vstart->write(P.VU.vstart->read() + 1);                                                                   \
      }                                                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
  P.VU.vstart->write(0);
#endif

#ifdef VI_VFP_VV_LOOP
#undef VI_VFP_VV_LOOP
#define VI_VFP_VV_LOOP(BODY16, BODY32, BODY64) \
  VI_CHECK_SSS(true); \
  VI_VFP_LOOP_GENERAL_BASE \
  VI_LOOP_ELEMENT_MASK \
  switch (P.VU.vsew) { \
    case e16: { \
      float16_t& vd_ma = P.VU.elt<float16_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
        continue; \
      } \
      VFP_VV_PARAMS(16); \
      BODY16; \
      set_fp_exceptions; \
      break; \
    } \
    case e32: { \
      float32_t& vd_ma = P.VU.elt<float32_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_VV_PARAMS(32); \
      BODY32; \
      set_fp_exceptions; \
      break; \
    } \
    case e64: { \
      float64_t& vd_ma = P.VU.elt<float64_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_VV_PARAMS(64); \
      BODY64; \
      set_fp_exceptions; \
      break; \
    } \
    default: \
      require(0); \
      break; \
  }; \
  DEBUG_RVV_FP_VV; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
#endif

#ifdef VI_VFP_VF_LOOP
#undef VI_VFP_VF_LOOP
#define VI_VFP_VF_LOOP(BODY16, BODY32, BODY64) \
  VI_CHECK_SSS(false); \
  VI_VFP_LOOP_GENERAL_BASE \
  VI_LOOP_ELEMENT_MASK \
  switch (P.VU.vsew) { \
    case e16: { \
      float16_t& vd_ma = P.VU.elt<float16_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
        continue; \
      } \
      VFP_VF_PARAMS(16); \
      BODY16; \
      set_fp_exceptions; \
      break; \
    } \
    case e32: { \
      float32_t& vd_ma = P.VU.elt<float32_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_VF_PARAMS(32); \
      BODY32; \
      set_fp_exceptions; \
      break; \
    } \
    case e64: { \
      float64_t& vd_ma = P.VU.elt<float64_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_VF_PARAMS(64); \
      BODY64; \
      set_fp_exceptions; \
      break; \
    } \
    default: \
      require(0); \
      break; \
  }; \
  DEBUG_RVV_FP_VF; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
#endif

#ifdef VI_VFP_V_LOOP
#undef VI_VFP_V_LOOP
#define VI_VFP_V_LOOP(BODY16, BODY32, BODY64) \
  VI_CHECK_SSS(false); \
  VI_VFP_LOOP_GENERAL_BASE \
  VI_LOOP_ELEMENT_MASK \
  switch (P.VU.vsew) { \
    case e16: { \
      float16_t& vd_ma = P.VU.elt<float16_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
        continue; \
      } \
      VFP_V_PARAMS(16); \
      BODY16; \
      break; \
    } \
    case e32: { \
      float32_t& vd_ma = P.VU.elt<float32_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_V_PARAMS(32); \
      BODY32; \
      break; \
    } \
    case e64: { \
      float64_t& vd_ma = P.VU.elt<float64_t>(rd_num, i, true); \
      if (skip) \
      { \
        if (P.VU.vma) { vd_ma.v = 0; vd_ma.v = ~vd_ma.v; } \
        continue; \
      } \
      VFP_V_PARAMS(64); \
      BODY64; \
      break; \
    } \
    default: \
      require(0); \
      break; \
  }; \
  set_fp_exceptions; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)
#endif

#define VI_VFP_LOOP_SCALE_BASE_GENERAL \
  require_fp; \
  require_vector(true); \
  require(STATE.frm->read() < 0x5); \
  reg_t vl = P.VU.vl->read(); \
  reg_t rd_num = insn.rd(); \
  reg_t UNUSED rs1_num = insn.rs1(); \
  reg_t rs2_num = insn.rs2(); \
  reg_t sew = P.VU.vsew; \
  softfloat_roundingMode = STATE.frm->read(); \
  for (reg_t i = P.VU.vstart->read(); i < vl; ++i) { \
    VI_LOOP_ELEMENT_MASK

#define VI_VFP_CVT_LOOP_GENERAL_FP16(CVT_PARAMS, CHECK, BODY) \
  CHECK \
  VI_VFP_LOOP_SCALE_BASE_GENERAL \
  float16_t& vd_ma = P.VU.elt<float16_t>(rd_num, i, true); \
  if (skip) \
  { \
    if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
    continue; \
  } \
  CVT_PARAMS \
  BODY \
  set_fp_exceptions; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)

#define VI_VFP_CVT_LOOP_GENERAL_FP32(CVT_PARAMS, CHECK, BODY) \
  CHECK \
  VI_VFP_LOOP_SCALE_BASE_GENERAL \
  float32_t& vd_ma = P.VU.elt<float32_t>(rd_num, i, true); \
  if (skip) \
  { \
    if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
    continue; \
  } \
  CVT_PARAMS \
  BODY \
  set_fp_exceptions; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)

#define VI_VFP_CVT_LOOP_GENERAL_FP64(CVT_PARAMS, CHECK, BODY) \
  CHECK \
  VI_VFP_LOOP_SCALE_BASE_GENERAL \
  float64_t& vd_ma = P.VU.elt<float64_t>(rd_num, i, true); \
  if (skip) \
  { \
    if (P.VU.vma) { vd_ma.v = 0; vd_ma.v= ~vd_ma.v; } \
    continue; \
  } \
  CVT_PARAMS \
  BODY \
  set_fp_exceptions; \
  VI_VFP_LOOP_END \
  V_HANDLE_TAIL(VEC_COMMON, EXT_GET_VD)

#ifdef VI_VFP_CVT_INT_TO_FP
#undef VI_VFP_CVT_INT_TO_FP
#define VI_VFP_CVT_INT_TO_FP(BODY16, BODY32, BODY64, sign) \
  VI_CHECK_SSS(false); \
  VI_VFP_COMMON \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_GENERAL_FP16(CVT_INT_TO_FP_PARAMS(16, 16, sign), \
        { require(p->extension_enabled(EXT_ZVFH)); },   \
        BODY16); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_GENERAL_FP32(CVT_INT_TO_FP_PARAMS(32, 32, sign), \
        { require(p->get_isa().get_zvf()); },  \
        BODY32); } \
      break; \
    case e64: \
      { VI_VFP_CVT_LOOP_GENERAL_FP64(CVT_INT_TO_FP_PARAMS(64, 64, sign), \
        { require(p->get_isa().get_zvd()); },  \
        BODY64); } \
      break; \
    default: \
      require(0); \
      break; \
  }
#endif

#ifdef VI_VFP_CVT_FP_TO_INT
#undef VI_VFP_CVT_FP_TO_INT
#define VI_VFP_CVT_FP_TO_INT(BODY16, BODY32, BODY64, sign) \
  VI_CHECK_SSS(false); \
  VI_VFP_COMMON \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_GENERAL_FP16(CVT_FP_TO_INT_PARAMS(16, 16, sign), \
        { require(p->extension_enabled(EXT_ZVFH)); },   \
        BODY16); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_GENERAL_FP32(CVT_FP_TO_INT_PARAMS(32, 32, sign), \
        { require(p->get_isa().get_zvf()); },  \
        BODY32); } \
      break; \
    case e64: \
      { VI_VFP_CVT_LOOP_GENERAL_FP64(CVT_FP_TO_INT_PARAMS(64, 64, sign), \
        { require(p->get_isa().get_zvd()); },  \
        BODY64); } \
      break; \
    default: \
      require(0); \
      break; \
  }
#endif


#ifdef  VI_VFP_NCVT_BF16_TO_FP
#undef  VI_VFP_NCVT_BF16_TO_FP
#define VI_VFP_NCVT_BF16_TO_FP(BODY, CHECK) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_NARROW_FP(CVT_FP_TO_FP_PARAMS(32, 16), CHECK, BODY); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif

#ifdef  VI_VFP_NCVT_FP_TO_INT
#undef  VI_VFP_NCVT_FP_TO_INT
#define VI_VFP_NCVT_FP_TO_INT(BODY16, BODY32, BODY64, \
                              CHECK16, CHECK32, CHECK64, \
                              sign) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  switch (P.VU.vsew) { \
    case e8: \
      { VI_VFP_CVT_LOOP_NARROW(CVT_FP_TO_INT_PARAMS(16, 8, sign), CHECK16, BODY16); } \
      break; \
    case e16: \
      { VI_VFP_CVT_LOOP_NARROW(CVT_FP_TO_INT_PARAMS(32, 16, sign), CHECK32, BODY32); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_NARROW(CVT_FP_TO_INT_PARAMS(64, 32, sign), CHECK64, BODY64); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif

#ifdef  VI_VFP_NCVT_FP_TO_FP
#undef  VI_VFP_NCVT_FP_TO_FP
#define VI_VFP_NCVT_FP_TO_FP(BODY32, BODY64, \
                             CHECK32, CHECK64) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_NARROW_FP(CVT_FP_TO_FP_PARAMS(32, 16), CHECK32, BODY32); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_NARROW_FP(CVT_FP_TO_FP_PARAMS(64, 32), CHECK64, BODY64); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif

#ifdef  VI_VFP_NCVT_INT_TO_FP
#undef  VI_VFP_NCVT_INT_TO_FP
#define VI_VFP_NCVT_INT_TO_FP(BODY32, BODY64, \
                              CHECK32, CHECK64, \
                              sign) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_SDS(false); \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_NARROW_FP(CVT_INT_TO_FP_PARAMS(32, 16, sign), CHECK32, BODY32); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_NARROW_FP(CVT_INT_TO_FP_PARAMS(64, 32, sign), CHECK64, BODY64); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif

#ifdef  VI_VFP_WCVT_FP_TO_FP
#undef  VI_VFP_WCVT_FP_TO_FP
#define VI_VFP_WCVT_FP_TO_FP(BODY16, BODY32, \
                             CHECK16, CHECK32) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_DSS(false); \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_FP_TO_FP_PARAMS(16, 32), CHECK16, BODY16); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_FP_TO_FP_PARAMS(32, 64), CHECK32, BODY32); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif

#ifdef  VI_VFP_WCVT_FP_TO_BF16
#undef  VI_VFP_WCVT_FP_TO_BF16
#define VI_VFP_WCVT_FP_TO_BF16(BODY, CHECK) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_DSS(false); \
  switch (P.VU.vsew) { \
    case e16: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_FP_TO_FP_PARAMS(16, 32), CHECK, BODY); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif


#ifdef  VI_VFP_WCVT_INT_TO_FP
#undef  VI_VFP_WCVT_INT_TO_FP
#define VI_VFP_WCVT_INT_TO_FP(BODY8, BODY16, BODY32, \
                              CHECK8, CHECK16, CHECK32, \
                              sign) \
  SAVE_VMA_VTA \
  SET_VMA_VTA_FOR_VS_VD_OVERLAP \
  VI_CHECK_DSS(false); \
  reg_t UNUSED rd_num = insn.rd(); \
  reg_t rs2_num = insn.rs2(); \
  reg_t sew = P.VU.vsew; \
  switch (P.VU.vsew) { \
    case e8: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_INT_TO_FP_PARAMS(8, 16, sign), CHECK8, BODY8); } \
      break; \
    case e16: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_INT_TO_FP_PARAMS(16, 32, sign), CHECK16, BODY16); } \
      break; \
    case e32: \
      { VI_VFP_CVT_LOOP_WIDEN_FP(CVT_INT_TO_FP_PARAMS(32, 64, sign), CHECK32, BODY32); } \
      break; \
    default: \
      require(0); \
      break; \
  } \
  RESTORE_VMA_VTA
#endif


#ifdef  VI_VFP_VF_LOOP_CMP
#undef  VI_VFP_VF_LOOP_CMP
#define VI_VFP_VF_LOOP_CMP(BODY16, BODY32, BODY64) \
  VI_CHECK_MSS(false); \
  VI_VFP_LOOP_CMP_GENERAL_BASE \
  switch (P.VU.vsew) { \
    case e16: { \
      if (skip) \
      { if (P.VU.vma) { res = 1; } else continue; } \
      else { \
        VFP_VF_CMP_PARAMS(16); \
        BODY16; \
        set_fp_exceptions; \
      } \
      break; \
    } \
    case e32: { \
      if (skip) \
      { if (P.VU.vma) { res = 1; } else continue; } \
      else { \
        VFP_VF_CMP_PARAMS(32); \
        BODY32; \
        set_fp_exceptions; \
      } \
      break; \
    } \
    case e64: { \
      if (skip) \
      { if (P.VU.vma) { res = 1; } else continue; } \
      else { \
        VFP_VF_CMP_PARAMS(64); \
        BODY64; \
        set_fp_exceptions; \
      } \
      break; \
    } \
    default: \
      require(0); \
      break; \
  }; \
  VI_VFP_LOOP_CMP_END
#endif



#endif // _RISCV_V_EXT_MACROS_EXTENSION_H
