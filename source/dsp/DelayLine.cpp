#include "DelayLine.h"
#include <cmath>
#include <algorithm>

namespace Lupex
{

DelayLine::DelayLine() = default;

// ── Prepare ────────────────────────────────────────────────────────────────
void DelayLine::prepare (double sr, float maxMs)
{
    sampleRate  = sr;
    maxDelayMs  = maxMs;

    // Calculamos cuántas muestras necesitamos para el delay máximo
    // Ej: 44100 Hz * 1.2 segundos = 52920 muestras
    int maxSamples = static_cast<int> (msToSamples (maxMs)) + 2;
    buffer.assign (maxSamples, 0.0f);
    writeIndex = 0;
}

// ── Reset ──────────────────────────────────────────────────────────────────
void DelayLine::reset()
{
    std::fill (buffer.begin(), buffer.end(), 0.0f);
    writeIndex = 0;
}

// ── Process ────────────────────────────────────────────────────────────────
float DelayLine::process (float inputSample, float delayMs)
{
    // 1. Leer el sample retrasado ANTES de escribir
    float delaySamples = msToSamples (delayMs);
    float delayedSample = readInterpolated (delaySamples);

    // 2. Escribir el input en la posición actual
    buffer[writeIndex] = inputSample;

    // 3. Avanzar el writeIndex — si llega al final, vuelve al principio
    writeIndex = (writeIndex + 1) % static_cast<int> (buffer.size());

    return delayedSample;
}

// ── Helpers ────────────────────────────────────────────────────────────────
float DelayLine::msToSamples (float ms) const
{
    return static_cast<float> (sampleRate) * ms / 1000.0f;
}

float DelayLine::readInterpolated (float delaySamples) const
{
    int bufferSize = static_cast<int> (buffer.size());

    // Calcular el índice de lectura retrocediendo desde writeIndex
    float readPos = static_cast<float> (writeIndex) - delaySamples;

    // Mantener el índice dentro del buffer (wrap around)
    while (readPos < 0.0f)
        readPos += static_cast<float> (bufferSize);

    // Separar la parte entera de la decimal
    // Ej: readPos = 42.7 → index0 = 42, index1 = 43, fraction = 0.7
    int   index0   = static_cast<int> (readPos) % bufferSize;
    int   index1   = (index0 + 1) % bufferSize;
    float fraction = readPos - std::floor (readPos);

    // Interpolación lineal: mezcla entre las dos muestras según fraction
    // fraction = 0.0 → 100% index0
    // fraction = 1.0 → 100% index1
    return buffer[index0] + fraction * (buffer[index1] - buffer[index0]);
}

void DelayLine::setDelayMs (float delayMs)
{
    // El clamp asegura que nunca pedimos más delay del que el buffer soporta
    delayMs = std::clamp (delayMs, 1.0f, maxDelayMs);
}

} // namespace Lupex