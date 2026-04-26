#include "BBDFilter.h"
#include <cmath>

namespace Lupex
{

    BBDFilter::BBDFilter() = default;

    void BBDFilter::prepare (double sr)
    {
        sampleRate = sr;
        reset();
    }

    void BBDFilter::reset()
    {
        lastOutput = 0.0f;
    }

    void BBDFilter::setTone (float tone)
    {
        coefficient = calculateCoefficient (tone);
    }

    float BBDFilter::process (float input)
    {
        // Filtro low-pass de un polo — el corazón del carácter BBD
        lastOutput = lastOutput + coefficient * (input - lastOutput);
        return lastOutput;
    }

    float BBDFilter::calculateCoefficient (float tone) const
    {
        // Mapeamos tone (0.0–1.0) a frecuencia de corte (800Hz–8000Hz)
        // A menor tone → menor frecuencia → más oscuro
        float cutoffHz = 1200.0f + tone * 7200.0f;
        // Fórmula estándar para coeficiente de filtro RC digital
        float rc = 1.0f / (2.0f * 3.14159265f * cutoffHz);
        float dt = 1.0f / static_cast<float> (sampleRate);

        return dt / (rc + dt);
    }

} // namespace Lupex