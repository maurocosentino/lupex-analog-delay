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

        void process (float* channelL, float* channelR,
                      int    numSamples,
                      float  delayMs,  float feedback,
                      float  mix,      float tone,
                      float  drive);

    private:
        PingPongRouter router;
        float applyMix (float dry, float wet, float mix) const;
    };

} // namespace Lupex