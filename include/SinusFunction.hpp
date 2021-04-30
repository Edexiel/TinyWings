#pragma once
#include "Function.hpp"
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{
class SinusFunction : public Function
{
public:
    SinusFunction(float x1, float x2, float y1, float y2, unsigned int _n, float precision);
    virtual ~SinusFunction() = default;

    float        pulsation;
    float        amplitude;
    float        offset;
    unsigned int n;
    float        phase;

    float image(float x) final
    {
        return (offset + amplitude * (powf(sinf(pulsation * x + phase), n)));
    }

    float deriv1(float x) final
    {
        return (amplitude * (powf(sinf(pulsation * x + phase + PI / 2), n + 1)));
    }

    float deriv2(float x) final
    {
        return (amplitude * (powf(sinf(pulsation * x + phase + PI / 2), n + 2)));
    }

    /*sinDeriv = [&](float x, float n1) {
        return (amplitude * (powf(sinf(pulsation * x + phase + PI / 2), n1)));
    };*/
};

SinusFunction::SinusFunction(float x1, float x2, float y1, float y2, unsigned int _n, float precision)
    : Function(y1, y2)
{
    n                   = _n;
    float tempPulsation = PI / (x2 - x1);
    float tempOffset    = (y1 + y2) / 2;
    float tempAmplitude = tempOffset - y1;
    bool  isNOdd        = n % 2;

    if (!isNOdd)
    {
        pulsation = tempPulsation / 2;
        amplitude = tempAmplitude * 2;
        offset    = tempOffset - tempAmplitude;
    }

    else
    {
        pulsation = tempPulsation;
        amplitude = tempAmplitude;
        offset    = tempOffset;
    }

    phase = (PI / 2) - pulsation * x2;

    float i = 0;
    while (i + x1 < x2)
    {
        pts.push_back(image(x1 + i));
        i += precision;
    }

    pts.push_back(image(x2));
}
} // namespace Tinywings