//
// Created by g.nisi on 07/04/2021.
//

#ifndef TINYWINGS_PLAYER_HPP
#define TINYWINGS_PLAYER_HPP

#include "raylib.h"

class Player
{
    Vector2 _position;

private:
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
