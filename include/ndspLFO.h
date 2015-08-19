#pragma once
#include "ndspTypes.h"

namespace ndsp {

  class LFO {
  private:
    LFO() {}
  protected:
    Waveform mWaveform;
    Real mPhase;
  public:
    explicit LFO( const Waveform waveform, const Real phase );
    const Waveform getWaveform() const;
    void setWaveform( const Waveform waveform );
    const Real getPhase() const;
    void setPhase( const Real phase );
    const Real process( const Real delta );
    ~LFO();
  };

}