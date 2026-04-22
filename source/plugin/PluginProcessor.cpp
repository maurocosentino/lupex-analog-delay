#include "PluginProcessor.h"

namespace lupex::plugin
{
PluginProcessor::PluginProcessor();
PluginProcessor::~PluginProcessor();
void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock);
void PluginProcessor::releaseResources();
bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const;
void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
juce::AudioProcessorEditor* PluginProcessor::createEditor();
bool PluginProcessor::hasEditor() const;
const juce::String PluginProcessor::getName() const;
bool PluginProcessor::acceptsMidi() const;
bool PluginProcessor::producesMidi() const;
bool PluginProcessor::isMidiEffect() const;
double PluginProcessor::getTailLengthSeconds() const;
int PluginProcessor::getNumPrograms();
int PluginProcessor::getCurrentProgram();
void PluginProcessor::setCurrentProgram(int index);
const juce::String PluginProcessor::getProgramName(int index);
void PluginProcessor::changeProgramName(int index, const juce::String& newName);
void PluginProcessor::getStateInformation(juce::MemoryBlock& destData);
void PluginProcessor::setStateInformation(const void* data, int sizeInBytes);
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();
}
