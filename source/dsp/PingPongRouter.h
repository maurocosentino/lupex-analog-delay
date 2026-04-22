#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

namespace lupex::dsp
{
class PingPongRouter
{
public:
    PingPongRouter();
    ~PingPongRouter();

    void prepare(std::size_t maximumBlockSize);
    void reset();
    void setEnabled(bool shouldEnable);
    void process(juce::AudioBuffer<float>& buffer);
};
}
