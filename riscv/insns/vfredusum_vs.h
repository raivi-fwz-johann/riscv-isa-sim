// vfredsum: vd[0] =  sum( vs2[*] , vs1[0] )
if (!usum_as_osum())
{

bool is_propagate = true;
reg_t vreg_n_elems = P.VU.VLEN/P.VU.vsew;

// #define DEBUG_FLOAT_ADD
  tree_reduce_binary_op<float16_ref, float16_ref, fp_bin_op_wrapper<std::plus<float16_ref>, float16_ref>> op16;
  #ifndef DEBUG_FLOAT_ADD
  tree_reduce_binary_op<float32_ref, float32_ref, fp_bin_op_wrapper<std::plus<float32_ref>, float32_ref>> op32;
  tree_reduce_binary_op<float64_ref, float64_ref, fp_bin_op_wrapper<std::plus<float64_ref>, float64_ref>> op64;
  #else
  printf("===================== vfredusum.vs pc: %lx =====================\n", pc);
  tree_reduce_binary_op<float32_ref, float32_ref, fp_bin_op_wrapper<debug_float_add, float32_ref>> op32;
  tree_reduce_binary_op<float64_ref, float64_ref, fp_bin_op_wrapper<debug_double_add,float64_ref>> op64;
  #endif

  bool use_mask = (insn.v_vm()==0);
  rvv_mask mask_op{ &P.VU.elt<uint64_t>(0,0),0 };

  VI_VFP_VV_TREE_REDUCTION
  ( 
  {
    for (reg_t pos=0; pos<vl; pos+=vreg_n_elems) {
      reg_t op_len = ((pos+vreg_n_elems)>vl)?(vl-pos):vreg_n_elems;
      mask_op.offset = pos;
      float16_ref tree_res = op16(
        reinterpret_cast<float16_ref*>(&(P.VU.elt<float16_t>(rs2_num, pos))), 0, op_len, 
        fp_bin_op_wrapper<std::plus<float16_ref>, float16_ref>(),
        use_mask, mask_op
      );
      set_fp_exceptions;
      vd_0 = float16_ref(vd_0) + tree_res;
      set_fp_exceptions;
    }
  },
  #ifndef DEBUG_FLOAT_ADD
  {
    for (reg_t pos=0; pos<vl; pos+=vreg_n_elems) {
      reg_t op_len = ((pos+vreg_n_elems)>vl)?(vl-pos):vreg_n_elems;
      mask_op.offset = pos;
      float32_ref tree_res = op32(
        reinterpret_cast<float32_ref*>(&(P.VU.elt<float32_t>(rs2_num, pos))), 0, op_len, 
        fp_bin_op_wrapper<std::plus<float32_ref>, float32_ref>(),
        use_mask, mask_op
        );
        set_fp_exceptions;
        vd_0 = float32_ref(vd_0) + tree_res;
        set_fp_exceptions;
    }
  },
  {
    for (reg_t pos=0; pos<vl; pos+=vreg_n_elems) {
      reg_t op_len = ((pos+vreg_n_elems)>vl)?(vl-pos):vreg_n_elems;
      mask_op.offset = pos;
      float64_ref tree_res = op64(
        reinterpret_cast<float64_ref*>(&(P.VU.elt<float64_t>(rs2_num, pos))), 0, op_len, 
        fp_bin_op_wrapper<std::plus<float64_ref>, float64_ref>(),
        use_mask, mask_op
      );
      set_fp_exceptions;
      vd_0 = float64_ref(vd_0) + tree_res;
      set_fp_exceptions;
    }
  }
  #else
  {
    for (reg_t pos=0; pos<vl; pos+=vreg_n_elems) {
      reg_t op_len = ((pos+vreg_n_elems)>vl)?(vl-pos):vreg_n_elems;
      mask_op.offset = pos;    
      float32_t tree_res = op32(
        reinterpret_cast<float32_ref*>(&(P.VU.elt<float32_t>(rs2_num, pos))), 0, op_len,
        fp_bin_op_wrapper<debug_float_add, float32_ref>(),
        use_mask, mask_op
      );
      set_fp_exceptions;
      vd_0 = debug_float_add()(float32_ref(vd_0) , tree_res);
      set_fp_exceptions;
    }
  },
  {
    for (reg_t pos=0; pos<vl; pos+=vreg_n_elems) {
      reg_t op_len = ((pos+vreg_n_elems)>vl)?(vl-pos):vreg_n_elems;
      mask_op.offset = pos;    
      float64_t tree_res = op64(
        reinterpret_cast<float64_ref*>(&(P.VU.elt<float64_t>(rs2_num, pos))), 0, op_len,
        fp_bin_op_wrapper<debug_double_add, float64_ref>(),
        use_mask, mask_op
      );
      set_fp_exceptions;
      vd_0 = debug_double_add()(float64_ref(vd_0) , tree_res);
      set_fp_exceptions;
    }
  }
  #endif
  )
}
else
{
bool is_propagate = false;
VI_VFP_VV_LOOP_REDUCTION
({
  vd_0 = f16_add(vd_0, vs2);
},
{
  vd_0 = f32_add(vd_0, vs2);
},
{
  vd_0 = f64_add(vd_0, vs2);
})
}