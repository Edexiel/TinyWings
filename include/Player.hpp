//
// Created by g.nisi on 07/04/2021.
//

#ifndef TINYWINGS_PLAYER_HPP
#define TINYWINGS_PLAYER_HPP

#include "raylib.h"

class Player
{

public:
    // float _mass=1;
    float     _scale                 = {1.f};
    float     _rotation              = {0.f};
    float     _gravity               = {0.0002f};
    Vector2   _direction             = {1.f, 0.f};
    float     _speed                 = {1.f};
    float     _baseSpeed             = {1.f};
    float     _directionAcceleration = {0.001f};
    float     _speedAcceleration     = {0.00001f};
    Texture2D _texture;

public:
    Vector2 _position = {0, 0};
    Player(const Vector2& position, float scale);

    const Vector2& GetPosition() const;

    void Update(float deltaTime);

    void Draw();
};

#endif // TINYWINGS_PLAYER_HPP
