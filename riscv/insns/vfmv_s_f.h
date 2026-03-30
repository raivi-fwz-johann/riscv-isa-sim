// vfmv_s_f: vd[0] = rs1 (vs2=0)
require_vector(true);
require_fp;
require((P.VU.vsew == e16 && p->extension_enabled(EXT_ZVFH)) ||
        (P.VU.vsew == e32 && p->extension_enabled('F')) ||
        (P.VU.vsew == e64 && p->extension_enabled('D')));
require(STATE.frm->read() < 0x5);

reg_t vl = P.VU.vl->read();

if (vl > 0 && P.VU.vstart->read() < vl) {
  reg_t rd_num = insn.rd();
  reg_t rs2_num = insn.rs2(); /* code ext */

  switch (P.VU.vsew) {
    case e16:
      P.VU.elt<uint16_t>(rd_num, 0, true) = f16(FRS1).v;
      V_HANDLE_TAIL_OPERATION_EEW_SINGLE_TA_NOVL(VEC_VLS(SE_GET_VLS_VD,uint16_t), 16)/* code ext */
      break;
    case e32:
      P.VU.elt<uint32_t>(rd_num, 0, true) = f32(FRS1).v;
      V_HANDLE_TAIL_OPERATION_EEW_SINGLE_TA_NOVL(VEC_VLS(SE_GET_VLS_VD,uint32_t), 32)/* code ext */
      break;
    case e64:
      if (FLEN == 64)
        P.VU.elt<uint64_t>(rd_num, 0, true) = f64(FRS1).v;
      else
        P.VU.elt<uint64_t>(rd_num, 0, true) = f32(FRS1).v;
      V_HANDLE_TAIL_OPERATION_EEW_SINGLE_TA_NOVL(VEC_VLS(SE_GET_VLS_VD,uint64_t), 64)/* code ext */
      break;
  }
}
P.VU.vstart->write(0);
