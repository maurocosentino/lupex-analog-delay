#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace lupex::ui
{
class DelayDisplay : public juce::Component
{
public:
    DelayDisplay();
    ~DelayDisplay() override;

    void paint(juce::Graphics& g) override;
    void setDelayTimeMilliseconds(float delayTimeMs);
};
}
