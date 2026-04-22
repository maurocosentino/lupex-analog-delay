#include "LupexParameters.h"

namespace lupex::parameters
{
LupexParameters::LupexParameters();
LupexParameters::~LupexParameters();
juce::AudioProcessorValueTreeState::ParameterLayout LupexParameters::createLayout();
}
