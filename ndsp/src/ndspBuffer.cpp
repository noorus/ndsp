#include "ndsp.h"
#include "ndspUtil.h"

namespace ndsp {

  Buffer::Buffer( size_t length ): mLength( length ), mBuffer( nullptr )
  {
    mBuffer = (Sample*)util::avx_malloc( mLength * sizeof( Sample ) );
  }

  Buffer::~Buffer()
  {
    util::avx_free( mBuffer );
  }

}