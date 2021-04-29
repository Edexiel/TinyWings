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
#define NB_POINTS 512
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
        Vector2 p1;
        Vector2 p2;
        Vector2 size;
        std::vector<float> heightPoints;

        bool sens;     //true : RED ascendant //false : GREEN Descendant

        Zone(F_TYPE, Vector2 &start, bool orientation, float precision);

        //Rectangle GetRectangle() const;

        void DrawZone() const;

        std::vector<float> &getPoints();
    };

    class Map
    {
    private:
        std::deque<Zone> _zones;
    public:
        float speed;
        Vector2 offset{0, 0};

        int _precision;
        F_TYPE _currentType;

        std::vector<float> _allPoints;
        std::vector<float> _buffer;

        explicit Map(int precision);

        void DrawDebug();

        void CreateBuffer();

        float GetValue(int x);

        void AddZone();
    };

} // namespace Tinywings

#endif // TINYWINGS_MAP_HPP
