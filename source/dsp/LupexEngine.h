#pragma once

#include "PingPongRouter.h"

namespace Lupex
{

    class LupexEngine
    {
    public:
        LupexEngine();

        void prepare (double sampleRate, int samplesPerBlock);
        void reset();

        // Procesa un buffer completo de audio
        void process (float* channelL, float* channelR,
                      int    numSamples,
                      float  delayMs,  float feedback,
                      float  mix,      float tone,
                      float  drive,    bool  pingPong,
                      bool   filterOn);

    private:
        PingPongRouter router;

        // Mezcla wet/dry — 0.0 = solo seco, 1.0 = solo wet
        float applyMix (float dry, float wet, float mix) const;
    };

} // namespace Lupex