#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace lupex::ui
{
class PedalLookAndFeel : public juce::LookAndFeel_V4
{
public:
    PedalLookAndFeel();
    ~PedalLookAndFeel() override;

    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
};
}
