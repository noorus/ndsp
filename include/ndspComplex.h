#pragma once
#include "ndspTypes.h"
#include "ndspMath.h"

namespace ndsp {

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
      auto rsqr = rhs.sqr();
      auto rr = ( ( real * rhs.real + imaginary * rhs.imaginary ) / rsqr );
      auto ir = ( ( imaginary * rhs.real - real * rhs.imaginary ) / rsqr );
      return Complex( rr, ir );
    }
    //! negation (unary minus)
    inline Complex operator - () const
    {
      return Complex( -real, -imaginary );
    }
    //! conjugate
    inline Complex conjugate() const
    {
      return Complex( real, -imaginary );
    }
    inline Real sqr() const
    {
      return ( real * real + imaginary * imaginary );
    }
    //! magnitude (abs)
    inline Real magnitude() const
    {
      return math::sqrt( sqr() );
    }
    //! phase (argument)
    inline Real phase() const
    {
      return math::arctanxy( real, imaginary );
    }
  };

}