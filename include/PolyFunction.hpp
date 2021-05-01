#pragma once
#include "Function.hpp"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

namespace Tinywings
{
class PolyFunction : public Function
{
public:
    PolyFunction(float x1, float x2, float y1, float y2, float precision);
    virtual ~PolyFunction() = default;

    float a;
    float b;
    float c;
    float d;

    float image(float x) final
    {
        return (a * x * x * x + b * x * x + c * x + d);
    }

    float deriv1(float x) final
    {
        return (3 * a * x * x + 2 * b * x + c);
    }

    float deriv2(float x) final
    {
        return (6 * a * x + 2 * b);
    }
};

PolyFunction::PolyFunction(float x1, float x2, float y1, float y2, float precision) : Function(y1, y2)
{
    Matrix A = {x1 * x1 * x1, x1 * x1, x1, 1, x2 * x2 * x2, x2 * x2, x2, 1,
                3 * x1 * x1,  2 * x1,  1,  0, 3 * x2 * x2,  2 * x2,  1,  0};

    Matrix B = {y1, 0, 0, 0, y2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Matrix tempA = MatrixInvert(A);

    Matrix X = MatrixMultiply(B, tempA);

    a = X.m0;
    b = X.m1;
    c = X.m2;
    d = X.m3;

    float i = 0;
    while (i + x1 < x2)
    {
        pts.push_back(image(x1 + i));
        i += precision;
    }

    pts.push_back(image(x2));
}
} // namespace Tinywings