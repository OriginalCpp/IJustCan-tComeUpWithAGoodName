#include "Player.hpp"
#include "GameObject.hpp"
#include "Constants.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>

Player::Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect)
	:GameObject{p_tex, p_src, p_dst, p_collisionRect}
{
	objectType = ObjectType::player;
}

void Player::setGoalX(int goal)
{
	Goal[0] = goal;
}

int Player::getGoalX()
{
	return Goal[0];
}

void Player::move(float p_dt, int p_speed) {
	float difference = Goal[0] - vector[0]; 
	float dt = p_dt * 10;
	if (difference > dt)
	{
		vector[0] += dt;
	}
	else if (difference < -dt)
	{
		vector[0] -= dt;
	}
	else
	{
		vector[0] = Goal[0];
	}
	previousPos[0] = pos[0];
	previousPos[1] = pos[1];
	pos[0] += p_speed * p_dt * vector[0];
	pos[1] += p_dt * vector[1];
	vector[1] += constants::gravity * p_dt;
	
	collisionRect.x = pos[0];
	collisionRect.y = pos[1];

	dst.x = pos[0];
	dst.y = pos[1] - (dst.h - collisionRect.h);
}

