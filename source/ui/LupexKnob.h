#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PedalLookAndFeel.h"

namespace Lupex
{

    class LupexKnob : public juce::Slider
    {
    public:
        LupexKnob (const juce::String& labelText, PedalLookAndFeel& laf);

        void paint   (juce::Graphics&) override;
        void resized() override;

    private:
        juce::String label;
    };

} // namespace Lupex