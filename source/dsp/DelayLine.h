#pragma once

#include <vector>
#include <cstddef>

namespace Lupex
{

    class DelayLine
    {
    public:
        DelayLine();

        void prepare (double sampleRate, float maxDelayMs);
        void reset();

        // Proceso combinado (solo lectura + avance)
        float process (float inputSample, float delayMs);

        // Lectura y escritura separadas
        float read  (float delayMs) const;
        void  write (float sample);

    private:
        float msToSamples    (float ms) const;
        float readInterpolated (float delaySamples) const;

        std::vector<float> buffer;
        int    writeIndex { 0 };
        double sampleRate { 44100.0 };
        float  maxDelayMs { 1200.0f };
    };

} // namespace Lupex