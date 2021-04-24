//
// Created by g.nisi on 07/04/2021.
//

#ifndef TINYWINGS_PLAYER_HPP
#define TINYWINGS_PLAYER_HPP

#include "raylib.h"

class Player
{

private:
    float _mass=1;
    float _gravity = 100;
    Vector2 _position;
    Vector2 _velocity{0,0};
    float _scale;
    float _speed{0.f};
    float _rotation{0.f};

    Texture2D _texture;

public:
    Player(const Vector2 &position, float scale);

    const Vector2 &GetPosition() const;

    void Update(float deltaTime);

    void Draw();
};


#endif //TINYWINGS_PLAYER_HPP
