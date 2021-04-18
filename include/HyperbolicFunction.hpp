#pragma once
#pragma once
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{

struct HyperbolicFunction
{
    inline static std::vector<float> Create(float x1, float x2, float y1, float y2, float precision) noexcept;
    inline static std::vector<float> Create(const Vector2& p1, const Vector2& p2, float precision) noexcept;
};

std::vector<float> HyperbolicFunction::Create(float x1, float x2, float y1, float y2, float precision) noexcept
{
    float a     = y1 + ((y2 - y1) / 2.f);
    float b     = x1 + ((x2 - x1) / 2.f);
    float k     = (-10.f / (x2 - x1));
    float k1    = (y2 - y1) / 2.f;
    float alpha = 1.4f;

    auto fx = [&](float x) { return (a + k1 * ((1.f - exp(alpha * k * (x - b))) / (1.f + exp(alpha * k * (x - b))))); };

    std::vector<float> table;
    float              i = 0.f;
    while (x1 + i < x2)
    {
        table.push_back(fx(x1 + i));
        i += precision;
    }

    table.push_back(fx(x2));

    return table;
}

std::vector<float> HyperbolicFunction::Create(const Vector2& p1, const Vector2& p2, float precision) noexcept
{
    return HyperbolicFunction::Create(p1.x, p2.x, p1.y, p2.y, precision);
}
} // namespace Tinywings
