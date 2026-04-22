#include "PingPongRouter.h"

namespace lupex::dsp
{
PingPongRouter::PingPongRouter();
PingPongRouter::~PingPongRouter();
void PingPongRouter::prepare(std::size_t maximumBlockSize);
void PingPongRouter::reset();
void PingPongRouter::setEnabled(bool shouldEnable);
void PingPongRouter::process(juce::AudioBuffer<float>& buffer);
}
