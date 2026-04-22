#include "TapeEmulator.h"

namespace lupex::dsp
{
TapeEmulator::TapeEmulator();
TapeEmulator::~TapeEmulator();
void TapeEmulator::prepare(const juce::dsp::ProcessSpec& spec);
void TapeEmulator::reset();
void TapeEmulator::setWowAndFlutter(float amount);
void TapeEmulator::setSaturation(float amount);
float TapeEmulator::processSample(float inputSample);
}
