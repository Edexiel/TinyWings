#pragma once
#include "Function.hpp"
#include <cmath>
#include <functional>
#include <math.h>
#include <raylib.h>
#include <vector>

namespace Tinywings
{

class EllipticFunction : public Function
{
public:
    EllipticFunction(float x1, float x2, float y1, float y2, float precision);
    virtual ~EllipticFunction() = default;

    float x1;
    float x2;
    float y1;
    float y2;
    float k;
    float k1;

    float image(float x) final
    {
        if (x <= (x2 - ((x2 - x1) / 2)))
        {
            return (y2 - k1 * sqrtf(1 - ((k * (x - x1)) * (k * (x - x1)))));
        }

        else
        {
            return (y1 + k1 * sqrtf(1 - ((k * (x - x2)) * (k * (x - x2)))));
        }
    }

    float deriv1(float x) final
    {
        if (x <= (x2 - ((x2 - x1) / 2)))
        {
            return ((k * k * k1 * (x - x1)) / sqrtf(1 - k * k * (x - x1) * (x - x1)));
        }

        else
        {
            return ((k * k * k1 * (x - x2)) / sqrt(1 - k * k * (x - x2) * (x - x2)));
        }
    }

    float deriv2(float x) final
    {
        if (x <= (x2 - ((x2 - x1) / 2)))
        {
            return ((k * k * k1) / sqrt(1 - k * k * (x - x1) * (x - x1)) -
                    (powf(k, 4) * k1 * (x - x1) * (x - x1)) / powf((1 - k * k * (x - x1) * (x - x1)), (3 / 2)));
        }

        else
        {
            return ((k * k * k1) / sqrt(1 - k * k * (x - x2) * (x - x2)) -
                    (powf(k, 4) * k1 * (x - x2) * (x - x2)) / powf((1 - k * k * (x - x2) * (x - x2)), (3 / 2)));
        }
    }
};

EllipticFunction::EllipticFunction(float x1, float x2, float y1, float y2, float precision) : Function(y1, y2)
{
    float s  = 1 - ((y2 - y1) / (2 * (y2 - y1))) * ((y2 - y1) / (2 * (y2 - y1)));
    float t  = (x1 - x2) / 2;
    float k  = sqrtf(s) / t;
    float k1 = y2 - y1;

    float i = 0;
    while (x1 + i < x2)
    {
        if ((x1 + i) <= (x2 - ((x2 - x1) / 2)))
        {
            pts.push_back(image(x1 + i));
        }
        else
        {
            pts.push_back(image(x1 + i));
        }

        i += precision;
    }

    pts.push_back(image(x2));
}
} // namespace Tinywings
