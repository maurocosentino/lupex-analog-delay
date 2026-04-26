#pragma once

#include "DelayLine.h"
#include "BBDFilter.h"
#include "TapeEmulator.h"

namespace Lupex
{

    class LupexEngine
    {
    public:
        LupexEngine();

        void prepare (double sampleRate, int samplesPerBlock);
        void setPingPong (bool enabled);
        void reset();

        void process (float* channelL, float* channelR,
                      int    numSamples,
                      float  delayMs,
                      float  feedback,
                      float  mix,
                      float  tone);

    private:
        DelayLine    delayL;
        DelayLine    delayR;
        BBDFilter    filterL;
        BBDFilter    filterR;
        TapeEmulator tapeL;
        TapeEmulator tapeR;

        // Smoother para el delay time — evita glitches y crea pitch shift
        float currentDelayMs { 300.0f };
        float targetDelayMs  { 300.0f };
        static constexpr float maxStepMs { 0.5f };
        static constexpr float stereoSpread { 0.01f };
        bool pingPong { false };

        float applyMix (float dry, float wet, float mix) const;
        float pingPongMix { 0.0f };        // 0.0 = normal, 1.0 = ping-pong
        static constexpr float pingPongSlew { 0.005f };  // antes: 0.001f
    };

} // namespace Lupex