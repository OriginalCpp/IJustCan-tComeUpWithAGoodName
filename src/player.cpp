#include "Player.hpp"
#include "GameObject.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>

Player::Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, int p_w, int p_h)
	:GameObject{p_tex, p_src, p_dst, p_w, p_h}
{

}

void Player::setGoalX(int goal)
{
	Goal[0] = goal;
}

int Player::getGoalX()
{
	return Goal[0];
}

void Player::move(float p_dt, int p_speed, int p_gravity) {
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
	previousPos[0] = x;
	previousPos[1] = y;
	x += p_speed * p_dt * vector[0];
	y += p_dt * vector[1];
	vector[1] += p_gravity * p_dt;
	dst = utils::createRect(x, y, w, h);
}

//detects wether the player is colliding a GameObject or not and then returns the point which is colliding

float* Player::detectCollision(GameObject* p_gameObject)
{
	float objectX = p_gameObject->getX();
	float objectY = p_gameObject->getY();
	int objectH {p_gameObject->getH()};
	int objectW {p_gameObject->getW()};
	float objectPoints[4][2] = { {objectX, objectY},
								 {objectX + objectW, objectY},
								 {objectX + objectW, objectY + objectH},
								 {objectX, objectY + objectH}};							
	float playerPoints[4][2] = { {x, y},
								 {x + w, y},
								 {x + w, y + h},
								 {x, y + h}};
	
	float* collisionPoint = new float[2];
	
	for(int i = 0; i < 4; i++)
	{
		if(utils::collision_PointVsRect(playerPoints[i], objectPoints[0], objectW, objectH))
		{
			collisionPoint[0] = playerPoints[i][0];
			collisionPoint[1] = playerPoints[i][1];
			return(collisionPoint);
		}
		if(utils::collision_PointVsRect(objectPoints[i], playerPoints[0], w, h))
		{
			collisionPoint[0] = objectPoints[i][0];
			collisionPoint[1] = objectPoints[i][1];
			return(collisionPoint);
		}
	}
	return(NULL);
}