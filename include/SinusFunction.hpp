#pragma once
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{
struct SinusFunction
{
    inline std::vector<float> Create(float x1, float x2, float y1, float y2, unsigned int n, float precision) noexcept;
    inline std::vector<float> Create(const Vector2& p1, const Vector2& p2, unsigned int n, float precision) noexcept;

    std::function<float(float)>        fx;
    std::function<float(float, float)> deriv;
};

std::vector<float> SinusFunction::Create(float x1, float x2, float y1, float y2, unsigned int n,
                                         float precision) noexcept
{
    float pulsation;
    float amplitude;
    float offset;

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

    float phase = (PI / 2) - pulsation * x2;

    fx = [&](float x) { return (offset + amplitude * (powf(sinf(pulsation * x + phase), n))); };

    deriv = [&](float x, float n1) { return (offset + amplitude * (powf(sinf(pulsation * x + phase + PI / 2), n1))); };

    std::vector<float> table;
    float              i = 0;
    while (i + x1 < x2)
    {
        table.push_back(fx(x1 + i));
        i += precision;
    }

    table.push_back(fx(x2));

    return table;
}

std::vector<float> SinusFunction::Create(const Vector2& p1, const Vector2& p2, unsigned int n, float precision) noexcept
{
    return SinusFunction::Create(p1.x, p2.x, p1.y, p2.y, n, precision);
}
} // namespace Tinywings