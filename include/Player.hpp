//
// Created by g.nisi on 07/04/2021.
//

#ifndef TINYWINGS_PLAYER_HPP
#define TINYWINGS_PLAYER_HPP

#include "raylib.h"

namespace Tinywings
{
class Map;

class Player
{

private:
    // float _mass=1;
    float     _scale                 = {1.f};
    float     _rotation              = {0.f};
    float     _gravity               = {2.f};
    Vector2   _direction             = {1.f, 0.f};
    float     _baseSpeed             = {200.f};
    float     _directionAcceleration = {10.f};
    float     _speedAcceleration     = {100.f};
    Texture2D _texture;

public:
    float   _speed    = {250.f};
    Vector2 _position = {0, 0};
    Player(const Vector2& position, float scale) noexcept;

    const Vector2& GetPosition() const noexcept;

    void Update(float deltaTime, Map* map) noexcept;

    int GetZoneIndex(const Map& map) noexcept;

    void Draw() noexcept;
};
} // namespace Tinywings
#endif // TINYWINGS_PLAYER_HPP
