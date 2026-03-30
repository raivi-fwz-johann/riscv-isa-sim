#ifndef _TYPE_FUNCTIONS_H_
#define _TYPE_FUNCTIONS_H_

#include <functional>
#include <cfenv>

#include "softfloat_types.h"
#include "softfloat.h"

/* ==============================================
 * a bunch of template meta classes, dealing
 *   with rvv functions, to easily combined to 
 *   various implementations
 */

namespace type_functions 
{

template <typename T>
struct type_info
{
  static const size_t bytes = sizeof(T);
  static const size_t bits  = sizeof(T)*8;
};

enum sign_type
{
  UNSIGNED, SIGNED
};

/*
 * meta functions, width -> type
 */
template <size_t bits, sign_type is_signed>
struct int_type
{};
template <>
struct int_type<8, SIGNED>
{
  using single = int8_t; 
  using widen  = int16_t;
  // using narrow = // forbidden
};
template <>
struct int_type<16, SIGNED>
{
  using single = int16_t; 
  using widen  = int32_t;
  using narrow = int8_t;
};
template <>
struct int_type<32, SIGNED>
{
  using single = int32_t;
  using widen  = int64_t;
  using narrow = int16_t;
};
template <>
struct int_type<64, SIGNED>
{
  using single = int64_t; 
  // using widen  = int128_t; // forbidden
  using narrow = int32_t;
};
template <>
struct int_type<8, UNSIGNED>
{
  using single = uint8_t; 
  using widen  = uint16_t;
  // using narrow = // forbidden
};
template <>
struct int_type<16, UNSIGNED>
{
  using single = uint16_t; 
  using widen  = uint32_t;
  using narrow = uint8_t;
};
template <>
struct int_type<32, UNSIGNED>
{
  using single = uint32_t;
  using widen  = uint64_t;
  using narrow = uint16_t;
};
template <>
struct int_type<64, UNSIGNED>
{
  using single = uint64_t; 
  // using widen = ; // forbidden
  using narrow = uint32_t;
};

/*
 * meta functions for soft floats
 */
template <size_t WIDTH>
struct soft_float_type
{};
template <>
struct soft_float_type<e16>
{
  using single = float16_t; 
  using widen  = float32_t;
  // narrow forbidden
};
template <>
struct soft_float_type<e32>
{
  using single  = float32_t; 
  using narrow  = float16_t; 
  using widen   = float64_t;
};
template <>
struct soft_float_type<e64>
{
  using single = float64_t;
  using narrow = float32_t;
  // widen forbidden
};



static reg_t int_half(reg_t n)
{
  return 1<<(63-__builtin_clz(n-1));
}


template <typename T>
struct use_origin_value
{
  T operator() (T origin) { return origin; }
};

struct mask_all_true
{
  bool operator() (size_t i) { return true; }
};

struct rvv_mask
{
  uint64_t* mask_p;
  uint64_t  offset;
  bool operator() (size_t i) const
  { 
    size_t index = offset + i;
    const int midx = index / 64;
    const int mpos = index % 64;
    size_t result = ((mask_p[midx] >> mpos) & 0x1);
    return result == 1;
  }
};

struct float_widen_op
{
  float32_t operator() (float16_t src) { return f16_to_f32(src); }
  float64_t operator() (float32_t src) { return f32_to_f64(src); }
};

struct debug_double_add
{
  int fload_rounding_mode;
  float64_ref operator() (float64_ref a, float64_ref b)
  {
    fesetround(fload_rounding_mode);
    float64_ref res = a+b;
    double ref = (*(double*)&a) + (*(double*)&b);
    printf("==========\n");
    printf("src2, encoding: %lx, value: %f\n", b.v, (*(double*)&b) );
    printf("src1, encoding: %lx, value: %f\n", a.v, (*(double*)&a) );
    printf("soft float sum: encoding: %lx, value: %f\n", res.v, (*(double*)&res) );
    printf("x86  float sum: encoding: %lx, value: %f\n\n", (*(uint64_t*)&ref) , ref );
    // res.v = (*(uint64_t*)&ref);
    return res;
  }
};

struct debug_float_add
{
  int fload_rounding_mode;
  float32_ref operator() (float32_ref a, float32_ref b)
  {
    fesetround(fload_rounding_mode);
    float ref = (*(float*)&a) + (*(float*)&b);
    float32_ref res = b+a;
    printf("==========\n");
    printf("src2, encoding: %x, value: %f\n", b.v, (*(float*)&b) );
    printf("src1, encoding: %x, value: %f\n", a.v, (*(float*)&a) );
    printf("soft float sum: encoding: %x, value: %f\n", res.v, (*(float*)&res) );
    ref = (*(float*)&b) + (*(float*)&a);
    printf("x86  float sum: encoding: %x, value: %f\n\n", (*(uint32_t*)&ref) , ref );
    // res.v = (*(uint64_t*)&ref);
    return res;
  }
};

/*
 * decorator for binary float operators such as plus,
 * to reserve floating point exception flags for a bunch
 * of binary operations with any order, the reason to
 * use this decorator is: floating point flags should be
 * checked and set to FCSR, however FCSR belongs to every
 * processor core, in this file I try to decouple operations
 * from specific core implemetation, to regain interface
 * independence and make to code easier to maintain.
 *
 * This class does one thing: check and save all exception flags
 * from global variable "softfloat_exceptionFlags" after each 
 * time the wrapped operator is called, then set back to it 
 * before destruction. It can be wrappered to any binary 
 * operator like std::plus<float32_ref>, which should have an
 * operator like:
 *
 * data_type operator() (data_type a, data_type b);
 *
 * possible future update: to pass a lambda function or similar to 
 * abstract flag checking/setting operation, get ride of read
 * global variable softfloat_exceptionFlags directly
 */
template <typename bin_op_type, typename data_type>
struct fp_bin_op_wrapper
{
  bin_op_type _op=bin_op_type();
  uint_fast8_t fp_exception_flag=0;

