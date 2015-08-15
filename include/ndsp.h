#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <list>
#include <vector>
#include <string>
#include <exception>
#include "ndspTypes.h"

namespace ndsp {

  class System {
  protected:
    HANDLE mHeap;
  public:
    System();
    void initialize();
    void shutdown();
    void* alloc( size_t size );
    void* realloc( void* allocation, size_t newSize );
    void free( void* allocation );
    ~System();
  };

  class Buffer {
  protected:
    size_t mLength;
    Sample* mBuffer;
  public:
    Buffer( size_t length );
    ~Buffer();
  };

  typedef std::vector<Buffer*> BufferVector;

  class Channel {
  public:
  };

  typedef std::vector<Channel*> ChannelVector;

  class Processor {
  protected:
    ChannelVector mChannels;
  };

}