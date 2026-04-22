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

        // Procesa un par de samples estéreo
        // inputL/R  → señal seca entrante
        // outputL/R → señal con ping-pong aplicado
        void process (float  inputL,    float  inputR,
                      float& outputL,   float& outputR,
                      float  delayMs,   float  feedback,
                      float  tone,      float  drive,
                      bool   filterOn);

    private:
        // Dos delay lines independientes — uno por canal
        DelayLine    delayL;
        DelayLine    delayR;

        // Filtros y saturación independientes por canal
        BBDFilter    filterL;
        BBDFilter    filterR;
        TapeEmulator tapeL;
        TapeEmulator tapeR;
    };

} // namespace Lupex