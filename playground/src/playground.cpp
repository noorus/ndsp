#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <pmmintrin.h>

typedef double Real;

#define AVX_ALIGN __declspec(align(32))

AVX_ALIGN class vec4 {
public:
  union {
    struct {
      Real x, y, z, w;
    };
    __m256d packed;
  };
  inline vec4()
  {
    packed = _mm256_setzero_pd();
  }
  inline vec4( const Real value )
  {
    packed = _mm256_broadcast_sd( &value );
  }
  inline vec4( __m256d& rhs ): packed( rhs )
  {
  }
  inline vec4( Real _x, Real _y, Real _z, Real _w )
  {
    packed = _mm256_setr_pd( _x, _y, _z, _w );
  }
  //! Load four 32-byte boundary aligned sample values into vector
  inline void load( const Real* values )
  {
    packed = _mm256_load_pd( values );
  }
  //! Load four unaligned sample values into vector
  inline void loadUnaligned( const Real* values )
  {
    packed = _mm256_loadu_pd( values );
  }
  //! Store four sample values from vector to 32-byte boundary aligned memory
  inline void store( Real* values )
  {
    _mm256_stream_pd( values, packed );
  }
  //! Store four sample values from vector to unaligned memory
  inline void storeUnaligned( Real* values )
  {
    _mm256_store_pd( values, packed );
  }
  //! Set all vector members to single value
  inline void set( const Real* value )
  {
    packed = _mm256_broadcast_sd( value );
  }
  //! Set vector members individually
  inline void set( Real _x, Real _y, Real _z, Real _w )
  {
    packed = _mm256_setr_pd( _x, _y, _z, _w );
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
  //! v = a & b (bitwise and)
  inline vec4 operator & ( const vec4& rhs ) const
  {
    return _mm256_and_pd( packed, rhs.packed );
  }
  //! v = a | b (bitwise or)
  inline vec4 operator | ( const vec4& rhs ) const
  {
    return _mm256_or_pd( packed, rhs.packed );
  }
  //! v = a ^ b (bitwise xor)
  inline vec4 operator ^ ( const vec4& rhs ) const
  {
    return _mm256_xor_pd( packed, rhs.packed );
  }
  //! v = a * b
  inline vec4 operator * ( const Real scalar ) const
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
  inline vec4 operator / ( const Real scalar ) const
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
  //! v = round(a)
  inline vec4 round() const
  {
    return _mm256_round_pd( packed, _MM_FROUND_NINT );
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
  //! f = x + y + z + w
  inline Real sum() const
  {
    auto hadd = _mm256_hadd_pd( packed, packed );
    auto hi = _mm256_extractf128_pd( hadd, 1 );
    auto lo = _mm256_castpd256_pd128( hadd );
    auto ret = _mm_add_sd( lo, hi );
    return _mm_cvtsd_f64( ret );
  }
  //! v = a * b + c (fused multiply & add)
  static inline vec4 fma( const vec4& a, const vec4& b, const vec4& c )
  {
    return _mm256_fmadd_pd( a.packed, b.packed, c.packed );
  }
  //! v = a * b - c (fused multiply & subtract)
  static inline vec4 fms( const vec4& a, const vec4& b, const vec4& c )
  {
    return _mm256_fmsub_pd( a.packed, b.packed, c.packed );
  }
};

class Complex {
public:
  Real real;
  Real imaginary;
public:
  inline Complex(): real( 0.0 ), imaginary( 0.0 )
  {
  }
  inline Complex( const Real real_, const Real imaginary_ = 0.0 ) :
  real( real_ ), imaginary( imaginary_ )
  {
  }
  //! equality
  inline bool operator == ( const Complex& rhs ) const
  {
    return ( real == rhs.real && imaginary == rhs.imaginary );
  }
  //! addition
  inline Complex operator + ( const Complex& rhs ) const
  {
    return Complex( real + rhs.real, imaginary + rhs.imaginary );
  }
  //! subtraction
  inline Complex operator - ( const Complex& rhs ) const
  {
    return Complex( real - rhs.real, imaginary - rhs.imaginary );
  }
  //! multiplication
  inline Complex operator * ( const Complex& rhs ) const
  {
    auto rr = ( ( real * rhs.real ) - ( imaginary * rhs.imaginary ) );
    auto ir = ( ( imaginary * rhs.real ) + ( real * rhs.imaginary ) );
    return Complex( rr, ir );
  }
  //! division
  inline Complex operator / ( const Complex& rhs ) const
  {
    auto tmp = ( rhs.real * rhs.real + rhs.imaginary * rhs.imaginary );
    auto rr = ( ( real * rhs.real + imaginary * rhs.imaginary ) / tmp );
    auto ir = ( ( imaginary * rhs.real - real * rhs.imaginary ) / tmp );
    return Complex( rr, ir );
  }
  //! negation (unary minus)
  inline Complex operator - () const
  {
    return Complex( -real, -imaginary );
  }
};

int main( int argc, char** argv, char** env )
{
  printf( "playground\n" );

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