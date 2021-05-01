#include "Map.hpp"
//#include "Functions.hpp"
#include "Function.hpp"
#include "Functions.hpp"
#include "raymath.h"
#include <cmath>
#include <iostream>

using namespace Tinywings;

Zone::Zone(F_TYPE functionType, Vector2& start, bool orientation, float precision)
{
    sens = orientation;

    const int width  = GetScreenWidth();
    const int height = GetScreenHeight();

    size.x = (float)GetRandomValue(width / ZONE_MIN_WIDTH, width / ZONE_MAX_WIDTH);
    size.y = (float)GetRandomValue(height / ZONE_MIN_HEIGHT, height / ZONE_MAX_HEIGHT);

    if (sens)
        size.y *= -1;

    p1 = start;
    p2 = Vector2{p1.x + size.x, p1.y + size.y};

    switch (functionType)
    {

    case F_TYPE::E_SIN:
        function = std::make_unique<SinusFunction>(p1.x, p2.x, p1.y, p2.y, 1, 1);
        break;
    case F_TYPE::E_POLY:
        function = std::make_unique<PolyFunction>(p1.x, p2.x, p1.y, p2.y, 1);
        break;
    case F_TYPE::E_ELLI:
        function = std::make_unique<EllipticFunction>(p1.x, p2.x, p1.y, p2.y, 1);
        break;
    case F_TYPE::E_HYP:
        function = std::make_unique<HyperbolicFunction>(p1.x, p2.x, p1.y, p2.y, 1);
        break;
    }

    heightPoints = function->pts;
    //    std::cout << "Width: " << size.x << "  Precision: " << precision << "  Array size : " << heightPoints.size()
    //              << std::endl;
    //
    //    std::cout << "Start "<< p1.y << std::endl;
    //    for (const auto &heightPoint : heightPoints) {
    //        std::cout << heightPoint << std::endl;
    //    }
    //    std::cout << "Stop "<< p2.y << std::endl;
}


Map::Map(Player& player, Vector2& screenSize, float precision)
    : _player{player}, _screenSize{screenSize}, _precision{precision}
{
    _currentType = F_TYPE::E_SIN;
    _allPoints.reserve((size_t)(_screenSize.x * 5.f)); // we reserve 5x the width of the screen, because yes

    for (int i = 0; i < INIT_ZONES_NB; ++i)
    {
        AddZone();
    }
}

void Map::DrawDebug()
{
    for (const auto& i : _zones)
    {
        DrawRectangleLines((int)(i.p1.x - _offset.x), (int)(i.p1.y + _offset.y), (int)i.size.x,(int)i.size.y, i.sens ? RED : GREEN);
    }
}

void Map::CreateBuffer()
{
    _allPoints.clear();
    _buffer.clear();

    for (Zone& item : _zones)
    {
        _allPoints.insert(_allPoints.end(), item.heightPoints.begin(), item.heightPoints.end());
        if (_allPoints.size() >= (int)(_screenSize.x * 1.5f * _scale))
            break;
    }

    const float start = _offset.x - _deletedSpace;
    const float end   = _precision + _offset.x - _deletedSpace + _screenSize.x;
    const float step  = _precision; //_scale;

    // todo : lol pas propre
    for (float i = start; i < end; i += step)
    {
        _buffer.push_back(GetIPoint(i));
    }

    if (_offset.x - _deletedSpace > _zones[0].size.x)
    {
        _deletedSpace += _zones[0].size.x;
        _zones.pop_front();
        AddZone();
    }
}

void Map::AddZone()
{
    if (_zones.empty())
    {
        const float height = _screenSize.y;
        Vector2     start{0, height - (height / 3.f)};

        _zones.emplace_back(_currentType, start, (bool)GetRandomValue(0, 1), _precision);
        _zones.emplace_back(_currentType, _zones.back().p2, (bool)GetRandomValue(0, 1), _precision);
        return;
    }

    /* Orientation */
    bool orientation = (bool)GetRandomValue(0, 1);
    // Do not repeat an orientation more than twice
    unsigned long size = _zones.size();
    if ((_zones[size - 2].sens == orientation) && (_zones[size - 1].sens == orientation))
        orientation = !orientation;

    _zones.emplace_back(_currentType, _zones.back().p2, orientation, _precision);
}
void Map::Update(float DeltaTime)
{
    _offset.x += _player._speed * DeltaTime;
}

float Map::GetIPoint(float position)
{
    const int   from  = floor(position);
    const int   to    = ceil(position);
    const float fract = position - (float)from;

    return Lerp(_allPoints[from], _allPoints[to], fract);
}
