//
// Created by g.nisi on 07/04/2021.
//

#include "Player.hpp"
#include "Map.hpp"
#include "raymath.h"
#include <iostream>

using namespace Tinywings;

Player::Player(const Vector2& position, float scale) noexcept : _position(position), _scale(scale)
{
    _texture = LoadTexture("../assets/texture/frame-1.png");
    // SetTextureFilter(_texture,FILTER_TRILINEAR);
}

void Player::Update(float deltaTime, Map* map) noexcept
{
    int zoneIndex = GetZoneIndex(*map);
    if (zoneIndex != -1)
    {
        const Zone& zone = map->_zones[zoneIndex];

        float funcY = zone.function->image(_position.x + map->_offset.x + (_texture.width * _scale * 0.5));

        if (_position.y >= funcY - (_texture.height * _scale))
        {
            _position.y = funcY - (_texture.height * _scale);

            if (IsKeyDown(KEY_SPACE))
            {
                if (!zone.function->isAscending)
                {
                    _speed += _speedAcceleration * deltaTime;
                }

                else
                {
                    _speed -= _speedAcceleration * deltaTime;

                    if (_speed < _baseSpeed)
                    {
                        _speed = _baseSpeed;
                    }
                }
            }

            if (_direction.y > 0 && !zone.function->isAscending)
            {
                _speed = _baseSpeed;
            }

            _direction = {1, zone.function->deriv1(_position.x + map->_offset.x + (_texture.width * _scale * 0.5))};
            if (Vector2Length(_direction) > 0)
            {
                _direction = Vector2Normalize(_direction);
            }
        }

        else
        {
            if (IsKeyDown(KEY_SPACE))
            {
                _speed += _speedAcceleration * deltaTime;
                _direction.y += _directionAcceleration * deltaTime;
                if (Vector2Length(_direction) > 0)
                {
                    _direction = Vector2Normalize(_direction);
                }
            }

            _direction.y += _gravity * deltaTime;
            if (Vector2Length(_direction) > 0)
            {
                _direction = Vector2Normalize(_direction);
            }
        }
        float deltaSpeed = _speed * deltaTime;
        _direction       = Vector2Scale(_direction, deltaSpeed);
        _position.y      = _position.y + _direction.y;
        map->_offset.x   = map->_offset.x + _direction.x * deltaTime;
        if (Vector2Length(_direction) > 0)
        {
            _direction = Vector2Normalize(_direction);
        }
    }
    // std::cout << "Speed = {" << _speed << "}" << std::endl;
    // std::cout << "Direction = {" << _direction.x << ";" << _direction.y << "}" << std::endl;
}

void Player::Draw() noexcept
{
    DrawTextureEx(_texture, _position, _rotation, _scale, WHITE);
}

const Vector2& Player::GetPosition() const noexcept
{
    return _position;
}

int Player::GetZoneIndex(const Map& map) noexcept
{
    float realX = _position.x + map._offset.x;
    for (int i = 0; i < map._zones.size(); i++)
    {
        if (realX >= map._zones[i].p1.x && realX <= map._zones[i].p2.x)
        {
            return i;
        }
    }

    return -1;
}
