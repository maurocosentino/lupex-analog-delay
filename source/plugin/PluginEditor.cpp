#include "PluginEditor.h"

namespace Lupex
{

    LupexEditor::LupexEditor (LupexProcessor& p)
        : AudioProcessorEditor (&p), processor (p)
    {
        setSize (400, 300);
    }

    LupexEditor::~LupexEditor() {}

    void LupexEditor::paint (juce::Graphics& g)
    {
        g.fillAll (juce::Colour (0x1a1a1aff));
        g.setColour (juce::Colours::white);
        g.setFont (20.0f);
        g.drawFittedText ("Lupex", getLocalBounds(), juce::Justification::centred, 1);
    }

    void LupexEditor::resized() {}

} // namespace Lupex