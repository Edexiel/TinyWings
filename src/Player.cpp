//
// Created by g.nisi on 07/04/2021.
//

#include "Player.hpp"
#include "raymath.h"

Player::Player(const Vector2 &position,float scale) : _position(position),_scale(scale)
{
    _texture = LoadTexture("../assets/texture/frame-1.png");
    //SetTextureFilter(_texture,FILTER_TRILINEAR);
}

void Player::Update(float deltaTime)
{
    _velocity = Vector2Add(_velocity,Vector2{0,(_gravity)*deltaTime});
    _position.y += (_velocity.y*deltaTime);
}

void Player::Draw()
{
    DrawTextureEx(_texture,_position,_rotation,_scale,WHITE);
}

const Vector2 &Player::GetPosition() const
{
    return _position;
}
