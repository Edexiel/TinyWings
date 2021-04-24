#pragma once
#include <functional>
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{

struct EllipticFunction
{
    inline std::vector<float> Create(float x1, float x2, float y1, float y2, float precision) noexcept;
    inline std::vector<float> Create(const Vector2& p1, const Vector2& p2, float precision) noexcept;

    std::function<float(float)> fx;
    std::function<float(float)> deriv1fx;
    std::function<float(float)> deriv2fx;
    std::function<float(float)> gx;
    std::function<float(float)> deriv1gx;
    std::function<float(float)> deriv2gx;
};

std::vector<float> EllipticFunction::Create(float x1, float x2, float y1, float y2, float precision) noexcept
{
    float a  = (y2 + y1) / 2;
    float k  = 2 / (x2 - x1);
    float k1 = (y1 - y2) / 2;
    float k2 = (y2 - y1) / 2;

    fx       = [&](float x) { return (a + k1 * sqrtf(1 - ((k * (x - x1)) * (k * (x - x1))))); };
    deriv1fx = [&](float x) { return (-(k * k * k1 * (x - x1)) / sqrtf(1 - k * k * (x - x1) * (x - x1))); };
    deriv2fx = [&](float x) {
        return (-(k * k * k1) / sqrt(1 - k * k * (x - x1) * (x - x1)) -
                (powf(k, 4) * k1 * (x - x1) * (x - x1)) / powf((1 - k * k * (x - x1) * (x - x1)), (3 / 2)));
    };

    gx       = [&](float x) { return (a + k2 * sqrtf(1 - ((k * (x - x2)) * (k * (x - x2))))); };
    deriv1gx = [&](float x) { return (-(k * k * k2 * (x - x2)) / sqrt(1 - k * k * (x - x2) * (x - x2))); };
    deriv2gx = [&](float x) {
        return (-(k * k * k2) / sqrt(1 - k * k * (x - x2) * (x - x2)) -
                (powf(k, 4) * k2 * (x - x2) * (x - x2)) / powf((1 - k * k * (x - x2) * (x - x2)), (3 / 2)));
    };

    std::vector<float> table;
    float              i = 0;
    while (x1 + i < x2)
    {
        if ((x1 + i) <= (x2 - ((x2 - x1) / 2)))
        {
            table.push_back(fx(x1 + i));
        }
        else
        {
            table.push_back(gx(x1 + i));
        }

        i += precision;
    }

    table.push_back(gx(x2));

    return table;
}

std::vector<float> EllipticFunction::Create(const Vector2& p1, const Vector2& p2, float precision) noexcept
{
    return EllipticFunction::Create(p1.x, p2.x, p1.y, p2.y, precision);
}
} // namespace Tinywings
