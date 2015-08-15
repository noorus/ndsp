#pragma once
#include "ndspTypes.h"
#include <math.h>

namespace ndsp {

  namespace math {

    inline Real sqrt( const Real x )
    {
      return ::sqrt( x );
    }

    inline Real arctanxy( const Real x, const Real y )
    {
      return ::atan2( y, x );
    }

  }

}