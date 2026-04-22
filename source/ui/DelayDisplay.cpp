#include "DelayDisplay.h"

namespace lupex::ui
{
DelayDisplay::DelayDisplay();
DelayDisplay::~DelayDisplay();
void DelayDisplay::paint(juce::Graphics& g);
void DelayDisplay::setDelayTimeMilliseconds(float delayTimeMs);
}
