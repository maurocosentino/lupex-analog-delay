#include "PluginEditor.h"

namespace lupex::plugin
{
PluginEditor::PluginEditor(PluginProcessor& processor);
PluginEditor::~PluginEditor();
void PluginEditor::paint(juce::Graphics& g);
void PluginEditor::resized();
}
