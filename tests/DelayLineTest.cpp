#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "dsp/DelayLine.h"

using namespace Catch::Matchers;

TEST_CASE ("DelayLine — prepare inicializa sin NaN", "[DelayLine]")
{
    Lupex::DelayLine dl;
    dl.prepare (44100.0, 1200.0f);

    float out = dl.read (10.0f);
    REQUIRE_FALSE (std::isnan (out));
    REQUIRE_FALSE (std::isinf (out));
    REQUIRE_THAT (out, WithinAbs (0.0f, 1e-6f));
}

TEST_CASE ("DelayLine — write y read retornan señal correcta", "[DelayLine]")
{
    Lupex::DelayLine dl;
    dl.prepare (44100.0, 1200.0f);

    for (int i = 0; i < 441; ++i)
        dl.write (i == 0 ? 1.0f : 0.0f);

    float out = dl.read (10.0f);
    REQUIRE_FALSE (std::isnan (out));
    REQUIRE_FALSE (std::isinf (out));
}

TEST_CASE ("DelayLine — reset limpia el buffer", "[DelayLine]")
{
    Lupex::DelayLine dl;
    dl.prepare (44100.0, 1200.0f);

    for (int i = 0; i < 100; ++i)
        dl.write (1.0f);

    dl.reset();

    float out = dl.read (5.0f);
    REQUIRE_THAT (out, WithinAbs (0.0f, 0.01f));
}

TEST_CASE ("DelayLine — no genera NaN con delay time extremo", "[DelayLine]")
{
    Lupex::DelayLine dl;
    dl.prepare (44100.0, 1200.0f);

    for (int i = 0; i < 1000; ++i)
        dl.write (0.5f);

    float out = dl.read (1199.0f);
    REQUIRE_FALSE (std::isnan (out));
    REQUIRE_FALSE (std::isinf (out));
}