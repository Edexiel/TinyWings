#include "Function.hpp"
#include "Functions.hpp"

using namespace Tinywings;

void Function::Create(float x1, float x2, float y1, float y2, float precision, F_TYPE funcType, float n) noexcept
{
    type = funcType;

    SinusFunction      function;
    PolyFunction       function2;
    EllipticFunction   function3;
    HyperbolicFunction function4;

    switch (type)
    {

    case F_TYPE::E_SIN:
        pts      = function.Create(x1, x2, y1, y2, 1, precision);
        fx       = function.fx;
        sinDeriv = function.sinDeriv;
        break;

    case F_TYPE::E_POLY:
        pts      = function2.Create(x1, x2, y1, y2, precision);
        fx       = function2.fx;
        deriv1fx = function2.deriv1fx;
        deriv1fx = function2.deriv2fx;
        break;
    case F_TYPE::E_ELLI:
        pts      = function3.Create(x1, x2, y1, y2, precision);
        fx       = function3.fx;
        deriv1fx = function3.deriv1fx;
        deriv1fx = function3.deriv2fx;
        gx       = function3.gx;
        deriv1gx = function3.deriv1gx;
        deriv1gx = function3.deriv2gx;
        break;
    case F_TYPE::E_HYP:
        pts      = function4.Create(x1, x2, y1, y2, precision);
        fx       = function4.fx;
        deriv1fx = function4.deriv1fx;
        deriv1fx = function4.deriv2fx;
        break;
    }
}

void Function::Create(const Vector2& p1, const Vector2& p2, float precision, F_TYPE funcType, float n) noexcept
{
    Create(p1.x, p2.x, p1.y, p2.y, precision, funcType, n);
}