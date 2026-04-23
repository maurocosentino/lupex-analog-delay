#include "DelayLine.h"
#include <cmath>
#include <algorithm>

namespace Lupex
{

    DelayLine::DelayLine() = default;

    void DelayLine::prepare (double sr, float maxMs)
    {
        sampleRate = sr;
        maxDelayMs = maxMs;

        auto maxSamples = static_cast<size_t> (msToSamples (maxMs)) + 2;
        buffer.assign (maxSamples, 0.0f);
        writeIndex = 0;
    }

    void DelayLine::reset()
    {
        std::fill (buffer.begin(), buffer.end(), 0.0f);
        writeIndex = 0;
    }

    float DelayLine::process (float inputSample, float delayMs)
    {
        float delayedSample = readInterpolated (msToSamples (delayMs));
        buffer[static_cast<size_t> (writeIndex)] = inputSample;
        writeIndex = (writeIndex + 1) % static_cast<int> (buffer.size());
        return delayedSample;
    }

    float DelayLine::read (float delayMs) const
    {
        return readInterpolated (msToSamples (delayMs));
    }

    void DelayLine::write (float sample)
    {
        buffer[static_cast<size_t> (writeIndex)] = sample;
        writeIndex = (writeIndex + 1) % static_cast<int> (buffer.size());
    }

    float DelayLine::msToSamples (float ms) const
    {
        return static_cast<float> (sampleRate) * ms / 1000.0f;
    }

    float DelayLine::readInterpolated (float delaySamples) const
    {
        int bufferSize = static_cast<int> (buffer.size());

        float readPos = static_cast<float> (writeIndex) - delaySamples;
        while (readPos < 0.0f)
            readPos += static_cast<float> (bufferSize);

        int   index0   = static_cast<int> (readPos) % bufferSize;
        int   index1   = (index0 + 1) % bufferSize;
        float fraction = readPos - std::floor (readPos);

        return buffer[static_cast<size_t> (index0)]
             + fraction * (buffer[static_cast<size_t> (index1)]
                         - buffer[static_cast<size_t> (index0)]);
    }

} // namespace Lupex