#pragma once
#include "ndspPrerequisites.h"

namespace ndsp {

  typedef double Sample;
  typedef double Real;
  typedef double Time;
  typedef std::string utf8String;

  enum Waveform {
    WaveformSine = 0,
    WaveformSquare,
    WaveformTriangle,
    WaveformSawtooth,
    WaveformInverseSawtooth
  };

}