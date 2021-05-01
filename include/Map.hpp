#ifndef TINYWINGS_MAP_HPP
#define TINYWINGS_MAP_HPP

#include "Player.hpp"
#include "common.hpp"
#include "raylib.h"
#include <deque>
#include <vector>

#define MAX_ZONES 100
#define NB_POINTS 512
#define INIT_ZONES_NB 25
#define ZONE_MIN_WIDTH 15  // in fraction of the screen , 10 -> 1/10 width
#define ZONE_MAX_WIDTH 5   // in fraction of the screen , 10 -> 1/10 width
#define ZONE_MIN_HEIGHT 15 // in fraction of the screen , 10 -> 1/10 height
#define ZONE_MAX_HEIGHT 10 // in fraction of the screen , 10 -> 1/10 height

namespace Tinywings
{
enum class F_TYPE
{
    E_SIN=0,
    E_POLY,
    E_ELLI,
    E_HYP,
};

struct Zone
{
    Vector2                   p1;
    Vector2                   p2;
    Vector2                   size;
    std::vector<float>        heightPoints;
    std::vector<Vector2>      points;
    std::unique_ptr<Function> function = nullptr;

    bool sens; // true : RED ascendant //false : GREEN Descendant

    Zone(F_TYPE, Vector2& start, bool orientation, float precision);
};

class Map
{
public:
    std::deque<Zone> _zones;
    float            _scale{1.f};
    float            _deletedSpace{0.f};
    Player&          _player;
    Vector2          _offset{0, 0};
    Vector2&         _screenSize;
    float            _precision{10.f};
    F_TYPE           _currentType;

    std::vector<float> _allPoints;
    std::vector<float> _buffer;

    Map(Player& player, Vector2& screenSize, float precision);

    void DrawDebug();

    void CreateBuffer();

    void Update(float DeltaTime);

    float GetIPoint(float position);

    void AddZone();
};

} // namespace Tinywings

#endif // TINYWINGS_MAP_HPP
