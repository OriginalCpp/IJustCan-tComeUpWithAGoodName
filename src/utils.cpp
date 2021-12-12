#include "utils.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

//creates a SDL_Rect with given dimensions

SDL_Rect utils::createRect(int p_x, int p_y, int p_width, int p_height)
{
	SDL_Rect rect;
	rect.x = p_x;
	rect.y = p_y;
	rect.w = p_width;
	rect.h = p_height;
	return(rect);
}



//checks for collision between a point and a rectangle (1 = collision detected; 0 = no collision)

bool utils::collision_PointVsRect(float* p_point, float* p_rectOrigin, int p_rectWidth, int p_rectHeight)
{
	if((p_point[0] >= p_rectOrigin[0]) && (p_point[0] <= (p_rectOrigin[0] + p_rectWidth)) 
		&& (p_point[1] >= p_rectOrigin[1]) && (p_point[1] <= (p_rectOrigin[1] + p_rectHeight)))  //nur < damit der Spieler nicht unten an Blöcken hängen bleibt!
		return true;
	else 
		return false;
}



//checks from which direction the collision is happening and accordingly adjusts the position and the vector of the p_dynamicObject
//only works if a dynamicObject is colliding with a staticGameObject
//true = player is on the floor, false = player is not on the floor

bool utils::resolveCollision(Player* p_dynamicGameObject, float* p_collisionPoint, GameObject* p_staticGameObject)
{
	float dOX {p_dynamicGameObject->getX()};
	float dOY {p_dynamicGameObject->getY()};
	int dOW   {p_dynamicGameObject->getW()};
	int dOH   {p_dynamicGameObject->getH()};
	float sOX {p_staticGameObject->getX()};
	float sOY {p_staticGameObject->getY()};
	int sOW   {p_staticGameObject->getW()};
	int sOH   {p_staticGameObject->getH()};
	float* pP {p_dynamicGameObject->getpP()};
	if((p_collisionPoint[0] == dOX) && (p_collisionPoint[1] == dOY))
	{
		if(pP[1] >= sOY + sOH)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY + sOH + 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW);
		}
	}
	else if((p_collisionPoint[0] == dOX + dOW) && (p_collisionPoint[1] == dOY))  
	{
		if(pP[1] >= sOY + sOH)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY + sOH + 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW);
		}
	}
	else if((p_collisionPoint[0] == dOX) && (p_collisionPoint[1] == dOY + dOH))
	{
		if((pP[1] + dOH) <= sOY)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY - dOH);
			return(true);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW);
		}
	}
	else if((p_collisionPoint[0] == dOX + dOW) && (p_collisionPoint[1] == dOY + dOH))
	{
		if((pP[1] + dOH) <= sOY)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY - dOH);
			return(true);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW);
		}
	}
	else if((p_collisionPoint[0] == sOX) && (p_collisionPoint[1] == sOY))
	{
		if((pP[1] + dOH) <= sOY)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY - dOH);
			return(true);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW);
		}
	}
	else if((p_collisionPoint[0] == sOX + sOW) && p_collisionPoint[1] == sOY)
	{
		if((pP[1] + dOH) <= sOY)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY - dOH);
			return(true);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW);
		}
	}
	else if((p_collisionPoint[0] == sOX) && (p_collisionPoint[1] == sOY + sOH))
	{
		if(pP[1] >= sOY + sOH)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY + sOH + 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW);
		}
	}
	else if((p_collisionPoint[0] == sOX + sOW) && (p_collisionPoint[1] == sOY + sOH))
	{
		if(pP[1] >= sOY + sOH)
		{
			p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
			p_dynamicGameObject->setY(sOY + sOH + 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW);
		}
	}
	return(false);
}


SDL_Texture* utils::loadTexture(const char* p_filePath, SDL_Renderer* p_renderer) 
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(p_renderer, p_filePath);
	if (texture == NULL)
		std::cout << "Could not load Texture. Error: " << SDL_GetError() << std::endl;
	else
		std::cout << "Texture loaded: " << p_filePath << std::endl;
	return(texture);
}

Player* utils::setUpPlayer(SDL_Renderer* p_renderer)
{
	SDL_Texture* playerStanding = utils::loadTexture("../res/player/maincharacter.png", p_renderer);
    Player* player = new Player(playerStanding, utils::createRect(0, 0, 16, 23), utils::createRect(190, 350, 64, 92), 92, 64);
	return(player);
}

