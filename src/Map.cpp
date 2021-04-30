#include "Map.hpp"
#include "Function.hpp"
//#include "Functions.hpp"
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

    Function function;

    switch (functionType)
    {

    case F_TYPE::E_SIN:
        function.Create(p1, p2, precision, functionType, 1);
        heightPoints = function.pts;
        break;
    case F_TYPE::E_POLY:
        function.Create(p1, p2, precision, functionType);
        heightPoints = function.pts;
        break;
    case F_TYPE::E_ELLI:
        function.Create(p1, p2, precision, functionType);
        heightPoints = function.pts;
        break;
    case F_TYPE::E_HYP:
        function.Create(p1, p2, precision, functionType);
        heightPoints = function.pts;
        break;
    }

    for (int i = 0; i < heightPoints.size(); ++i)
    {

        points.emplace_back(Vector2{p1.x + (float)i * precision, p1.y + heightPoints[i]});
    }

    auto nbpoints = (float)points.size();
    for (Vector2& point : points)
    {
        point.x = point.x / nbpoints;
        point.y = point.y / size.y;
    }
}

void Zone::DrawZone() const
{

    DrawRectangleLines((int)p1.x, (int)p1.y, (int)(p2.x - p1.x), (int)(p2.y - p1.y), sens ? RED : GREEN);

    //    for (int i = 0; i < heightPoints.size()-1; ++i)
    //    {
    //        DrawLine(p1.x + i, heightPoints[i], p1.x + (i + 1.f), heightPoints[i + 1.f], BLACK);
    //    }
}

Map::Map(float precision, Camera2D* camera) : _precision{precision}, _camera2D{camera}
{
    _currentType = F_TYPE::E_SIN;
    _allPoints.reserve(NB_POINTS);

    for (int i = 0; i < INIT_ZONES_NB; ++i)
    {
        AddZone();
    }
}

void Map::DrawDebug()
{
    for (const auto& item : _zones)
    {
        item.DrawZone();
    }
}

void Map::CreateBuffer()
{
    _allPoints.clear();

    for (int i = 0; i < NB_POINTS; ++i)
    {
        //_allPoints.emplace_back(GetValue(i));
    }

    for (Zone& item : _zones)
    {
        _allPoints.insert(_allPoints.end(), item.heightPoints.begin(), item.heightPoints.end());
        if (_allPoints.size() >= NB_POINTS)
            return;
    }
}

float Map::GetValue(int x)
{
    _camera2D->zoom;
    _precision;
    offset;
    return 0;
}

void Map::AddZone()
{
    if (_zones.empty())
    {
        const int height = GetScreenHeight();
        Vector2   start{0, (float)(height - ((float)height / 3.f))};

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
