#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

namespace lupex::parameters
{
class LupexParameters
{
public:
    LupexParameters();
    ~LupexParameters();

    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
};
}
