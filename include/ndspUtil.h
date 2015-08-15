#pragma once
#include "ndspTypes.h"
#include <stdlib.h>
#include <exception>

namespace ndsp {

  namespace util {

    inline void* avx_malloc( size_t size )
    {
      auto ret = _aligned_malloc( size, 32 );
      if ( !ret )
        throw std::exception( "Allocation failed" );
      return ret;
    }

    inline void avx_free( void* memory )
    {
      _aligned_free( memory );
    }

    inline Real todB( const Real value )
    {
      return ( 20.0 * log10( value ) );
    }

    inline Real fromdB( const Real value )
    {
      return ( pow( 10.0, ( value / 20.0 ) ) );
    }

  }

}