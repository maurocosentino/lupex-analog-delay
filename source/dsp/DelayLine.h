#pragma once

#include <vector>
#include <cstddef>

namespace Lupex
{

    class DelayLine
    {
    public:
        DelayLine();

        // Llama antes de procesar audio — reserva el buffer
        void prepare (double sampleRate, float maxDelayMs);

        // Limpia el buffer — útil cuando el plugin se pausa
        void reset();

        // Escribe una muestra y lee el delay en un solo paso
        float process (float inputSample, float delayMs);

        // Setea el tamaño actual del delay en muestras
        void setDelayMs (float delayMs);

    private:
        // Convierte ms a cantidad de muestras
        float msToSamples (float ms) const;

        // Lee con interpolación lineal entre dos muestras
        float readInterpolated (float delaySamples) const;

        std::vector<float> buffer;
        int writeIndex { 0 };
        double sampleRate { 44100.0 };
        float maxDelayMs { 1200.0f };
    };

} // namespace Lupex