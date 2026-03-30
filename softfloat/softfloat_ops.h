
#ifndef softfloat_ops_h
#define softfloat_ops_h 1

#include "softfloat_types.h"

// overload operators of soft floats
#define USE_SOFTFLOAT_OPERATORS

struct float16_ref;
struct bfloat16_ref;
struct float32_ref;
struct float64_ref;
struct float128_ref;

struct float16_ref : float16_t
{ 
  float16_ref() = default;
  float16_ref(const float16_ref&) = default;
  float16_ref(float16_t f16) { float16_t::v=f16.v; }
  void operator= ( uint32_t src);
  void operator= ( uint64_t src);
  void operator= (  int32_t src);
  void operator= (  int64_t src);
  void operator= (float16_t src);
  void operator= (float32_t src);
  void operator= (float64_t src);
  float16_t operator+ (float16_ref src) const;
  float16_t operator- (float16_ref src) const;
  float16_t operator* (float16_ref src) const;
  float16_t operator/ (float16_ref src) const;
  float16_t operator% (float16_ref src) const;
  bool operator== (float16_ref src) const;
  bool operator<= (float16_ref src) const;
  bool operator<  (float16_ref src) const;
  #ifdef SOFTFLOAT_FAST_INT64
  void operator= (float128_ref src);
  #endif // SOFTFLOAT_FAST_INT64
};
// typedef float16_t bfloat16_t;

struct bfloat16_ref : bfloat16_t
{ 
  bfloat16_ref() = default;
  bfloat16_ref(const bfloat16_ref&) = default;
  bfloat16_ref(bfloat16_t bf16) { bfloat16_t::v=bf16.v; }
  #ifdef USE_SOFTFLOAT_OPERATORS
  bfloat16_t operator+ (bfloat16_t src);
  bfloat16_t operator- (bfloat16_t src);
  bfloat16_t operator* (bfloat16_t src);
  bfloat16_t operator/ (bfloat16_t src);
  void operator= (float16_t src);
  void operator= (float32_t src);
  void operator= (float64_t src);
  #endif // USE_SOFTFLOAT_OPERATORS
};

struct float32_ref : float32_t
{ 
  float32_ref() = default;
  float32_ref(const float32_ref&) = default;
  float32_ref(float32_t f32) { float32_t::v=f32.v; }
  #ifdef USE_SOFTFLOAT_OPERATORS
  void operator= (  uint32_t src);
  void operator= (  uint64_t src);
  void operator= (   int32_t src);
  void operator= (   int64_t src);
  void operator= ( float32_t src);
  void operator= ( float16_ref src);
  void operator= (bfloat16_ref src);
  float32_t operator+ (float32_ref src) const;
  float32_t operator- (float32_ref src) const;
  float32_t operator* (float32_ref src) const;
  float32_t operator/ (float32_ref src) const;
  float32_t operator% (float32_ref src) const;
  bool operator== (float32_ref src) const;
  bool operator<= (float32_ref src) const;
  bool operator<  (float32_ref src) const;
  #ifdef SOFTFLOAT_FAST_INT64
  void operator= (float128_ref src);
  #endif // SOFTFLOAT_FAST_INT64
  #endif // USE_SOFTFLOAT_OPERATORS
  
};

struct float64_ref : float64_t
{
  float64_ref() = default;
  float64_ref(const float64_ref&) = default;
  float64_ref(float64_t f64) { float64_t::v=f64.v; }
  #ifdef USE_SOFTFLOAT_OPERATORS
  void operator= (  uint32_t src);
  void operator= (  uint64_t src);
  void operator= (   int32_t src);
  void operator= (   int64_t src);
  void operator= ( float16_t src);
  void operator= ( float32_t src);
  void operator= ( float64_t src);
  void operator= (bfloat16_ref src);
  float64_t operator+ (float64_ref src) const;
  float64_t operator- (float64_ref src) const;
  float64_t operator* (float64_ref src) const;
  float64_t operator/ (float64_ref src) const;
  float64_t operator% (float64_ref src) const;
  bool operator== (float64_ref src) const;
  bool operator<= (float64_ref src) const;
  bool operator<  (float64_ref src) const;
  #ifdef SOFTFLOAT_FAST_INT64
  void operator= (float128_ref src);
  #endif // SOFTFLOAT_FAST_INT64
  #endif // USE_SOFTFLOAT_OPERATORS
};

struct float128_ref : float128_t
{ 
  #ifdef SOFTFLOAT_FAST_INT64
  #ifdef USE_SOFTFLOAT_OPERATORS
  void operator= (  uint32_t src);
  void operator= ( float16_t src);
  void operator= ( float32_t src);
  void operator= ( float64_t src);
  void operator= (float128_t src);
  float128_t operator+ (float128_ref src) const;
  float128_t operator- (float128_ref src) const;
  float128_t operator* (float128_ref src) const;
  float128_t operator/ (float128_ref src) const;
  float128_t operator% (float128_ref src) const;
  bool operator== (float128_ref src) const;
  bool operator<= (float128_ref src) const;
  bool operator<  (float128_ref src) const;
  #endif // USE_SOFTFLOAT_OPERATORS
  #endif // SOFTFLOAT_FAST_INT64
};

#endif
