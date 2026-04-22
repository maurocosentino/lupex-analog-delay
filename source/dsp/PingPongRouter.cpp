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
        lastFeedbackL = 0.0f;
        lastFeedbackR = 0.0f;
    }

    void PingPongRouter::process (float  inputL,  float  inputR,
                                   float& outputL, float& outputR,
                                   float  delayMs, float  feedback,
                                   float  tone,    float  drive,
                                   bool   filterOn)
    {
        // Configurar tone y drive antes de procesar
        tapeL.setDrive (drive);
        tapeR.setDrive (drive);

        if (filterOn)
        {
            filterL.setTone (tone);
            filterR.setTone (tone);
        }

        // Leer el estado actual del feedback de cada canal
        float feedbackL = lastFeedbackL * feedback;
        float feedbackR = lastFeedbackR * feedback;

        // Aplicar saturación de cinta al feedback
        feedbackL = tapeL.process (feedbackL);
        feedbackR = tapeR.process (feedbackR);

        // Aplicar filtro BBD al feedback si está activo
        if (filterOn)
        {
            feedbackL = filterL.process (feedbackL);
            feedbackR = filterR.process (feedbackR);
        }

        // Ping-pong: L recibe input + feedback de R, y viceversa
        float writeL = inputL + feedbackR;
        float writeR = inputR + feedbackL;

        // Procesar los delay lines
        outputL = delayL.process (writeL, delayMs);
        outputR = delayR.process (writeR, delayMs);

        // Guardar el output para el próximo ciclo de feedback
        lastFeedbackL = outputL;
        lastFeedbackR = outputR;
    }

} // namespace Lupex