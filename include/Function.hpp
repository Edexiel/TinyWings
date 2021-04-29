#ifndef TINYWINGS_FUNCTION_HPP
#define TINYWINGS_FUNCTION_HPP

#include "Map.hpp"
#include <functional>
#include <vector>

namespace Tinywings
{
class Function
{
public:
    void Create(float x1, float x2, float y1, float y2, float precision, F_TYPE funcType, float n = 1) noexcept;
    void Create(const Vector2& p1, const Vector2& p2, float precision, F_TYPE funcType, float n = 1) noexcept;

    std::vector<float> pts;
    F_TYPE             type;

    std::function<float(float)>        fx       = nullptr;
    std::function<float(float)>        deriv1fx = nullptr;
    std::function<float(float)>        deriv2fx = nullptr;
    std::function<float(float)>        gx       = nullptr;
    std::function<float(float)>        deriv1gx = nullptr;
    std::function<float(float)>        deriv2gx = nullptr;
    std::function<float(float, float)> sinDeriv = nullptr;
};
} // namespace Tinywings

#endif // TINYWINGS_FUNCTION_HPP