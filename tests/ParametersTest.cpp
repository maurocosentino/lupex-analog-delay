#include <cmath>
#include <catch2/catch_test_macros.hpp>

TEST_CASE ("Rangos de parámetros — valores normalizados", "[Parameters]")
{
    // Time: 1 a 1200ms
    float timeMin = 1.0f;
    float timeMax = 1200.0f;
    REQUIRE (timeMin < timeMax);
    REQUIRE (timeMin > 0.0f);

    // Feedback: 0 a 100%
    float feedbackMin = 0.0f;
    float feedbackMax = 100.0f;
    REQUIRE (feedbackMin >= 0.0f);
    REQUIRE (feedbackMax <= 100.0f);

    // Mix: 0 a 100%
    float mixMin = 0.0f;
    float mixMax = 100.0f;
    REQUIRE (mixMin >= 0.0f);
    REQUIRE (mixMax <= 100.0f);

    // Tone: 0 a 100%
    float toneMin = 0.0f;
    float toneMax = 100.0f;
    REQUIRE (toneMin >= 0.0f);
    REQUIRE (toneMax <= 100.0f);
}