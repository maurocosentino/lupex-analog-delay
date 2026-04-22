#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace lupex::ui
{
class LupexKnob : public juce::Slider
{
public:
    LupexKnob();
    ~LupexKnob() override;

    void paint(juce::Graphics& g) override;
};
}
