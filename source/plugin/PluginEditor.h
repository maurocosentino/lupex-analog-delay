#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace lupex::plugin
{
class PluginProcessor;

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor& processor);
    ~PluginEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
};
}
