#include "Function.hpp"

using namespace Tinywings;

Function::Function(float y1, float y2) noexcept
{
    if (y1 <= y2)
    {
        isAscending = true;
    }

    else
    {
        isAscending = false;
    }
}