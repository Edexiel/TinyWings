#pragma once
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

namespace Tinywings
{
struct PolyFunction
{
    inline std::vector<float> Create(float x1, float x2, float y1, float y2, float precision) noexcept;
    inline std::vector<float> Create(const Vector2& p1, const Vector2& p2, float precision) noexcept;

    std::function<float(float)> fx;
    std::function<float(float)> deriv1;
    std::function<float(float)> deriv2;
};

std::vector<float> PolyFunction::Create(float x1, float x2, float y1, float y2, float precision) noexcept
{
    Matrix A = {x1 * x1 * x1, x1 * x1, x1, 1, x2 * x2 * x2, x2 * x2, x2, 1,
                3 * x1 * x1,  2 * x1,  1,  0, 3 * x2 * x2,  2 * x2,  1,  0};

    Matrix B = {y1, 0, 0, 0, y2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Matrix tempA = MatrixInvert(A);

    Matrix X = MatrixMultiply(B, tempA);

    float a = X.m0;
    float b = X.m1;
    float c = X.m2;
    float d = X.m3;

    fx     = [&](float x) { return (a * x * x * x + b * x * x + c * x + d); };
    deriv1 = [&](float x) { return (3 * a * x * x + 2 * b * x + c); };
    deriv2 = [&](float x) { return (6 * a * x + 2 * b); };

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

std::vector<float> PolyFunction::Create(const Vector2& p1, const Vector2& p2, float precision) noexcept
{
    return PolyFunction::Create(p1.x, p2.x, p1.y, p2.y, precision);
}
} // namespace Tinywings