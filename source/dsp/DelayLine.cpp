#include "DelayLine.h"

namespace lupex::dsp
{
DelayLine::DelayLine();
DelayLine::~DelayLine();
void DelayLine::prepare(const juce::dsp::ProcessSpec& spec);
void DelayLine::reset();
void DelayLine::setDelayTimeMilliseconds(float delayTimeMs);
void DelayLine::setFeedback(float feedbackAmount);
void DelayLine::setMix(float mixAmount);
float DelayLine::processSample(float inputSample);
}
