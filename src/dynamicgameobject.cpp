/**
 * @file dynamicgameobject.cpp
 * @brief All definitions of function of the DynamicGameObject class.
 * @see DynamicGameObject.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "DynamicGameObject.hpp"

#include "Utils.hpp"
#include <iostream>
#include <memory>

DynamicGameObject::DynamicGameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox)
:GameObject{p_texture, p_src, p_dst, p_hitbox}
{}



const float* DynamicGameObject::getVector() const
{
	return(m_vector);
}

void DynamicGameObject::setVector(float p_x, float p_y) 
{
	m_vector[0] = p_x;
	m_vector[1] = p_y;
}



const SDL_FPoint* DynamicGameObject::getPreviousPosition() const
{
	return m_previousPos;
}

void DynamicGameObject::setPreviousPosition(const SDL_FPoint* p_previousPosition)
{
	m_previousPos->x = p_previousPosition->x;
	m_previousPos->y = p_previousPosition->y;	
}



void DynamicGameObject::handleCollision(const StaticGameObject* const p_otherGameObject)
{
	if(((getObjectType() == ObjectType::player) && !utils::isInWindow(p_otherGameObject)) || !p_otherGameObject) return;

	std::unique_ptr<std::vector<SDL_FPoint>> cornerPoints_unique {utils::getIntersectionCornerFPoints(getHitBox(), p_otherGameObject->getHitBox())};
	
	std::vector<SDL_FPoint>* cornerPoints = cornerPoints_unique.get();

	if(!cornerPoints) return;

	resolveCollision(cornerPoints, p_otherGameObject);
}

void DynamicGameObject::handleCollision(DynamicGameObject* const p_otherGameObject)
{
	if(((getObjectType() == ObjectType::player) && !utils::isInWindow(p_otherGameObject)) || !p_otherGameObject) return;

	std::unique_ptr<std::vector<SDL_FPoint>> cornerPoints_unique {utils::getIntersectionCornerFPoints(getHitBox(), p_otherGameObject->getHitBox())};
	
	std::vector<SDL_FPoint>* cornerPoints = cornerPoints_unique.get();

	if(!cornerPoints) return;

	resolveCollision(cornerPoints, p_otherGameObject);
}



void DynamicGameObject::resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, const StaticGameObject* const p_staticGameObject)
{
	if(!p_outerPoints || !p_staticGameObject)
		throw "RESOLVECOLLISION(): CALL_WITH_NULLPTR";

	SDL_FRect thisHitbox {*getHitBox()};

	SDL_FRect sOHitbox {*p_staticGameObject->getHitBox()};
	const ObjectType sOType {p_staticGameObject->getObjectType()};

	bool fromAbove{};
	bool fromLeft{};
	bool fromBelow{};
	bool fromRight{};

	/* iterates through each outerPoint and checks the directions from which the dO is colliding with the sO */

	for(const SDL_FPoint& outerPoint : (*p_outerPoints))
	{
		if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y))
		{
			if(m_previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y))  
		{
			if(m_previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((m_previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((m_previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x) && (outerPoint.y == sOHitbox.y))
		{
			if((m_previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x + sOHitbox.w) && outerPoint.y == sOHitbox.y)
		{
			if((m_previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == sOHitbox.x) && (outerPoint.y == sOHitbox.y + sOHitbox.h))
		{
			if(m_previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x + sOHitbox.w) && (outerPoint.y == sOHitbox.y + sOHitbox.h))
		{
			if(m_previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else
		{
			std::cout << "Error: CollisionPoint: " << outerPoint.x << ',' << outerPoint.y << "is not a outerPoint of either object that is colliding...\n";
		}
	}

	if(sOType == ObjectType::tile)
	{
		if(p_staticGameObject->adjancentTiles[0])
			fromAbove = false;
		if(p_staticGameObject->adjancentTiles[1])
			fromRight = false;
		if(p_staticGameObject->adjancentTiles[2])
			fromBelow = false;
		if(p_staticGameObject->adjancentTiles[3])
			fromLeft = false;
	}


	/* changes the position of the dO based on the directions it is colliding with the sO */

	if(fromAbove)
	{
		setVector(getVector()[0], 0);
		setY(sOHitbox.y - thisHitbox.h);
		isGrounded(true);
	}
	else if(fromRight)
	{
		setVector(0, (getVector())[1]);
		setX(sOHitbox.x + sOHitbox.w + 0.01);
	}
	else if(fromBelow)
	{
		setVector((getVector())[0], 0);
		setY(sOHitbox.y + sOHitbox.h + 0.01);
	}
	else if(fromLeft)
	{
		setVector(-1 * (getVector())[0], (getVector())[1]);
		setVector(0, (getVector())[1]);
		setX(sOHitbox.x - thisHitbox.w - 0.01);
	}
}


bool DynamicGameObject::isAlive()
{
	return(m_alive);
}

void DynamicGameObject::isAlive(bool p_isAlive)
{
	m_alive = p_isAlive;
}

int DynamicGameObject::getSpeed() const
{
	return m_speed;
}

void DynamicGameObject::setSpeed(int p_speed)
{
	m_speed = p_speed;
}


float DynamicGameObject::getMass() const
{
	return m_mass;
}

void DynamicGameObject::setMass(float p_mass)
{
	m_mass = p_mass;
}

bool DynamicGameObject::isGrounded() const
{
	return(m_grounded);
}

void DynamicGameObject::isGrounded(bool p_grounded)
{
	m_grounded = p_grounded;
}

