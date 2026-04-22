#pragma once

#include <juce_dsp/juce_dsp.h>

namespace lupex::dsp
{
class BBDFilter
{
public:
    BBDFilter();
    ~BBDFilter();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void setClockRate(float clockRateHz);
    void setDrive(float driveAmount);
    float processSample(float inputSample);
};
}
