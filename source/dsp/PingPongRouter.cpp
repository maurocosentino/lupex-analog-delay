#include "PingPongRouter.h"

namespace Lupex
{

    PingPongRouter::PingPongRouter() = default;

    void PingPongRouter::prepare (double sampleRate, float maxDelayMs)
    {
        delayL.prepare (sampleRate, maxDelayMs);
        delayR.prepare (sampleRate, maxDelayMs);
        filterL.prepare (sampleRate);
        filterR.prepare (sampleRate);
    }

    void PingPongRouter::reset()
    {
        delayL.reset();
        delayR.reset();
        filterL.reset();
        filterR.reset();
        tapeL.reset();
        tapeR.reset();
    }

    void PingPongRouter::process (float  inputL,  float  inputR,
                                   float& outputL, float& outputR,
                                   float  delayMs, float  feedback,
                                   float  tone,    float  drive,
                                   bool   filterOn)
    {
        // Leer los repetidos actuales de cada canal
        float delayedL = delayL.process (0.0f, delayMs);
        float delayedR = delayR.process (0.0f, delayMs);

        // Aplicar saturación de cinta al feedback
        tapeL.setDrive (drive);
        tapeR.setDrive (drive);
        float saturatedL = tapeL.process (delayedL * feedback);
        float saturatedR = tapeR.process (delayedR * feedback);

        // Aplicar filtro BBD si está activo
        if (filterOn)
        {
            filterL.setTone (tone);
            filterR.setTone (tone);
            saturatedL = filterL.process (saturatedL);
            saturatedR = filterR.process (saturatedR);
        }

        // El ping-pong cruza los canales en el feedback
        // L alimenta a R y R alimenta a L — así rebotan
        delayL.process (inputL + saturatedR, delayMs);
        delayR.process (inputR + saturatedL, delayMs);

        outputL = delayedL;
        outputR = delayedR;
    }

} // namespace Lupex