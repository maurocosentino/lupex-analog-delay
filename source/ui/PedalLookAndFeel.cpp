#include "PedalLookAndFeel.h"

namespace lupex::ui
{
PedalLookAndFeel::PedalLookAndFeel();
PedalLookAndFeel::~PedalLookAndFeel();
void PedalLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                        int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPosProportional,
                                        float rotaryStartAngle,
                                        float rotaryEndAngle,
                                        juce::Slider& slider);
}
