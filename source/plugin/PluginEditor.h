#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

namespace Lupex
{

    class LupexEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit LupexEditor (LupexProcessor&);
        ~LupexEditor() override;

        void paint (juce::Graphics&) override;
        void resized() override;

    private:
        LupexProcessor& processor;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LupexEditor)
    };

} // namespace Lupex