#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace Lupex
{

LupexProcessor::LupexProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this)
{
}

LupexProcessor::~LupexProcessor() {}

void LupexProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    engine.prepare (sampleRate, samplesPerBlock);
}

void LupexProcessor::releaseResources()
{
    engine.reset();
}

    void LupexProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                        juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    float delayMs  = parameters.getTime();
    float feedback = parameters.getFeedback();
    float mix      = parameters.getMix();
    float tone     = parameters.getTone();
    float drive    = feedback * 0.5f;

    float* channelL = buffer.getWritePointer (0);
    float* channelR = buffer.getWritePointer (1);

    engine.process (channelL, channelR,
                    buffer.getNumSamples(),
                    delayMs, feedback,
                    mix, tone, drive);
}

juce::AudioProcessorEditor* LupexProcessor::createEditor()
{
    return new LupexEditor (*this);
}

bool LupexProcessor::hasEditor() const { return true; }
const juce::String LupexProcessor::getName() const { return JucePlugin_Name; }
bool LupexProcessor::acceptsMidi() const { return false; }
bool LupexProcessor::producesMidi() const { return false; }
double LupexProcessor::getTailLengthSeconds() const { return 2.0; }
int LupexProcessor::getNumPrograms() { return 1; }
int LupexProcessor::getCurrentProgram() { return 0; }
void LupexProcessor::setCurrentProgram (int) {}
const juce::String LupexProcessor::getProgramName (int) { return {}; }
void LupexProcessor::changeProgramName (int, const juce::String&) {}

void LupexProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void LupexProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    if (xml && xml->hasTagName (parameters.apvts.state.getType()))
        parameters.apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

} // namespace Lupex

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Lupex::LupexProcessor();
}