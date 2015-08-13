#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <pmmintrin.h>

typedef double sample;
typedef double real;

#define AVX_ALIGN __declspec(align(32))

AVX_ALIGN class vec4 {
public:
  union {
    struct {
      sample x, y, z, w;
    };
    __m256d packed;
  };
  inline vec4()
  {
    packed = _mm256_setzero_pd();
  }
  inline vec4( const sample value )
  {
    packed = _mm256_broadcast_sd( &value );
  }
  inline vec4( __m256d& rhs ): packed( rhs )
  {
  }
  inline vec4( sample _x, sample _y, sample _z, sample _w )
  {
    packed = _mm256_set_pd( _x, _y, _z, _w );
  }
  inline void set( const sample value )
  {
    packed = _mm256_broadcast_sd( &value );
  }
  inline void set( sample _x, sample _y, sample _z, sample _w )
  {
    packed = _mm256_set_pd( _x, _y, _z, _w );
  }
  //! v = a + b
  inline vec4 operator + ( const vec4& rhs ) const
  {
    return _mm256_add_pd( packed, rhs.packed );
  }
  //! v = a - b
  inline vec4 operator - ( const vec4& rhs ) const
  {
    return _mm256_sub_pd( packed, rhs.packed );
  }
  //! v = a xor b
  inline vec4 operator ^ ( const vec4& rhs ) const
  {
    return _mm256_xor_pd( packed, rhs.packed );
  }
  //! v = a * b
  inline vec4 operator * ( const real scalar ) const
  {
    auto im = _mm256_set1_pd( scalar );
    return _mm256_mul_pd( packed, im );
  }
  //! v = a * b
  inline vec4 operator * ( const vec4& rhs ) const
  {
    return _mm256_mul_pd( packed, rhs.packed );
  }
  //! v = a / b
  inline vec4 operator / ( const real scalar ) const
  {
    auto im = _mm256_set1_pd( scalar );
    return _mm256_div_pd( packed, im );
  }
  //! v = a / b
  inline vec4 operator / ( const vec4& rhs ) const
  {
    return _mm256_div_pd( packed, rhs.packed );
  }
  //! a == b
  inline bool operator == ( const vec4& rhs ) const
  {
    auto ret = _mm256_cmp_pd( packed, rhs.packed, _CMP_NEQ_OS );
    return ( _mm256_movemask_pd( ret ) == 0 );
  }
  //! a != b
  inline bool operator != ( const vec4& rhs ) const
  {
    auto ret = _mm256_cmp_pd( packed, rhs.packed, _CMP_EQ_OS );
    return ( _mm256_movemask_pd( ret ) == 0 );
  }
  //! v = ceil(a)
  inline vec4 ceil() const
  {
    return _mm256_round_pd( packed, _MM_FROUND_CEIL );
  }
  //! v = floor(a)
  inline vec4 floor() const
  {
    return _mm256_round_pd( packed, _MM_FROUND_FLOOR );
  }
  //! v = trunc(a)
  inline vec4 trunc() const
  {
    return _mm256_round_pd( packed, _MM_FROUND_TRUNC );
  }
  //! v = sqrt(a)
  inline vec4 sqrt() const
  {
    return _mm256_sqrt_pd( packed );
  }
};

int main( int argc, char** argv, char** env )
{
  printf( "playground\n" );

  // set DAZ & FTZ, rounding to nearest
  _MM_SET_ROUNDING_MODE( _MM_ROUND_NEAREST );
  _MM_SET_DENORMALS_ZERO_MODE( _MM_DENORMALS_ZERO_ON );
  _MM_SET_FLUSH_ZERO_MODE( _MM_FLUSH_ZERO_ON );

  vec4 a( 1, 2, 3, 4 );
  vec4 b( 5, 6, 7, 8 );
  vec4 c = a + b;
  vec4 d;

  printf( "a: %f %f %f %f\n", a.x, a.y, a.z, a.w );
  printf( "b: %f %f %f %f\n", b.x, b.y, b.z, b.w );
  printf( "c: %f %f %f %f\n", c.x, c.y, c.z, c.w );
  printf( "d: %f %f %f %f\n", d.x, d.y, d.z, d.w );

  vec4 e( 1, 0, 3.31, -4 );
  vec4 f( 1, -0.0, 3.31, -4.000 );

  printf( "comparison = %s\n", e == f ? "true" : "false" );

  return EXIT_SUCCESS;
}