#include "LupexEngine.h"

namespace lupex::dsp
{
LupexEngine::LupexEngine();
LupexEngine::~LupexEngine();
void LupexEngine::prepare(const juce::dsp::ProcessSpec& spec);
void LupexEngine::reset();
void LupexEngine::process(juce::AudioBuffer<float>& buffer);
void LupexEngine::setTempo(double bpm);
}
