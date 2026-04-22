#include "TapeEmulator.h"
#include <cmath>

namespace Lupex
{

    TapeEmulator::TapeEmulator() = default;

    void TapeEmulator::reset() {}

    void TapeEmulator::setDrive (float d)
    {
        drive = d;
    }

    float TapeEmulator::process (float input)
    {
        float amplified = input * (1.0f + drive * 3.0f);

        // Curva de Langevin simplificada — modela magnetización de cinta
        float saturated = amplified / (std::abs (amplified) + 1.0f);

        // El 0.1f * drive agrega un toque de armónicos extra a mayor drive
        return saturated * (1.0f + 0.1f * drive);
    }

} // namespace Lupex