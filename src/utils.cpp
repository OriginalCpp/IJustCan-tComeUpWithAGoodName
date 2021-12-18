#include "utils.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

//initializes all parts of SDL that we need

int utils::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_INIT_VIDEO has failed. Error:" << SDL_GetError() << std::endl;
		return(1);
	}
	if (!(IMG_Init(IMG_INIT_PNG))) 
	{
		std::cout << "IMG_INIT_PNG has failed. Error:" << SDL_GetError() << std::endl;
		return(1);
	}	
	return(0);
}

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

SDL_FRect utils::createFRect(float p_x, float p_y, float p_width, float p_height)
{
	SDL_FRect frect;
	frect.x = p_x;
	frect.y = p_y;
	frect.w = p_width;
	frect.h = p_height;
	return frect;
}


SDL_Texture* utils::loadTexture(const char* p_filePath, SDL_Renderer* p_renderer) 
{
	SDL_Texture* texture {NULL};
	texture = IMG_LoadTexture(p_renderer, p_filePath);
	if (texture == NULL)
		std::cout << "Could not load Texture. Error: " << SDL_GetError() << std::endl;
	else
		std::cout << "Texture loaded: " << p_filePath << std::endl;
	return(texture);
}


/**
 * @brief checks for a collision
 * 
 * @param p_point the point for the collision check
 * @param rect the rect for the collision check
 * @return true collision detected
 * @return false no collision detected 
 */

bool utils::collision_PointVsRect(float* p_point, SDL_FRect rect)
{
	if((p_point[0] >= rect.x) && (p_point[0] <= (rect.x + rect.w)) 
		&& (p_point[1] >= rect.y) && (p_point[1] <= (rect.y + rect.h)))
		return true;
	else 
		return false;
}


/**
 * @brief checks from which direction the collision is happening and accordingly adjusts the position and the vector of the p_dynamicObject
 * 
 * !only works if a dynamicObject is colliding with a staticGameObject
 * 
 * @param p_dynamicGameObject dynamic object to change the position of
 * @param p_collisionPoint    points which collides with the other object
 * @param p_staticGameObject  static object to collide with
 * @return true = player is on the floor
 * @return false = player is not on the floor; or error
 */

bool utils::resolveCollision(GameObject* p_dynamicGameObject, std::vector<std::vector<float>>* p_collisionPoint, GameObject* p_staticGameObject)
{
	if(!p_dynamicGameObject || !p_staticGameObject || !p_collisionPoint)
	{
		std::cout << "Error: Call to resolveCollision with nullptr\n";
		return(false);
	}

	bool grounded {};

	float dOX {p_dynamicGameObject->getX()};
	float dOY {p_dynamicGameObject->getY()};
	int dOW   {p_dynamicGameObject->getW()};
	int dOH   {p_dynamicGameObject->getH()};

	float sOX {p_staticGameObject->getX()};
	float sOY {p_staticGameObject->getY()};
	int sOW   {p_staticGameObject->getW()};
	int sOH   {p_staticGameObject->getH()};

	bool fromAbove{};
	bool fromLeft{};
	bool fromBelow{};
	bool fromRight{};

	float* pP {p_dynamicGameObject->getpP()};

	/* iterates through each collision point and checks the directions from which the dO is colliding with the sO */

	for(int i = 0; i < static_cast<int>(p_collisionPoint->size()); ++i)
	{
		if(((*p_collisionPoint)[i][0] == dOX) && ((*p_collisionPoint)[i][1] == dOY))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoint)[i][0] == dOX + dOW) && ((*p_collisionPoint)[i][1] == dOY))  
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoint)[i][0] == dOX) && ((*p_collisionPoint)[i][1] == dOY + dOH))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoint)[i][0] == dOX + dOW) && ((*p_collisionPoint)[i][1] == dOY + dOH))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoint)[i][0] == sOX) && ((*p_collisionPoint)[i][1] == sOY))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoint)[i][0] == sOX + sOW) && (*p_collisionPoint)[i][1] == sOY)
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoint)[i][0] == sOX) && ((*p_collisionPoint)[i][1] == sOY + sOH))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoint)[i][0] == sOX + sOW) && ((*p_collisionPoint)[i][1] == sOY + sOH))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromRight = true;
		}
		else
		{
			std::cout << "Error: CollisionPoint: " << (*p_collisionPoint)[i][0] << ',' << (*p_collisionPoint)[i][1] << "is not a point of either object that is colliding...\n";
		}
	}

	/* changes the position of the dO based on the directions it is colliding with the sO */

	if(fromAbove)
	{
		std::cout << "Collision from above\n";
		p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
		p_dynamicGameObject->setY(sOY - dOH);
		grounded = true;
	}
	if(fromRight)
	{
		std::cout << "Collision from right\n";
		p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
		p_dynamicGameObject->setX(sOX + sOW + 0.01);
	}
	if(fromBelow)
	{
		std::cout << "Collision from below\n";
		p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
		p_dynamicGameObject->setY(sOY + sOH + 0.01);
	}
	if(fromLeft)
	{
		std::cout << "Collision from left\n";
		p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
		p_dynamicGameObject->setX(sOX - dOW - 0.01);
	}

	return(grounded);
}




/**
 * @brief checks for each tile for adjancent tiles and then sets the texture(s) so that the tiles match
 * 
 * @param p_tiles 
 */

void utils::selectTiles(std::vector<std::vector<Tile*>>& p_tiles)
{
	int outerSize {static_cast<int>(p_tiles.size())};
	int innerSize {static_cast<int>(p_tiles[0].size())};

	for(int i = 0; i < outerSize; ++i)
	{
		for(int j = 0; j < innerSize; ++j)
		{
			if(!p_tiles[i][j])
			{
				continue;
			}
			
			bool top {};
			bool right {};
			bool below{};
			bool left {};

			if (i > 0)
			{
				if(p_tiles[i - 1][j])
					top = true;
			}
			else
				top = true;

			if (j < innerSize - 1)
			{
				if(p_tiles[i][j+1])
				right = true;
			}
			else
			 	right = true;
	
			if(i < outerSize - 1)
			{
				if(p_tiles[i + 1][j])
				below = true;
			}
			else	
				below = true;

			if(j > 0)
			{
				if(p_tiles[i][j - 1])
					left = true;
			}
			else 
				left = true;


			if(top && right && below && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && below && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && below && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right && left)
				p_tiles[i][j]->setSrc(utils::createRect(0, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right && below)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(below && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && below)
				p_tiles[i][j]->setSrc(utils::createRect(0, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && left)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && below)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(left)
				p_tiles[i][j]->setSrc(utils::createRect(0, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(below)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*3, 0, constants::tileSprite::w, constants::tileSprite::h));
			else if(right)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w*2, 0, constants::tileSprite::w, constants::tileSprite::h));
			else if(top)
				p_tiles[i][j]->setSrc(utils::createRect(constants::tileSprite::w, 0, constants::tileSprite::w, constants::tileSprite::h));
			else	
				p_tiles[i][j]->setSrc(utils::createRect(0, 0, constants::tileSprite::w, constants::tileSprite::h));
		}
	}
}