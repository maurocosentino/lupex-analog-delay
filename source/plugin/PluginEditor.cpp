#include "PluginEditor.h"
#include <BinaryData.h>
namespace Lupex
{

LupexEditor::LupexEditor (LupexProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setLookAndFeel (&laf);
    setSize (260, 420);

    addAndMakeVisible (knobTime);
    addAndMakeVisible (knobFeedback);
    addAndMakeVisible (knobTone);
    addAndMakeVisible (knobMix);

    toggle.setButtonText ("—");
    toggle.setLookAndFeel (&laf);
    addAndMakeVisible (toggle);

    bypass.setButtonText ("BYPASS");
    bypass.setLookAndFeel (&laf);
    bypass.setToggleState (true, juce::dontSendNotification);
    bypass.onClick = [this]
    {
        bypassActive = !bypassActive;
        bypass.setToggleState (bypassActive, juce::dontSendNotification);
        repaint();
    };
    addAndMakeVisible (bypass);

    // Attachments se crean acá — después de que los knobs existen
    auto& apvts = processor.parameters.apvts;
    attachTime     = std::make_unique<SliderAttachment> (apvts, "time",     knobTime);
    attachFeedback = std::make_unique<SliderAttachment> (apvts, "feedback", knobFeedback);
    attachTone     = std::make_unique<SliderAttachment> (apvts, "tone",     knobTone);
    attachMix      = std::make_unique<SliderAttachment> (apvts, "mix",      knobMix);
    attachToggle   = std::make_unique<ButtonAttachment> (apvts, "toggle",   toggle);
}

LupexEditor::~LupexEditor()
{
    setLookAndFeel (nullptr);
}

void LupexEditor::paint (juce::Graphics& g)
{
    drawPedalBody  (g);
    drawBypassLed  (g);
    drawBrandLabel (g);
}

void LupexEditor::resized()
{
    auto area  = getLocalBounds().reduced (24);
    int  knobS = 72;

    // Fila superior — TIME, FEEDBACK, TONE
    auto topRow = area.removeFromTop (knobS + 16);
    knobTime    .setBounds (topRow.removeFromLeft (knobS));
    topRow.removeFromLeft (8);
    knobFeedback.setBounds (topRow.removeFromLeft (knobS));
    topRow.removeFromLeft (8);
    knobTone    .setBounds (topRow.removeFromLeft (knobS));

    area.removeFromTop (16);

    // Fila media — TOGGLE · LED · MIX
    auto midRow = area.removeFromTop (knobS);
    toggle.setBounds (midRow.removeFromLeft (64)
                           .withHeight (40)
                           .withY (midRow.getY() + 16));
    knobMix.setBounds (midRow.removeFromRight (knobS));

    area.removeFromTop (24);

    // Bypass centrado abajo
    int fsSize = 56;
    bypass.setBounds (getWidth() / 2 - fsSize / 2,
                      area.getY(),
                      fsSize, fsSize);
}

    void LupexEditor::drawPedalBody (juce::Graphics& g)
{
    auto bg = juce::ImageCache::getFromMemory (
        BinaryData::background_png,
        BinaryData::background_pngSize);

    g.drawImageWithin (bg, 0, 0, getWidth(), getHeight(),
                       juce::RectanglePlacement::stretchToFit);
}

void LupexEditor::drawBypassLed (juce::Graphics& g)
{
    float ledX = getWidth()  * 0.5f;
    float ledY = getHeight() * 0.56f;
    float ledR = 7.0f;

    g.setColour (bypassActive ? juce::Colour (0x334dff88)
                              : juce::Colour (0x22000000));
    g.fillEllipse (ledX - ledR * 2.0f, ledY - ledR * 2.0f,
                   ledR * 4.0f,        ledR * 4.0f);

    g.setColour (bypassActive ? juce::Colour (0xff4dff88)
                              : juce::Colour (0xff2a2a2a));
    g.fillEllipse (ledX - ledR, ledY - ledR, ledR * 2.0f, ledR * 2.0f);

    g.setColour (juce::Colours::white.withAlpha (bypassActive ? 0.4f : 0.1f));
    g.fillEllipse (ledX - ledR * 0.5f, ledY - ledR * 0.7f,
                   ledR * 0.6f,        ledR * 0.5f);
}

void LupexEditor::drawBrandLabel (juce::Graphics& g)
{
    g.setColour (juce::Colour (0xff333333));
    g.setFont (juce::FontOptions (22.0f).withStyle ("Bold"));
    g.drawText ("LUPEX",
                getWidth() / 2 - 60, 14, 120, 28,
                juce::Justification::centred);

    g.setColour (juce::Colour (0xffaaaaaa));
    g.setFont (juce::FontOptions (9.0f));
    g.drawText ("FAUZ AUDIO",
                getWidth() / 2 - 50, 42, 100, 14,
                juce::Justification::centred);
}

} // namespace Lupex