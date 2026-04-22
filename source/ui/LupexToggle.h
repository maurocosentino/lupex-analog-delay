#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace lupex::ui
{
class LupexToggle : public juce::ToggleButton
{
public:
    LupexToggle();
    ~LupexToggle() override;

    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};
}
