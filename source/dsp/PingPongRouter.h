#pragma once

#include "DelayLine.h"
#include "BBDFilter.h"
#include "TapeEmulator.h"

namespace Lupex
{

    class PingPongRouter
    {
    public:
        PingPongRouter();

        void prepare (double sampleRate, float maxDelayMs);
        void reset();

        void process (float  inputL,    float  inputR,
                      float& outputL,   float& outputR,
                      float  delayMs,   float  feedback,
                      float  tone,      float  drive,
                      bool   filterOn);

    private:
        DelayLine    delayL;
        DelayLine    delayR;
        BBDFilter    filterL;
        BBDFilter    filterR;
        TapeEmulator tapeL;
        TapeEmulator tapeR;

        // Estado del feedback entre samples
        float lastFeedbackL { 0.0f };
        float lastFeedbackR { 0.0f };
    };

} // namespace Lupex