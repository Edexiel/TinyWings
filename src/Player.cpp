//
// Created by g.nisi on 07/04/2021.
//

#include "Player.hpp"
#include "raymath.h"
#include <iostream>
#include "Map.hpp"
#include "Function.hpp"

using namespace Tinywings;

Player::Player(const Vector2& position, float scale) noexcept : _position(position), _scale(scale)
{
	_texture = LoadTexture("../assets/texture/frame-1.png");
	// SetTextureFilter(_texture,FILTER_TRILINEAR);
}

void Player::Update(float deltaTime, const Map& map) noexcept
{
	return;
	int zoneIndex = GetZoneIndex(map);
	if (zoneIndex != -1)
	{
		/*Zone zone = map._zones[zoneIndex];
		float funcY;

		if (zone.function.type == F_TYPE::E_ELLI)
		{
			if (_position.x + map.offset.x > zone.p1.x + (zone.p2.x - zone.p1.x)/2 )
			{
				funcY = zone.function.gx(_position.x + map.offset.x);
			}
		}
		else
		{
			funcY = zone.function.fx(_position.x+map.offset.x);
		}*/
		if (_position.y <= 0/*zone.heightPoints[zone.function.]*/ /*function.y*/)
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

			_direction = { 0.5, 0.5 }; // function.tangeante;
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
		_position = Vector2Add(_position, _direction);
		_direction = Vector2Normalize(_direction);
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
