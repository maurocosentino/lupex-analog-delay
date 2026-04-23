#include "LupexEngine.h"
#include <juce_core/juce_core.h>

namespace Lupex
{

    LupexEngine::LupexEngine() = default;

    void LupexEngine::prepare (double sampleRate, int)
    {
        delayL.prepare (sampleRate, 1200.0f);
        delayR.prepare (sampleRate, 1200.0f);
        filterL.prepare (sampleRate);
        filterR.prepare (sampleRate);
    }

    void LupexEngine::reset()
    {
        delayL.reset();
        delayR.reset();
        filterL.reset();
        filterR.reset();
        tapeL.reset();
        tapeR.reset();
    }

    void LupexEngine::process (float* channelL, float* channelR,
                            int    numSamples,
                            float  delayMs,
                            float  feedback,
                            float  mix,
                            float  tone)
    {
        filterL.setTone (tone);
        filterR.setTone (tone);
        tapeL.setDrive (0.15f);
        tapeR.setDrive (0.15f);

        for (int i = 0; i < numSamples; ++i)
        {
            // Suavizar el delay time sample a sample
            // smoothingCoeff cercano a 1.0 = movimiento más lento = pitch más suave
            currentDelayMs = currentDelayMs * smoothingCoeff
                           + delayMs * (1.0f - smoothingCoeff);

            float dryL = channelL[i];
            float dryR = channelR[i];

            float wetL = delayL.read (currentDelayMs);
            float wetR = delayR.read (currentDelayMs);

            float fbL = juce::jlimit (-0.95f, 0.95f, wetL * feedback);
            float fbR = juce::jlimit (-0.95f, 0.95f, wetR * feedback);

            fbL = filterL.process (fbL);
            fbR = filterR.process (fbR);
            fbL = tapeL.process (fbL);
            fbR = tapeR.process (fbR);

            delayL.write (dryL + fbL);
            delayR.write (dryR + fbR);

            channelL[i] = applyMix (dryL, wetL, mix);
            channelR[i] = applyMix (dryR, wetR, mix);
        }
    }

    float LupexEngine::applyMix (float dry, float wet, float mix) const
    {
        return dry * (1.0f - mix) + wet * mix;
    }

} // namespace Lupex