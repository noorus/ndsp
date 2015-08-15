#include "ndsp.h"

namespace ndsp {

  const uint32_t cInitialHeapSize = 10240;

  System::System(): mHeap( NULL )
  {
    mHeap = HeapCreate( HEAP_GENERATE_EXCEPTIONS, cInitialHeapSize, 0 );
    if ( !mHeap )
      throw std::exception( "Heap creation failed" );

    ULONG lfh = 2;
    HeapSetInformation( mHeap, HeapCompatibilityInformation, &lfh, sizeof( ULONG ) );
  }

  void* System::alloc( size_t size )
  {
    return HeapAlloc( mHeap, HEAP_ZERO_MEMORY, size );
  }

  void* System::realloc( void* allocation, size_t newSize )
  {
    return HeapReAlloc( mHeap, HEAP_ZERO_MEMORY, allocation, newSize );
  }

  void System::free( void* allocation )
  {
    HeapFree( mHeap, HEAP_ZERO_MEMORY, allocation );
  }

  System::~System()
  {
    if ( mHeap )
      HeapDestroy( mHeap );
  }

  void System::initialize()
  {
    _MM_SET_ROUNDING_MODE( _MM_ROUND_NEAREST );
    _MM_SET_DENORMALS_ZERO_MODE( _MM_DENORMALS_ZERO_ON );
    _MM_SET_FLUSH_ZERO_MODE( _MM_FLUSH_ZERO_ON );
  }

  void System::shutdown()
  {
    //
  }

}