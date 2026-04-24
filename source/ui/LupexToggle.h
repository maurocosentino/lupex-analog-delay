#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Lupex
{

    class LupexToggle : public juce::Button
    {
    public:
        LupexToggle();

        void paintButton (juce::Graphics&,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;

    private:
        juce::Image toggleStrip;

        static constexpr int frameSize { 128 };
    };

} // namespace Lupex