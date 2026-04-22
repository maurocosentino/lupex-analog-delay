#pragma once

#include <juce_dsp/juce_dsp.h>

namespace lupex::dsp
{
class DelayLine
{
public:
    DelayLine();
    ~DelayLine();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void setDelayTimeMilliseconds(float delayTimeMs);
    void setFeedback(float feedbackAmount);
    void setMix(float mixAmount);
    float processSample(float inputSample);
};
}
