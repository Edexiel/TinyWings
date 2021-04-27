//
// Created by g.nisi on 07/04/2021.
//

#ifndef TINYWINGS_MAP_HPP
#define TINYWINGS_MAP_HPP

#include "common.hpp"
#include "raylib.h"
#include <deque>
#include <vector>

#define MAX_ZONES 100
#define INIT_ZONES_NB 100
#define ZONE_MIN_WIDTH 15  // in fraction of the screen , 10 -> 1/10 width
#define ZONE_MAX_WIDTH 5   // in fraction of the screen , 10 -> 1/10 width
#define ZONE_MIN_HEIGHT 15 // in fraction of the screen , 10 -> 1/10 height
#define ZONE_MAX_HEIGHT 10 // in fraction of the screen , 10 -> 1/10 height

namespace Tinywings
{
enum class F_TYPE
{
    E_SIN,
    E_POLY,
    E_ELLI,
    E_HYP,
};

struct Zone
{
    std::vector<float> heightPoints;

    F_TYPE  type;
    bool    sens; // true: ascent; false: descent
    Vector2 p1;
    Vector2 p2;

    Zone(F_TYPE, Vector2& start, bool orientation, float precision);
    Rectangle GetRectangle() const;
    void      Draw();
    void      DrawZone() const;
};

class Map
{
private:
    std::deque<Zone> _zones;
    F_TYPE           _currentType;
    float            _precision;

public:
    std::vector<float> _allPoints;

    Map(float precision);

    void   Update();
    void   DrawDebug();
    void   CreateBuffer();
    void   AddZone();
    F_TYPE GetCurrentType();
    void   SetCurrentType(F_TYPE currentType);
};

} // namespace Tinywings

#endif // TINYWINGS_MAP_HPP
