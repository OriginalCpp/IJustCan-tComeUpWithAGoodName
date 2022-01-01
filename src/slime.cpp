/**
 * @file slime.cpp
 * @brief Definitions of all functions of the Slime class.
 * @see Slime.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Slime.hpp"

#include "Constants.hpp"
#include "Utils.hpp"
#include <iostream>
#include <SDL.h>

Slime::Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect, float p_vectorX)
    :DynamicGameObject{p_tex, p_src, p_dst, p_collisionRect}
{
    setObjectType(ObjectType::slime);
    setVector(p_vectorX, 0);
    setSpeed(100);
}



void Slime::update(float p_elapsedTimeInSeconds)
{
    const SDL_FPoint* currentPosition {getPosition()};
    const float* currentVector {getVector()};

    setPreviousPosition(currentPosition);

    setX(currentPosition->x + getSpeed() * p_elapsedTimeInSeconds * currentVector[0]);
    setY(currentPosition->y + p_elapsedTimeInSeconds * currentVector[1]);

    setVector(currentVector[0], currentVector[1] + constants::gravity * p_elapsedTimeInSeconds);
}



void Slime::resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, const StaticGameObject* const p_staticGameObject)
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

    const SDL_FPoint* previousPos {getPreviousPosition()};

	/* iterates through each outerPoint and checks the directions from which the dO is colliding with the sO */

	for(const SDL_FPoint& outerPoint : (*p_outerPoints))
	{
		if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y))
		{
			if(previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y))  
		{
			if(previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x) && (outerPoint.y == sOHitbox.y))
		{
			if((previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x + sOHitbox.w) && outerPoint.y == sOHitbox.y)
		{
			if((previousPos->y + thisHitbox.h) <= sOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == sOHitbox.x) && (outerPoint.y == sOHitbox.y + sOHitbox.h))
		{
			if(previousPos->y >= sOHitbox.y + sOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == sOHitbox.x + sOHitbox.w) && (outerPoint.y == sOHitbox.y + sOHitbox.h))
		{
			if(previousPos->y >= sOHitbox.y + sOHitbox.h)
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
		setVector(-1 * (getVector())[0], (getVector())[1]);
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
		setX(sOHitbox.x - thisHitbox.w - 0.01);
	}
}



void Slime::resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_dynamicGameObject)
{
    if(!p_outerPoints || !p_dynamicGameObject)
		throw "RESOLVECOLLISION(): CALL_WITH_NULLPTR";

	const SDL_FRect& thisHitbox {*getHitBox()};

	const SDL_FRect& dOHitbox {*p_dynamicGameObject->getHitBox()};

	bool fromAbove{};
	bool fromLeft{};
	bool fromBelow{};
	bool fromRight{};

	const SDL_FPoint* previousPos {getPreviousPosition()};

	/* iterates through each outerPoint and checks the directions from which the dO is colliding with the sO */

	//TODO make as own function that returns array of booleans!
	for(const SDL_FPoint& outerPoint : (*p_outerPoints))
	{
		if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y))
		{
			if(previousPos->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y))  
		{
			if(previousPos->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == thisHitbox.x) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPos->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == thisHitbox.x + thisHitbox.w) && (outerPoint.y == thisHitbox.y + thisHitbox.h))
		{
			if((previousPos->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x) && (outerPoint.y == dOHitbox.y))
		{
			if((previousPos->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x + dOHitbox.w) && outerPoint.y == dOHitbox.y)
		{
			if((previousPos->y + thisHitbox.h) <= dOHitbox.y)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if((outerPoint.x == dOHitbox.x) && (outerPoint.y == dOHitbox.y + dOHitbox.h))
		{
			if(previousPos->y >= dOHitbox.y + dOHitbox.h)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if((outerPoint.x == dOHitbox.x + dOHitbox.w) && (outerPoint.y == dOHitbox.y + dOHitbox.h))
		{
			if(previousPos->y >= dOHitbox.y + dOHitbox.h)
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

	
	if(fromRight)
    {
		float xIntersectionLength {dOHitbox.x + dOHitbox.w - thisHitbox.x};

		setX(thisHitbox.x + xIntersectionLength * 0.5 + 0.01);
        setVector(-1 * getVector()[0], getVector()[1]); 

		p_dynamicGameObject->setX(dOHitbox.x - xIntersectionLength * 0.5 - 0.01);
		p_dynamicGameObject->setVector(-1 * p_dynamicGameObject->getVector()[0], p_dynamicGameObject->getVector()[1]);
    }
    else if(fromLeft)
    {
		float xIntersectionLength {thisHitbox.x + thisHitbox.w - dOHitbox.x};

		setX(thisHitbox.x - xIntersectionLength * 0.5 - 0.01);
        setVector(-1 * getVector()[0], getVector()[1]);

		p_dynamicGameObject->setX(dOHitbox.x + xIntersectionLength * 0.5 + 0.01);
		p_dynamicGameObject->setVector(-1 * p_dynamicGameObject->getVector()[0], p_dynamicGameObject->getVector()[1]);
    }
}


void Slime::jump(){}

void Slime::die()
{
    isAlive(false);
}