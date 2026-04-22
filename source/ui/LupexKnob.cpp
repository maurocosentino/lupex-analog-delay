#include "LupexKnob.h"

namespace Lupex
{

    LupexKnob::LupexKnob (const juce::String& labelText, PedalLookAndFeel& laf)
        : label (labelText)
    {
        setLookAndFeel (&laf);
        setSliderStyle (juce::Slider::RotaryVerticalDrag);
        setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
        setRotaryParameters (juce::MathConstants<float>::pi * 1.25f,
                             juce::MathConstants<float>::pi * 2.75f,
                             true);
    }

    void LupexKnob::paint (juce::Graphics& g)
    {
        juce::Slider::paint (g);

        g.setColour (PedalLookAndFeel::textColour());
        g.setFont (juce::FontOptions (9.0f));
        g.drawFittedText (label,
                          0, getHeight() - 14,
                          getWidth(), 14,
                          juce::Justification::centred, 1);
    }

    void LupexKnob::resized()
    {
        juce::Slider::resized();
    }

} // namespace Lupex