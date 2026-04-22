#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "../ui/PedalLookAndFeel.h"
#include "../ui/LupexKnob.h"
#include "PluginProcessor.h"

namespace Lupex
{

    class LupexEditor : public juce::AudioProcessorEditor
    {
    public:
        explicit LupexEditor (LupexProcessor&);
        ~LupexEditor() override;

        void paint   (juce::Graphics&) override;
        void resized() override;

    private:
        LupexProcessor&   processor;
        PedalLookAndFeel  laf;

        LupexKnob          knobTime     { "TIME",     laf };
        LupexKnob          knobFeedback { "FEEDBACK", laf };
        LupexKnob          knobTone     { "TONE",     laf };
        LupexKnob          knobMix      { "MIX",      laf };

        juce::ToggleButton toggle;
        juce::ToggleButton bypass;

        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
        using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

        std::unique_ptr<SliderAttachment> attachTime;
        std::unique_ptr<SliderAttachment> attachFeedback;
        std::unique_ptr<SliderAttachment> attachTone;
        std::unique_ptr<SliderAttachment> attachMix;
        std::unique_ptr<ButtonAttachment> attachToggle;

        bool bypassActive { true };

        void drawPedalBody  (juce::Graphics&);
        void drawBypassLed  (juce::Graphics&);
        void drawBrandLabel (juce::Graphics&);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LupexEditor)
    };

} // namespace Lupex