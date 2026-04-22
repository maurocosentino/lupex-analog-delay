#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterIDs.h"

namespace Lupex
{

    class LupexParameters
    {
    public:
        explicit LupexParameters (juce::AudioProcessor& processor);

        // Referencia al APVTS — lo usan el Processor y el Editor
        juce::AudioProcessorValueTreeState apvts;

        // Getters — devuelven el valor actual de cada parámetro
        float getTime()        const;
        float getFeedback()    const;
        float getMix()         const;
        float getTone()        const;
        bool  getPingPong()    const;
        bool  getTempoSync()   const;
        bool  getFilter()      const;

    private:
        // Crea todos los parámetros con sus rangos y valores default
        static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    };

} // namespace Lupex