#include "Map.hpp"
#include "Functions.hpp"

using namespace Tinywings;
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
    //true : RED
    //false : GREEN
    //ascendant : Rouge
    //Descendant : VERT
    if (sens)
        yoffset *= -1;

    p2 = {start.x + (float)xoffset, start.y + (float)yoffset};

    switch (functionType) {

        case F_TYPE::E_SIN:
            heightPoints = SinusFunction::Create(p1, p2, 1, 1);
            break;
        case F_TYPE::E_POLY:
            heightPoints = PolyFunction::Create(p1, p2, 1);
            break;
        case F_TYPE::E_ELLI:
            heightPoints = EllipticFunction::Create(p1, p2, 1);
            break;
        case F_TYPE::E_HYP:
            break;
    }

    for (float &item : heightPoints) {
        item = (float)GetScreenHeight()-item;
    }

}

void Zone::Draw()
{

}

void Zone::DrawZone() const
{

    DrawRectangleLines((int) p1.x, (int) p1.y, (int) (p2.x - p1.x), (int) (p2.y - p1.y), sens ? RED : GREEN);

    for (int i = 0; i < heightPoints.size()-1; ++i)
    {
        DrawLine(p1.x + i, heightPoints[i], p1.x + (i + 1.f), heightPoints[i + 1.f], BLACK);
    }
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
    _allPoints.reserve(2000);


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

void Map::CreateBuffer()
{
    _allPoints.clear();

    for (Zone &item : _zones)
    {
        _allPoints.insert(_allPoints.end(), item.heightPoints.begin(), item.heightPoints.end());
        if(_allPoints.size()>=1000)
            return;
    }
}

void Map::AddZone()
{
    if (_zones.empty())
    {
        const int height = GetScreenHeight();
        Vector2 start{0, (float)(height -((float)height/3.f))};

        _zones.emplace_back(_currentType, start, (bool) GetRandomValue(0, 1));
        _zones.emplace_back(_currentType, _zones.back().p2, (bool) GetRandomValue(0, 1));
        return;
    }

    bool orientation = (bool) GetRandomValue(0, 1);
    int size = _zones.size();

    if (_zones[size - 1].sens && orientation)
        orientation = !orientation;

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

