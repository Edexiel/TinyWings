//
// Created by g.nisi on 05/04/2021.
//

#ifndef TINYWINGS_RECTANGLE_HPP
#define TINYWINGS_RECTANGLE_HPP

#include "raylib.h"

namespace Tinywings
{
    enum class F_TYPE
    {
        E_SIN,
        E_POLY,
        E_ARC,
        E_HYP,

    };

    struct Rectangle
    {
        Vector2 p1;
        Vector2 p2;
    };
}



#endif //TINYWINGS_RECTANGLE_HPP
