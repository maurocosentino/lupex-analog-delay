#pragma once

#include <juce_dsp/juce_dsp.h>

namespace lupex::dsp
{
class TapeEmulator
{
public:
    TapeEmulator();
    ~TapeEmulator();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void setWowAndFlutter(float amount);
    void setSaturation(float amount);
    float processSample(float inputSample);
};
}
