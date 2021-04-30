//
// Created by g.nisi on 07/04/2021.
//

#include "Player.hpp"
#include "raymath.h"
#include <iostream>

Player::Player(const Vector2& position, float scale) : _position(position), _scale(scale)
{
    _texture = LoadTexture("../assets/texture/frame-1.png");
    // SetTextureFilter(_texture,FILTER_TRILINEAR);
}

void Player::Update(float deltaTime)
{
    return;
    if (_position.y <= 0 /*function.y*/)
    {
        _position.y = 0 /*function.y*/;

        if (IsKeyDown(KEY_SPACE))
        {
            if (/*!function.isAscending*/ true)
            {
                _speed += _speedAcceleration;
            }

            else
            {
                _speed -= _speedAcceleration;

                if (_speed < _baseSpeed)
                {
                    _speed = _baseSpeed;
                }
            }
        }

        if (_direction.y < -0.5 && /*function.isAscending*/ false)
        {
            _speed = _baseSpeed;
        }

        _direction = {0.5, 0.5}; // function.tangeante;
        _direction = Vector2Normalize(_direction);
    }

    else
    {
        if (IsKeyDown(KEY_SPACE))
        {
            _speed += _speedAcceleration;
            _direction.y -= _directionAcceleration;
            _direction = Vector2Normalize(_direction);
        }

        _direction.y -= _gravity;
        _direction = Vector2Normalize(_direction);
    }
    _direction = Vector2Scale(_direction, _speed);
    _position  = Vector2Add(_position, _direction);
    _direction = Vector2Normalize(_direction);

    // std::cout << "Speed = {" << _speed << "}" << std::endl;
    // std::cout << "Direction = {" << _direction.x << ";" << _direction.y << "}" << std::endl;
}

void Player::Draw()
{
    DrawTextureEx(_texture, _position, _rotation, _scale, WHITE);
}

const Vector2& Player::GetPosition() const
{
    return _position;
}
