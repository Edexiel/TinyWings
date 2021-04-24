#pragma once
#pragma once
#include <functional>
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{

struct HyperbolicFunction
{
    inline std::vector<float> Create(float x1, float x2, float y1, float y2, float precision) noexcept;
    inline std::vector<float> Create(const Vector2& p1, const Vector2& p2, float precision) noexcept;

    std::function<float(float)> function;
    std::function<float(float)> deriv1;
    std::function<float(float)> deriv2;
};

std::vector<float> HyperbolicFunction::Create(float x1, float x2, float y1, float y2, float precision) noexcept
{
    float a     = y1 + ((y2 - y1) / 2.f);
    float b     = x1 + ((x2 - x1) / 2.f);
    float k     = (-10.f / (x2 - x1));
    float k1    = (y2 - y1) / 2.f;
    float alpha = 1.4f;

    auto expo = [&](float x) { return exp(alpha * k * (x - b)); };

    function = [&](float x) { return (a + k1 * ((1.f - expo(x)) / (1.f + expo(x)))); };

    deriv1 = [&](float x) { return (-(2 * alpha * expo(x) * k * k1) / ((1 + expo(x)) * (1 + expo(x)))); };
    deriv2 = [&](float x) {
        return (
            ((4 * alpha * alpha * k * k * k1 * expo(x) * expo(x)) / ((expo(x) + 1) * (expo(x) + 1) * (expo(x) + 1))) -
            ((2 * alpha * alpha * k * k * k1 * expo(x)) / (expo(x) + 1) * (expo(x) + 1)));
    };

    std::vector<float> table;
    float              i = 0.f;
    while (x1 + i < x2)
    {
        table.push_back(function(x1 + i));
        i += precision;
    }

    table.push_back(function(x2));

    return table;
}

std::vector<float> HyperbolicFunction::Create(const Vector2& p1, const Vector2& p2, float precision) noexcept
{
    return HyperbolicFunction::Create(p1.x, p2.x, p1.y, p2.y, precision);
}
} // namespace Tinywings
