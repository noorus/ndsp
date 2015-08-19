#pragma once
#include "ndspTypes.h"
#include <math.h>

namespace ndsp {

  namespace math {

    constexpr Real cPi  = 3.1415926535897932; //!< Pi
    constexpr Real c2Pi = 6.2831853071795865; //!< 2 * Pi
    constexpr Real cE = 2.7182818284590452; //!< Euler's number

    inline Real sqrt( const Real x )
    {
      return ::sqrt( x );
    }

    inline Real arctanxy( const Real x, const Real y )
    {
      return ::atan2( y, x );
    }

    inline Real sin( const Real x )
    {
      return ::sin( x );
    }

    inline Real fmod( const Real x, const Real y )
    {
      return ::fmod( x, y );
    }

  }

}