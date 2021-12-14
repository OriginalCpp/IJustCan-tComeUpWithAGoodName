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

//checks for each tile for adjancent tiles and then sets the texture(s) so that they match

void utils::selectTiles(std::vector<std::vector<Tile*>>& p_tiles)
{

	for(int i = 0; i < (static_cast<int>(p_tiles.size())); ++i)
	{
		for(int j = 0; j < (static_cast<int>(p_tiles[0].size())); ++j)
		{
			if(p_tiles[i][j] == NULL)
			{
				continue;
			}

			/*while(p_tiles[i][j] == NULL)
			{
				++j;
				if(j == (static_cast<int>(p_tiles[0].size()) - 1))
				{
					++i;

				}
			}*/
			bool top {};
			bool right {};
			bool below{};
			bool left {};

			if (i > 0)
			{
				if(p_tiles[i - 1][j] != NULL)
					top = true;
			}
			else
				top = true;

			if (j < (static_cast<int>(p_tiles[0].size()) - 1))
			{
				if(p_tiles[i][j+1] != NULL)
				right = true;
			}
			else
			 	right = true;
	
			if(i < (static_cast<int>(p_tiles.size()) - 1))
			{
				if(p_tiles[i + 1][j] != NULL)
				below = true;
			}
			else	
				below = true;

			if(j > 0)
			{
				if(p_tiles[i][j - 1] != NULL)
					left = true;
			}
			else 
				left = true;

			if(!top && !right && !below && !left)
				p_tiles[i][j]->setSrc(utils::createRect(0, 0, 16, 16));
			else if(!right && !below && !left)
				p_tiles[i][j]->setSrc(utils::createRect(16, 0, 16, 16));
			else if(!top && !below && !left)
				p_tiles[i][j]->setSrc(utils::createRect(16*2, 0, 16, 16));
			else if(!top && !right && !left)
				p_tiles[i][j]->setSrc(utils::createRect(16*3, 0, 16, 16));
			else if(!top && !right && !below)
				p_tiles[i][j]->setSrc(utils::createRect(0, 16, 16, 16));
			else if(!below && !left)
				p_tiles[i][j]->setSrc(utils::createRect(16, 16, 16, 16));
			else if(!right && !left)
				p_tiles[i][j]->setSrc(utils::createRect(16*2, 16, 16, 16));
			else if(!right && !below)
				p_tiles[i][j]->setSrc(utils::createRect(16*3, 16, 16, 16));
			else if(!top && !left)
				p_tiles[i][j]->setSrc(utils::createRect(0, 32, 16, 16));
			else if(!top && !below)
				p_tiles[i][j]->setSrc(utils::createRect(16, 32, 16, 16));
			else if(!top && !right)
				p_tiles[i][j]->setSrc(utils::createRect(16*2, 32, 16, 16));
			else if(!left)
				p_tiles[i][j]->setSrc(utils::createRect(16*3, 32, 16, 16));
			else if(!below)
				p_tiles[i][j]->setSrc(utils::createRect(0, 48, 16, 16));
			else if(!top)
				p_tiles[i][j]->setSrc(utils::createRect(16, 48, 16, 16));
			else if(!right)
				p_tiles[i][j]->setSrc(utils::createRect(16*2, 48, 16, 16));
			else
				p_tiles[i][j]->setSrc(utils::createRect(16*3, 48, 16, 16));
		}
	}
}
