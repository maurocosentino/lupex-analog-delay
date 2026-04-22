#include "BBDFilter.h"

namespace lupex::dsp
{
BBDFilter::BBDFilter();
BBDFilter::~BBDFilter();
void BBDFilter::prepare(const juce::dsp::ProcessSpec& spec);
void BBDFilter::reset();
void BBDFilter::setClockRate(float clockRateHz);
void BBDFilter::setDrive(float driveAmount);
float BBDFilter::processSample(float inputSample);
}
