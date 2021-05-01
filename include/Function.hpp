#ifndef TINYWINGS_FUNCTION_HPP
#define TINYWINGS_FUNCTION_HPP

#include <functional>
#include <vector>

namespace Tinywings
{

class Function
{
public:
    Function(float y1, float y2) noexcept;
    virtual ~Function()           = default;
    virtual float image(float x)  = 0;
    virtual float deriv1(float x) = 0;
    virtual float deriv2(float x) = 0;

    std::vector<float> pts;
    bool               isAscending;
};
} // namespace Tinywings

#endif // TINYWINGS_FUNCTION_HPP