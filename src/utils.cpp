#define SDL_MAIN_HANDLED
#include "utils.hpp"
#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tiles.hpp"
#include "Camera.hpp"
#include "constants.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

/**
 * @brief Initializes SDL's video subsystem and the PNG library of SDL_image
 * 
 * @return 0 on succes; 1 if the init. of the video subsystem failed; 2 if the init of the PNG library of SDL_image failed
 */
int utils::initSDL()
{
	SDL_SetMainReady();
	
	if (SDL_Init(SDL_INIT_VIDEO)) 
	{
		std::cout << "SDL_INIT_VIDEO has failed. Error:" << SDL_GetError() << std::endl;
		return(1);
	}
	if (!(IMG_Init(IMG_INIT_PNG))) 
	{
		std::cout << "IMG_INIT_PNG has failed. Error:" << SDL_GetError() << std::endl;
		return(2);
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
	SDL_Texture* texture {nullptr};
	texture = IMG_LoadTexture(p_renderer, p_filePath);
	if (!texture)
		std::cout << "Could not load Texture. Error: " << SDL_GetError() << std::endl;
	else
		std::cout << "Texture loaded: " << p_filePath << std::endl;
	return(texture);
}


/**
 * @sa utils.hpp
 * @sa Test::utils_collision_PointVsRect()
 */

bool utils::collision_PointVsRect(SDL_FPoint* point, SDL_FRect* rect)
{
	return(	((point->x > rect->x) && (point->x < (rect->x + rect->w)) 
			&& (point->y > rect->y) && (point->y < (rect->y + rect->h))) ? true : false	);
}


/**
 * @brief Checks from which direction the collision of two GameObjects is happening and accordingly adjusts the position and the vector of the p_dynamicGameObject
 * 
 * TODO: In mehrere Parts aufteilen damit mehrere Teile des Programms die Funktion besser nutzen können (der Slime z.B.)
 * 
 * @param p_dynamicGameObject GameObject which collides with p_staticGameObject
 * @param p_collisionPoint    Outer Points of the collision rectangle of both GameObjects that that intersect with the collision rectangle of the other GameObject
 * @param p_staticGameObject  GameObject that the p_dynamicGameObject collides with
 * @return Returns a bool. True if the p_dynamicGameObject is on the floor/ground or false if it is not.
 */
bool utils::resolveCollision(GameObject* p_dynamicGameObject, std::vector<SDL_FPoint>* p_collisionPoints, GameObject* p_staticGameObject)
{
	if(!p_dynamicGameObject || !p_staticGameObject || !p_collisionPoints)
	{
		std::cout << "Error: Call to resolveCollision with nullptr\n";
		return(false);
	}

	bool grounded {false};

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

	for(int i = 0; i < static_cast<int>(p_collisionPoints->size()); ++i)
	{
		if(((*p_collisionPoints)[i].x == dOX) && ((*p_collisionPoints)[i].y == dOY))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoints)[i].x == dOX + dOW) && ((*p_collisionPoints)[i].y == dOY))  
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoints)[i].x == dOX) && ((*p_collisionPoints)[i].y == dOY + dOH))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoints)[i].x == dOX + dOW) && ((*p_collisionPoints)[i].y == dOY + dOH))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoints)[i].x == sOX) && ((*p_collisionPoints)[i].y == sOY))
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoints)[i].x == sOX + sOW) && (*p_collisionPoints)[i].y == sOY)
		{
			if((pP[1] + dOH) <= sOY)
				fromAbove = true;
			else
				fromRight = true;
		}
		else if(((*p_collisionPoints)[i].x == sOX) && ((*p_collisionPoints)[i].y == sOY + sOH))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromLeft = true;
		}
		else if(((*p_collisionPoints)[i].x == sOX + sOW) && ((*p_collisionPoints)[i].y == sOY + sOH))
		{
			if(pP[1] >= sOY + sOH)
				fromBelow = true;
			else
				fromRight = true;
		}
		else
		{
			std::cout << "Error: CollisionPoint: " << (*p_collisionPoints)[i].x << ',' << (*p_collisionPoints)[i].y << "is not a point of either object that is colliding...\n";
		}
	}

	/* changes the position of the dO based on the directions it is colliding with the sO */

	if(fromAbove)
	{
		//std::cout << "Collision from above\n";
		p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
		p_dynamicGameObject->setY(sOY - dOH);
		grounded = true;
	}
	if(fromRight)
	{
		//std::cout << "Collision from right\n";
		if(p_dynamicGameObject->getObjectType() == ObjectType::slime)
		{
			p_dynamicGameObject->setVector(-1 * (p_dynamicGameObject->getVector())[0], (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW + 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX + sOW + 0.01);
		}
	}
	if(fromBelow)
	{
		//std::cout << "Collision from below\n";
		p_dynamicGameObject->setVector((p_dynamicGameObject->getVector())[0], 0);
		p_dynamicGameObject->setY(sOY + sOH + 0.01);
	}
	if(fromLeft)
	{
		//std::cout << "Collision from left\n";
		if(p_dynamicGameObject->getObjectType() == ObjectType::slime)
		{
			p_dynamicGameObject->setVector(-1 * (p_dynamicGameObject->getVector())[0], (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW - 0.01);
		}
		else
		{
			p_dynamicGameObject->setVector(0, (p_dynamicGameObject->getVector())[1]);
			p_dynamicGameObject->setX(sOX - dOW - 0.01);
		}
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