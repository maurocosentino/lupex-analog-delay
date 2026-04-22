#include "LupexParameters.h"

namespace Lupex
{

// ── Constructor ────────────────────────────────────────────────────────────
LupexParameters::LupexParameters (juce::AudioProcessor& processor)
    : apvts (processor, nullptr, "LupexState", createLayout())
{
}

// ── Layout ─────────────────────────────────────────────────────────────────
juce::AudioProcessorValueTreeState::ParameterLayout LupexParameters::createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Time — 1ms a 1200ms, default 300ms
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParameterIDs::TIME, 1 },
        "Time",
        juce::NormalisableRange<float> (1.0f, 1200.0f, 1.0f),
        300.0f));

    // Feedback — 0% a 95%, default 40%
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParameterIDs::FEEDBACK, 1 },
        "Feedback",
        juce::NormalisableRange<float> (0.0f, 95.0f, 0.1f),
        40.0f));

    // Mix — 0% a 100%, default 30%
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParameterIDs::MIX, 1 },
        "Mix",
        juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f),
        30.0f));

    // Tone — 0% a 100%, default 70%
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParameterIDs::TONE, 1 },
        "Tone",
        juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f),
        70.0f));

    // Ping Pong — toggle, default off
    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { ParameterIDs::PING_PONG, 1 },
        "Ping Pong",
        false));

    // Tempo Sync — toggle, default off
    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { ParameterIDs::TEMPO_SYNC, 1 },
        "Tempo Sync",
        false));

    // Filter — toggle, default off
    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { ParameterIDs::FILTER, 1 },
        "Filter",
        false));

    return { params.begin(), params.end() };
}

// ── Getters ────────────────────────────────────────────────────────────────
float LupexParameters::getTime() const
{
    return apvts.getRawParameterValue (ParameterIDs::TIME)->load();
}

float LupexParameters::getFeedback() const
{
    return apvts.getRawParameterValue (ParameterIDs::FEEDBACK)->load() / 100.0f;
}

float LupexParameters::getMix() const
{
    return apvts.getRawParameterValue (ParameterIDs::MIX)->load() / 100.0f;
}

float LupexParameters::getTone() const
{
    return apvts.getRawParameterValue (ParameterIDs::TONE)->load() / 100.0f;
}

bool LupexParameters::getPingPong() const
{
    return apvts.getRawParameterValue (ParameterIDs::PING_PONG)->load() > 0.5f;
}

bool LupexParameters::getTempoSync() const
{
    return apvts.getRawParameterValue (ParameterIDs::TEMPO_SYNC)->load() > 0.5f;
}

bool LupexParameters::getFilter() const
{
    return apvts.getRawParameterValue (ParameterIDs::FILTER)->load() > 0.5f;
}

} // namespace Lupex