
// overload operators of soft floats

#include "softfloat_ops.h"
#include "softfloat.h"

#define USE_SOFTFLOAT_OPERATORS

#ifdef USE_SOFTFLOAT_OPERATORS
void float16_ref::operator= ( uint32_t src) { *this = ui32_to_f16(src); }
void float16_ref::operator= ( uint64_t src) { *this = ui64_to_f16(src); }
void float16_ref::operator= (  int32_t src) { *this =  i32_to_f16(src); }
void float16_ref::operator= (  int64_t src) { *this =  i64_to_f16(src); }
void float16_ref::operator= (float16_t src) { *dynamic_cast<float16_t*>(this) = src; };
void float16_ref::operator= (float32_t src) { *dynamic_cast<float16_t*>(this) = f32_to_f16(src); };
void float16_ref::operator= (float64_t src) { *dynamic_cast<float16_t*>(this) = f64_to_f16(src); };
float16_t float16_ref::operator+ (float16_ref src) const { return f16_add(*this, src); }
float16_t float16_ref::operator- (float16_ref src) const { return f16_sub(*this, src); }
float16_t float16_ref::operator* (float16_ref src) const { return f16_mul(*this, src); }
float16_t float16_ref::operator/ (float16_ref src) const { return f16_div(*this, src); }
float16_t float16_ref::operator% (float16_ref src) const { return f16_rem(*this, src); }
bool float16_ref::operator== (float16_ref src) const { return f16_eq(*this, src); }
bool float16_ref::operator<= (float16_ref src) const { return f16_le(*this, src); }
bool float16_ref::operator<  (float16_ref src) const { return f16_lt(*this, src); }
#ifdef SOFTFLOAT_FAST_INT64
void float16_ref::operator= (float128_ref src) { *this = f128_to_f16(src); }
#endif // SOFTFLOAT_FAST_INT64
#endif // USE_SOFTFLOAT_OPERATORS

#ifdef USE_SOFTFLOAT_OPERATORS
bfloat16_t bfloat16_ref::operator+ (bfloat16_t src) { return bf16_add(*this, src); }
bfloat16_t bfloat16_ref::operator- (bfloat16_t src) { return bf16_sub(*this, src); }
bfloat16_t bfloat16_ref::operator* (bfloat16_t src) { return bf16_mul(*this, src); }
bfloat16_t bfloat16_ref::operator/ (bfloat16_t src) { return bf16_div(*this, src); }
void bfloat16_ref::operator= (bfloat16_t src) { *dynamic_cast<bfloat16_t*>(this) = src; }
void bfloat16_ref::operator= ( float32_t src) { *dynamic_cast<bfloat16_t*>(this) = f32_to_bf16(src); }
void bfloat16_ref::operator= ( float64_t src) { *dynamic_cast<bfloat16_t*>(this) = f64_to_bf16(src); }
#endif // USE_SOFTFLOAT_OPERATORS

#ifdef USE_SOFTFLOAT_OPERATORS
void float32_ref::operator= (  uint32_t src)  { *this = ui32_to_f32(src); }
void float32_ref::operator= (  uint64_t src)  { *this = ui64_to_f32(src); }
void float32_ref::operator= (   int32_t src)  { *this =  i32_to_f32(src); }
void float32_ref::operator= (   int64_t src)  { *this =  i64_to_f32(src); }
void float32_ref::operator= ( float32_t   src)  { *dynamic_cast<float32_t*>(this) = src ; }
void float32_ref::operator= ( float16_ref src)  { *dynamic_cast<float32_t*>(this) =  f16_to_f32(src); }
void float32_ref::operator= (bfloat16_ref src)  { *dynamic_cast<float32_t*>(this) = bf16_to_f32(src); }
float32_t float32_ref::operator+ (float32_ref src) const { return f32_add(*this, src); }
float32_t float32_ref::operator- (float32_ref src) const { return f32_sub(*this, src); }
float32_t float32_ref::operator* (float32_ref src) const { return f32_mul(*this, src); }
float32_t float32_ref::operator/ (float32_ref src) const { return f32_div(*this, src); }
float32_t float32_ref::operator% (float32_ref src) const { return f32_rem(*this, src); }
bool float32_ref::operator== (float32_ref src) const { return f32_eq(*this, src); }
bool float32_ref::operator<= (float32_ref src) const { return f32_le(*this, src); }
bool float32_ref::operator<  (float32_ref src) const { return f32_lt(*this, src); }
#ifdef SOFTFLOAT_FAST_INT64
void float32_ref::operator= (float128_ref src) { *this = f128_to_f32(src); }
#endif // SOFTFLOAT_FAST_INT64
#endif // USE_SOFTFLOAT_OPERATORS
  

