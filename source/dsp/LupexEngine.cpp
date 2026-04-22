#include "LupexEngine.h"

namespace Lupex
{

    LupexEngine::LupexEngine() = default;

    void LupexEngine::prepare (double sampleRate, int /*samplesPerBlock*/)
    {
        router.prepare (sampleRate, 1200.0f);
    }

    void LupexEngine::reset()
    {
        router.reset();
    }

    void LupexEngine::process (float* channelL, float* channelR,
                                int    numSamples,
                                float  delayMs,  float feedback,
                                float  mix,      float tone,
                                float  drive)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float dryL = channelL[i];
            float dryR = channelR[i];
            float wetL = 0.0f;
            float wetR = 0.0f;

            router.process (dryL, dryL,
                            wetL, wetR,
                            delayMs, feedback,
                            tone, drive, false);

            wetR = wetL;

            channelL[i] = applyMix (dryL, wetL, mix);
            channelR[i] = applyMix (dryR, wetR, mix);
        }
    }

    float LupexEngine::applyMix (float dry, float wet, float mix) const
    {
        return dry * (1.0f - mix) + wet * mix;
    }

} // namespace Lupex