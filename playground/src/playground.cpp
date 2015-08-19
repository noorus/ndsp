#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <math.h>
#include "ndspLFO.h"

int main( int argc, char** argv, char** env )
{
  printf( "playground\n" );

  ndsp::LFO* lfo = new ndsp::LFO( ndsp::WaveformInverseSawtooth, 0.0 );
  for ( int i = 0; i < 20; i++ )
  {
    printf( "InverseSawtooth %i: %f\n", i, lfo->process( 0.1 ) );
  }
  delete lfo;

  return EXIT_SUCCESS;
}