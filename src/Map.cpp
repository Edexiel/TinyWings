//
// Created by g.nisi on 07/04/2021.
//

#include "Map.hpp"

/*____________________ZONE______________________________*/

Zone::Zone(F_TYPE functionType, Vector2 &start, bool orientation)
{
    sens = orientation;

    p1 = start;
    type = functionType;
    const int width = GetScreenWidth();
    const int height = GetScreenHeight();
    int xoffset = GetRandomValue(width / ZONE_MIN_WIDTH, width / ZONE_MAX_WIDTH);
    int yoffset = GetRandomValue(height / ZONE_MIN_HEIGHT, height / ZONE_MAX_HEIGHT);

    //bool sens; // true: ascent; false: descent
    if (sens)
        yoffset *= -1;

    p2 = {start.x + xoffset, start.y + yoffset};

}

void Zone::Draw()
{

}

void Zone::DrawZone() const
{
    DrawRectangleLines((int) p1.x, (int) p1.y, (int) (p2.x - p1.x), (int) (p2.y - p1.y), sens ? RED : GREEN);
    DrawLineEx(p1, p2, 2, BLACK);
}

//void Zone::DrawZone() const
//{
//    DrawRectangleLinesEx(GetRectangle(), 2, sens ? RED : GREEN);
//    DrawLineEx(p1, p2, 2, BLACK);
//}

Rectangle Zone::GetRectangle() const
{
    return Rectangle{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y};
}


/*_______________________ MAP_______________________________*/

Map::Map()
{
    _currentType = F_TYPE::E_SIN;

    for (int i = 0; i < INIT_ZONES_NB; ++i) {
        AddZone();
    }
}

void Map::Update()
{

}

void Map::DrawDebug()
{
    for (const auto &item : _zones) {
        item.DrawZone();
    }
}

void Map::Draw()
{

}

void Map::AddZone()
{
    if (_zones.empty())
    {
        const int height = GetScreenHeight();
        Vector2 start{0, (float) (height - (height / ZONE_MIN_HEIGHT))};
        _zones.emplace_back(_currentType, start, (bool) GetRandomValue(0, 1));
        _zones.emplace_back(_currentType, start, (bool) GetRandomValue(0, 1));
        return;
    }

    bool orientation = (bool) GetRandomValue(0, 1);
    int size = _zones.size();

    if (_zones[size - 1].sens && _zones[size - 2].sens && orientation)
        orientation != orientation;

    _zones.emplace_back(_currentType, _zones.back().p2, orientation);
}

F_TYPE Map::GetCurrentType()
{
    return _currentType;
}

void Map::SetCurrentType(F_TYPE currentType)
{
    Map::_currentType = currentType;
}

