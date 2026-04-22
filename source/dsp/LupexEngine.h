#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

namespace lupex::dsp
{
class LupexEngine
{
public:
    LupexEngine();
    ~LupexEngine();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();
    void process(juce::AudioBuffer<float>& buffer);
    void setTempo(double bpm);
};
}