#ifdef USE_SOFTFLOAT_OPERATORS
void float64_ref::operator= (  uint32_t   src) { *dynamic_cast<float64_t*>(this) = ui32_to_f64(src); }
void float64_ref::operator= (  uint64_t   src) { *dynamic_cast<float64_t*>(this) = ui64_to_f64(src); }
void float64_ref::operator= (   int32_t   src) { *dynamic_cast<float64_t*>(this) =  i32_to_f64(src); }
void float64_ref::operator= (   int64_t   src) { *dynamic_cast<float64_t*>(this) =  i64_to_f64(src); }
void float64_ref::operator= ( float16_t   src) { *dynamic_cast<float64_t*>(this) =  f16_to_f64(src); }
void float64_ref::operator= ( float32_t   src) { *dynamic_cast<float64_t*>(this) =  f32_to_f64(src); }
void float64_ref::operator= ( float64_t   src) { *dynamic_cast<float64_t*>(this) = src; }
void float64_ref::operator= (bfloat16_ref src) { *dynamic_cast<float64_t*>(this) = bf16_to_f64(src); }
float64_t float64_ref::operator+ (float64_ref src) const { return f64_add(*this, src); }
float64_t float64_ref::operator- (float64_ref src) const { return f64_sub(*this, src); }
float64_t float64_ref::operator* (float64_ref src) const { return f64_mul(*this, src); }
float64_t float64_ref::operator/ (float64_ref src) const { return f64_div(*this, src); }
float64_t float64_ref::operator% (float64_ref src) const { return f64_rem(*this, src); }
bool float64_ref::operator== (float64_ref src) const { return f64_eq(*this, src); }
bool float64_ref::operator<= (float64_ref src) const { return f64_le(*this, src); }
bool float64_ref::operator<  (float64_ref src) const { return f64_lt(*this, src); }
#ifdef SOFTFLOAT_FAST_INT64
void float64_ref::operator= (float128_ref src) { *this = f128_to_f64(src); }
#endif // SOFTFLOAT_FAST_INT64
#endif // USE_SOFTFLOAT_OPERATORS


#ifdef SOFTFLOAT_FAST_INT64
#ifdef USE_SOFTFLOAT_OPERATORS
void float128_ref::operator= (  uint32_t src) { *dynamic_cast<float128_t*>(this) = ui32_to_f128(src); }
void float128_ref::operator= ( float16_t src) { *dynamic_cast<float128_t*>(this) =  f16_to_f128(src); }
void float128_ref::operator= ( float32_t src) { *dynamic_cast<float128_t*>(this) =  f32_to_f128(src); }
void float128_ref::operator= ( float64_t src) { *dynamic_cast<float128_t*>(this) =  f64_to_f128(src); }
void float128_ref::operator= (float128_t src) { *dynamic_cast<float128_t*>(this) =  src; }
float128_t float128_ref::operator+ (float128_ref src) const { return f128_add(*this, src); }
float128_t float128_ref::operator- (float128_ref src) const { return f128_sub(*this, src); }
float128_t float128_ref::operator* (float128_ref src) const { return f128_mul(*this, src); }
float128_t float128_ref::operator/ (float128_ref src) const { return f128_div(*this, src); }
float128_t float128_ref::operator% (float128_ref src) const { return f128_rem(*this, src); }
bool float128_ref::operator== (float128_ref src) const { return f128_eq(*this, src); }
bool float128_ref::operator<= (float128_ref src) const { return f128_le(*this, src); }
bool float128_ref::operator<  (float128_ref src) const { return f128_lt(*this, src); }
#endif // USE_SOFTFLOAT_OPERATORS
#endif // SOFTFLOAT_FAST_INT64