/**
 * @file player.cpp
 * @brief All definitions of functions of the Player class.
 * @see Player.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Player.hpp"

#include "GameObject.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include <SDL.h>
#include <iostream>

Player::Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox)
	:DynamicGameObject{p_tex, p_src, p_dst, p_hitbox}
{
	setObjectType(ObjectType::player);
	setSpeed(constants::normalPlayerSpeed);
}



void Player::resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_dynamicGameObject)
{
	if(!p_outerPoints || !p_dynamicGameObject)
		throw "RESOLVECOLLISION(): CALL_WITH_NULLPTR";

	const SDL_FRect thisHitbox {*getHitBox()};

	const SDL_FRect dOHitbox {*p_dynamicGameObject->getHitBox()};
	const ObjectType dOType {p_dynamicGameObject->getObjectType()};

	bool fromAbove{};
	bool fromLeft{};
	bool fromBelow{};
	bool fromRight{};

	const SDL_FPoint* previousPosition {getPreviousPosition()};

	/* iterates through each outerPoint and checks the directions from which the dO is colliding with the sO */

	for(const SDL_FPoint& outerPoint : (*p_outerPoints))
	{
		if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y))
		{
			if(previousPosition->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y))  
		{
			if(previousPosition->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPosition->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPosition->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x) && (outerPoint.y == dOHitbox.y))
		{
			if((previousPosition->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x + dOHitbox.w) && outerPoint.y == dOHitbox.y)
		{
			if((previousPosition->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == dOHitbox.x) && (outerPoint.y == dOHitbox.y + dOHitbox.h))
		{
			if(previousPosition->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x + dOHitbox.w) && (outerPoint.y == dOHitbox.y + dOHitbox.h))
		{
			if(previousPosition->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else
		{
			std::cout << "Error: CollisionPoint: " << outerPoint.x << ',' << outerPoint.y 
			<< "is not an outerPoint of either object that is colliding...\n";
		}
	}

	/* changes the position of the dO based on the directions it is colliding with the sO */
		
	if(dOType == ObjectType::slime)
	{
		if(fromAbove)
		{
			p_dynamicGameObject->die();

			int initialSpeed {getSpeed()};
			setSpeed(initialSpeed / 2);
			jump();
			setSpeed(initialSpeed);
		}
		else if(fromRight || fromBelow || fromLeft)
		{
			die();
		}
	}
}



void Player::update(float p_elapsedTimeInSeconds) 
{
	const SDL_FPoint* currentPosition {getPosition()};
	const float* currentVector {getVector()};

	setPreviousPosition(currentPosition);

	setX(currentPosition->x + getSpeed() * p_elapsedTimeInSeconds * currentVector[0]);
	setY(currentPosition->y + p_elapsedTimeInSeconds * currentVector[1]);

	float neededToReachGoal = m_xVelocityGoal - currentVector[0]; 
	float accelerationX = p_elapsedTimeInSeconds * 7;

	if (neededToReachGoal > accelerationX)
		setVector(currentVector[0] + accelerationX, currentVector[1] + constants::gravity * getMass() * p_elapsedTimeInSeconds);
	else if (neededToReachGoal < -accelerationX)
		setVector(currentVector[0] - accelerationX, currentVector[1] + constants::gravity * getMass() * p_elapsedTimeInSeconds);
	else
		setVector(m_xVelocityGoal, currentVector[1] + constants::gravity * getMass() * p_elapsedTimeInSeconds);
}



void Player::jump()
{
	constexpr int simplification = -2*constants::normalJumpHeight/(constants::normalJumpWidth/2); 
	setVector(getVector()[0], simplification * getSpeed());
}

void Player::die()
{
	isAlive(false);
}



int Player::getXVelocityGoal()
{
	return m_xVelocityGoal;
}

void Player::setXVelocityGoal(int goal)
{
	m_xVelocityGoal = goal;
}



int Player::getAmountOfJumps() const
{
	return m_amountOfJumps;
}

void Player::setAmountOfJumps(int p_newAmount)
{
	m_amountOfJumps = p_newAmount;
}