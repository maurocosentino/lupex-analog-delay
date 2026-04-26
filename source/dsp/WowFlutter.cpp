#include "WowFlutter.h"
#include <cstdlib>

namespace Lupex
{
    void WowFlutter::prepare (double sr)
    {
        sampleRate = sr;
        reset();
    }

    void WowFlutter::reset()
    {
        wowPhase    = 0.0f;
        flutterPhase = 0.0f;
        noiseState  = 0.0f;
    }

    float WowFlutter::process()
    {
        // Avanzar fases
        wowPhase     += static_cast<float> (wowRate     / sampleRate);
        flutterPhase += static_cast<float> (flutterRate / sampleRate);

        if (wowPhase     > 1.0f) wowPhase     -= 1.0f;
        if (flutterPhase > 1.0f) flutterPhase -= 1.0f;

        // Senoidal + ruido suavizado para cada componente
        float wow     = std::sin (wowPhase     * 6.28318f) * wowDepth;
        float flutter = std::sin (flutterPhase * 6.28318f) * flutterDepth;

        // Ruido orgánico mezclado con wow
        float noise = nextNoise();
        wow += noise * wowDepth * 0.3f;

        return wow + flutter;
    }

    float WowFlutter::nextNoise()
    {
        float raw = (static_cast<float> (std::rand()) / RAND_MAX) * 2.0f - 1.0f;
        noiseState = noiseState * noiseSmooth + raw * (1.0f - noiseSmooth);
        return noiseState;
    }

    void WowFlutter::setWowDepth (float ms)     { wowDepth     = ms; }
    void WowFlutter::setFlutterDepth (float ms) { flutterDepth = ms; }
}