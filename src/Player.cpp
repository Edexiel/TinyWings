//
// Created by g.nisi on 07/04/2021.
//

#include "Player.hpp"

Player::Player(const Vector2 &position,float scale) : _position(position),_scale(scale)
{
    _texture = LoadTexture("../assets/texture/frame-1.png");
    //SetTextureFilter(_texture,FILTER_TRILINEAR);
}

void Player::Update(float deltaTime)
{

}

void Player::Draw()
{
    DrawTextureEx(_texture,_position,_rotation,_scale,WHITE);
}

const Vector2 &Player::GetPosition() const
{
    return _position;
}
