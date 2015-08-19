#include "ndspLFO.h"
#include "ndspMath.h"

namespace ndsp {

  LFO::LFO( const Waveform waveform, const Real phase ):
  mWaveform( waveform ), mPhase( phase )
  {
    //
  }

  const Waveform LFO::getWaveform() const
  {
    return mWaveform;
  }

  void LFO::setWaveform( const Waveform waveform )
  {
    mWaveform = waveform;
  }

  const Real LFO::getPhase() const
  {
    return mPhase;
  }

  void LFO::setPhase( const Real phase )
  {
    mPhase = phase;
    if ( mPhase < 0.0 )
      mPhase = 0.0;
    if ( mPhase > 1.0 )
      mPhase = math::fmod( 1.0, mPhase );
  }

  const Real LFO::process( const Real delta )
  {
    mPhase += delta;

    while ( mPhase > 1.0 )
      mPhase -= 1.0;

    switch ( mWaveform )
    {
      case WaveformSine:
        return math::sin( mPhase * math::c2Pi );
        break;
      case WaveformSquare:
        return ( mPhase < 0.5 ? 1.0 : -1.0 );
        break;
      case WaveformTriangle:
        if ( mPhase < 0.25 )
          return ( 4.0 * mPhase );
        else if ( mPhase < 0.75 )
          return ( 1.0 - 4.0 * ( mPhase - 0.25 ) );
        else
          return ( -1.0 + 4.0 * ( mPhase - 0.75 ) );
        break;
      case WaveformSawtooth:
        return ( mPhase < 0.5 ? 2.0 * mPhase : 2.0 * mPhase - 2.0 );
        break;
      case WaveformInverseSawtooth:
        return ( mPhase < 0.5 ? -2.0 * mPhase : 2.0 - 2.0 * mPhase );
        break;
    }
  }

  LFO::~LFO()
  {
    //
  }

}