#pragma once
#include <cmath>

namespace Lupex
{
    class WowFlutter
    {
    public:
        void prepare (double sampleRate);
        void reset();
        float process();  // retorna offset en ms

        void setWowDepth     (float ms);   // 0.0–0.5ms
        void setFlutterDepth (float ms);   //  0.0–0.15ms

    private:
        float nextNoise();  // ruido suavizado

        double sampleRate { 44100.0 };

        // Wow
        float wowPhase    { 0.0f };
        float wowDepth    { 0.3f };
        static constexpr float wowRate { 0.8f };  // Hz

        // Flutter
        float flutterPhase { 0.0f };
        float flutterDepth { 0.08f };
        static constexpr float flutterRate { 12.0f };  // Hz

        // Ruido suavizado
        float noiseState  { 0.0f };
        static constexpr float noiseSmooth { 0.998f };
    };
}