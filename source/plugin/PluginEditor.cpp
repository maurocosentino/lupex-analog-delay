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
        addAndMakeVisible (toggle);
        addAndMakeVisible (bypass);

        auto& apvts = processor.parameters.apvts;
        attachTime     = std::make_unique<SliderAttachment> (apvts, "time",     knobTime);
        attachFeedback = std::make_unique<SliderAttachment> (apvts, "feedback", knobFeedback);
        attachTone     = std::make_unique<SliderAttachment> (apvts, "tone",     knobTone);
        attachMix      = std::make_unique<SliderAttachment> (apvts, "mix",      knobMix);
        attachToggle   = std::make_unique<ButtonAttachment> (apvts, "toggle",   toggle);
        attachBypass = std::make_unique<ButtonAttachment> (apvts, "bypass", bypass);
        processor.parameters.apvts.addParameterListener ("bypass", this);
    }

    LupexEditor::~LupexEditor()
    {
        processor.parameters.apvts.removeParameterListener ("bypass", this);
        setLookAndFeel (nullptr);
    }

    void LupexEditor::paint (juce::Graphics& g)
    {
        drawPedalBody (g);
        // drawBrandLabel (g); //Titulos
        bool bypassed = processor.parameters.getBypass();
        bool ledOn    = !bypassed;

        const int fsSize   = 92;
        const int fsOffset = 10;
        const int fsX      = getWidth() / 2 - fsSize / 2 + fsOffset;
        const int fsY      = getHeight() - 30 - fsSize;

        const int ledSize  = 12;
        const int ledX = fsX + fsSize + 8 - 20;
        const int ledY = fsY + fsSize / 2 - ledSize / 2 - 8;

        // Glow
        g.setColour (ledOn ? juce::Colour (0x55d0f4ff)
                   : juce::Colour (0x00000000));
        g.fillEllipse (ledX - ledSize * 0.5f, ledY - ledSize * 0.5f,
                       ledSize * 2.0f,        ledSize * 2.0f);

        // Núcleo
        g.setColour (ledOn ? juce::Colour (0xffe8f8ff)
                    : juce::Colour (0xff1a1a1a));
        g.fillEllipse ((float)ledX, (float)ledY,
                       (float)ledSize, (float)ledSize);

        // Reflejo — siempre visible
        g.setColour (juce::Colours::white.withAlpha (ledOn ? 0.4f : 0.15f));
        g.fillEllipse (ledX + ledSize * 0.2f, ledY + ledSize * 0.15f,
                       ledSize * 0.35f,       ledSize * 0.25f);
    }

    void LupexEditor::resized()
    {
        const int knobS   = 90;
        const int padding = 10;
        const int topY    = 15;

        const int totalRow = 3 * knobS + 2 * padding;
        const int startX   = (getWidth() - totalRow) / 2;

        // ── Fila 1: TIME, FEEDBACK, TONE ──────────────────────
        knobTime    .setBounds (startX + 15,                    topY, knobS, knobS + 14);
        knobFeedback.setBounds (startX + knobS + padding,       topY, knobS, knobS + 14);  // sin cambio
        knobTone    .setBounds (startX + 2*(knobS+padding) - 12,topY, knobS, knobS + 14);

        // ── Fila 2: TOGGLE (bajo TIME) y MIX (bajo TONE) ──────
        const int row2Y    = topY + knobS + 14 + 12;
        const int toggleSz = 48;

        toggle.setBounds (startX + 34,
                  row2Y  + 25,
                  toggleSz, toggleSz);
        knobMix.setBounds (startX + 2*(knobS+padding) - 12, row2Y, knobS, knobS + 14);

        // ── Bypass centrado abajo ──────────────────────────────
        const int fsSize = 92;
        bypass.setBounds (getWidth() / 2 - fsSize / 2 + 10,
                          getHeight() - 30 - fsSize,
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

    void LupexEditor::parameterChanged (const juce::String&, float)
    {
        // Este callback llega desde el audio thread → hay que redibujar en el mensaje thread
        juce::MessageManager::callAsync ([this] { repaint(); });
    }

} // namespace Lupex