#pragma once
#pragma once
#include "Function.hpp"
#include <functional>
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{

class HyperbolicFunction : public Function
{
public:
    HyperbolicFunction(float x1, float x2, float y1, float y2, float precision);
    virtual ~HyperbolicFunction() = default;

    float a;
    float b;
    float k;
    float k1;
    float alpha;

    float expo(float x)
    {
        return exp(alpha * k * (x - b));
    }

    float image(float x) final
    {
        return (a + k1 * ((1.f - expo(x)) / (1.f + expo(x))));
    }

    float deriv1(float x) final
    {
        return (-(2 * alpha * expo(x) * k * k1) / ((1 + expo(x)) * (1 + expo(x))));
    }

    float deriv2(float x) final
    {
        return (
            ((4 * alpha * alpha * k * k * k1 * expo(x) * expo(x)) / ((expo(x) + 1) * (expo(x) + 1) * (expo(x) + 1))) -
            ((2 * alpha * alpha * k * k * k1 * expo(x)) / (expo(x) + 1) * (expo(x) + 1)));
    }
};

HyperbolicFunction::HyperbolicFunction(float x1, float x2, float y1, float y2, float precision) : Function(y1, y2)
{
    a     = y1 + ((y2 - y1) / 2.f);
    b     = x1 + ((x2 - x1) / 2.f);
    k     = (-10.f / (x2 - x1));
    k1    = (y2 - y1) / 2.f;
    alpha = 1.4f;

    float i = 0.f;
    while (x1 + i < x2)
    {
        pts.push_back(image(x1 + i));
        i += precision;
    }

    pts.push_back(image(x2));
}
} // namespace Tinywings