  data_type operator() (data_type a, data_type b)
  { 
    data_type res = _op(a,b);
    // printf("store float exception flag: %x\n", softfloat_exceptionFlags);
    fp_exception_flag |= softfloat_exceptionFlags;
    softfloat_exceptionFlags = 0; 
    return res; }

  fp_bin_op_wrapper() { fp_exception_flag = softfloat_exceptionFlags; }
  ~fp_bin_op_wrapper() 
  { 
    // printf("restore fp_exception_flag: %x\n", fp_exception_flag);
    softfloat_exceptionFlags |= fp_exception_flag;
  }
};

/*
 * tree reduce:
 * make a balanced binary tree, apply binary operations
 * along the tree with a recursive manner
 * types:
 *    mask_type     : 
 *    unary_op_type :
 *    T_in          :
 *    T_out         :
 * args:
 *   
 */
template <typename T_in, typename T_out, typename bin_op_type>
struct tree_reduce_binary_op
{
  // with mask and single op
  // apply "unary_op" to single element first, like "widen" or "narrow"
  template <typename mask_type=mask_all_true, typename unary_op_type=use_origin_value<T_in> >
  T_out operator() (T_in* base, size_t nstart, size_t nlen, bin_op_type bin_op,
    bool          use_mask      = false,
    mask_type     mask_op       = mask_type(), 
    unary_op_type elem_op       = unary_op_type(),
    T_out         default_value = T_out())
  {
    if (nlen==1) 
    {
      bool skip = !mask_op(nstart);
      if (use_mask && skip) return default_value; // masked off
      // apply "elem_op"
      else return elem_op(base[nstart]);
    }
    // bin-tree iterative call bin_op
    size_t half_len = int_half(nlen);
    // printf("add index: %lu->%lu, %lu->%lu\n", nstart, nstart+half_len, nstart+half_len, nstart+nlen);
    T_out res = bin_op(
      this->operator()(base, nstart         , half_len     , bin_op, use_mask, mask_op, elem_op, default_value),
      this->operator()(base, nstart+half_len, nlen-half_len, bin_op, use_mask, mask_op, elem_op, default_value)
    );
    return res;
  }
};


/*
 * odd tree reduce
 */
template <typename T_in, typename T_out, typename bin_op_type>
struct odd_tree_reduce_binary_op
{
  template <typename mask_type=mask_all_true, typename unary_op_type=use_origin_value<T_in> >
  T_out operator() (T_in* base, size_t nstart, size_t nlen, bin_op_type bin_op,
    bool          use_mask      = false,
    mask_type     mask_op       = mask_type(), 
    unary_op_type elem_op       = unary_op_type(),
    T_out         default_value = T_out(),
    size_t        nstride       = 1)
  {
    if (nlen==1) 
    {
      if (use_mask && !mask_op(nstart) ) return default_value; // masked off
      // apply "elem_op"
      return elem_op(base[nstart]);
    }
    // bin-tree iterative call bin_op
    size_t half_len = nlen/2;
    return bin_op(
      this->operator()(base, nstart        , nlen-half_len, bin_op, use_mask, mask_op, elem_op, default_value, nstride*2),
      this->operator()(base, nstart+nstride, half_len     , bin_op, use_mask, mask_op, elem_op, default_value, nstride*2)
    );
  }
};

// tree_binary_op<float32_t, std::plus>(std::plus<float32_t>()) op;

// insn.v_vm() == 0
/*
 * meta functions, soft float add
 */
template <size_t ELEM_TYPE>
struct soft_float_ops
{};

#define DEF_FLOAT_OPS(WIDTH) \
template <> struct soft_float_ops<e##WIDTH> \
{ \
  using raw_type=soft_float_type<WIDTH>::single; \
  static raw_type add(raw_type f1, raw_type f2) \
  { return f##WIDTH##_add(f1, f2); }; \
  static raw_type tree_sum(processor_t& P, reg_t vreg_num, \
    reg_t startn, reg_t n, bool use_mask=false) \
  { \
    if (n==0) printf("\e[31m[error\e[0m] vreg_num=%lu, startn=%lu, n=%lu\n", \
      vreg_num, startn, n); \
    processor_t* p=&P; \
    if (n==1) \
    { \
      if (use_mask) { \
        int midx = (startn+n) / 64; \
        int mpos = (startn+n) % 64; \
        uint64_t& elt_data = P.VU.elt<uint64_t>(0ULL,midx); \
        bool skip = ((elt_data >> mpos) & 0x1) == 0; \
        if (skip) { raw_type result; result.v=0; return result; } \
      } \
      raw_type result; \
      result = P.VU.elt<raw_type>(vreg_num,startn); \
      return result; \
    } \
    reg_t half_n = int_half(n); \
    raw_type result= add( \
      tree_sum(P, vreg_num, startn,        half_n), \
      tree_sum(P, vreg_num, startn+half_n, n-half_n) ); \
      set_fp_exceptions; \
    return result; \
  } \
};

DEF_FLOAT_OPS(16)
DEF_FLOAT_OPS(32)
DEF_FLOAT_OPS(64)



template <size_t ELEM_WIDTH>
struct soft_float_widen_ops
{};

#define DEF_FLOAT_WIDEN_OPS(WIDTH, WIDEN_WIDTH) \
template <> struct soft_float_widen_ops<e##WIDTH> \
{ \
  using raw_type    =soft_float_type<WIDTH>::single; \
  using widen_type=soft_float_type<WIDTH>::widen; \
  static raw_type add(raw_type f1, raw_type f2) \
  { return f##WIDTH##_add(f1, f2); }; \
  static widen_type wadd(widen_type f1, widen_type f2) \
  { return f##WIDEN_WIDTH##_add(f1, f2); }; \
  static widen_type tree_wsum(processor_t& P, reg_t vreg_num, \
    reg_t startn, reg_t n, bool use_mask=false) \
  { \
    if (n==0) printf("\e[31m[error\e[0m] vreg_num=%lu, startn=%lu, n=%lu\n", \
      vreg_num, startn, n); \
    processor_t* p=&P; \
    if (n==1) \
    { \
      if (use_mask) { \
        int midx = (startn+n) / 64; \
        int mpos = (startn+n) % 64; \
        uint64_t& elt_data = P.VU.elt<uint64_t>(0ULL,midx); \
        bool skip = ((elt_data >> mpos) & 0x1) == 0; \
        if (skip) { widen_type result; result.v=0; return result; } \
      } \
      raw_type vs = P.VU.elt<raw_type>(vreg_num, startn); \
      widen_type result = f##WIDTH##_to_f##WIDEN_WIDTH(vs); \
      return result; \
    } \
    reg_t half_n = int_half(n); \
    widen_type result = wadd( \
      tree_wsum(P, vreg_num, startn,        half_n), \
      tree_wsum(P, vreg_num, startn+half_n, n-half_n) ); \
      set_fp_exceptions; \
    return result; \
  } \
};

DEF_FLOAT_WIDEN_OPS(16,32)
DEF_FLOAT_WIDEN_OPS(32,64)

} // namespace type_functions 

#endif // _TYPE_FUNCTIONS_H_