/**
 * @file utils.cpp
 * @brief Definitions of all functions in the namespace "utils".
 * @see Utils.hpp for function documentation.
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define SDL_MAIN_HANDLED
#include "Utils.hpp"

#include "Camera.hpp"
#include "GameObject.hpp"
#include "Constants.hpp"
#include "KeyboardState.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
	{
		std::string error {"FAILED_TO_LOAD_TEXTURE"};
		error.append(SDL_GetError());
		throw error;
	}

	return(texture);
}


/**
 * @see test::utils_isPointInRect()
 */
bool utils::isPointInRect(const SDL_FPoint& point, const SDL_FRect& rect)
{
	return( (point.x >= rect.x) && (point.x <= (rect.x + rect.w))
			&& (point.y >= rect.y) && (point.y <= (rect.y + rect.h)));
}

bool utils::isPointInRect(const SDL_FPoint& point, const SDL_Rect& rect)
{
	return( (point.x >= rect.x) && (point.x <= (rect.x + rect.w))
			&& (point.y >= rect.y) && (point.y <= (rect.y + rect.h)));
}

/**
 * @see test::utils_getIntersectionCornerFPoints()
 */
std::unique_ptr<std::vector<SDL_FPoint>> utils::getIntersectionCornerFPoints(const SDL_FRect* const p_rect1, const SDL_FRect* const p_rect2)
{
	if(!p_rect1 || !p_rect2)
		return nullptr;

	SDL_FPoint rect1Points[4]{	{p_rect1->x, p_rect1->y},
								{p_rect1->x + p_rect1->w, p_rect1->y},
								{p_rect1->x + p_rect1->w, p_rect1->y + p_rect1->h},
								{p_rect1->x, p_rect1->y + p_rect1->h}};
	
	SDL_FPoint rect2Points[4]{	{p_rect2->x, p_rect2->y},
								{p_rect2->x + p_rect2->w, p_rect2->y},
								{p_rect2->x + p_rect2->w, p_rect2->y + p_rect2->h},
								{p_rect2->x, p_rect2->y + p_rect2->h}};
	
	std::unique_ptr<std::vector<SDL_FPoint>> intersectionCornerFPoints {std::make_unique<std::vector<SDL_FPoint>>()};

	for(const SDL_FPoint& point : rect1Points)
	{
		if(utils::isPointInRect(point, *p_rect2))
			intersectionCornerFPoints->push_back(point);
	}

	for(const SDL_FPoint& point : rect2Points)
	{
		if(utils::isPointInRect(point, *p_rect1))
			intersectionCornerFPoints->push_back(point);
	}

	if(intersectionCornerFPoints->empty())
		return(nullptr);

	return(intersectionCornerFPoints);
}


/**
 * @brief checks for each tile for adjancent tiles and then sets the texture(s) so that the tiles match
 * 
 * @param p_tiles 
 */

void utils::selectTiles(std::vector<std::vector<Tile*>>& p_tiles)
{
	int rowCount {static_cast<int>(p_tiles.size())};
	int columnCount {static_cast<int>(p_tiles[0].size())};

	for(int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
	{
		for(int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
		{
			if(!p_tiles[rowIndex][columnIndex])
				continue;
			
			bool& top {p_tiles[rowIndex][columnIndex]->adjancentTiles[0]};
			bool& right {p_tiles[rowIndex][columnIndex]->adjancentTiles[1]};
			bool& below{p_tiles[rowIndex][columnIndex]->adjancentTiles[2]};
			bool& left {p_tiles[rowIndex][columnIndex]->adjancentTiles[3]};

			if (rowIndex > 0)
			{
				if(p_tiles[rowIndex - 1][columnIndex])
					top = true;
			}
			else
				top = true;

			if (columnIndex < columnCount - 1)
			{
				if(p_tiles[rowIndex][columnIndex + 1])
					right = true;
			}
			else
			 	right = true;
	
			if(rowIndex < rowCount - 1)
			{
				if(p_tiles[rowIndex + 1][columnIndex])
					below = true;
			}
			else	
				below = true;

			if(columnIndex > 0)
			{
				if(p_tiles[rowIndex][columnIndex - 1])
					left = true;
			}
			else 
				left = true;


			if(top && right && below && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && below && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && below && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(0, constants::tileSprite::h*3, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right && below)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(below && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(right && below)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(0, constants::tileSprite::h*2, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*3, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && below)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*2, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(top && right)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(left)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(0, constants::tileSprite::h, constants::tileSprite::w, constants::tileSprite::h));
			else if(below)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*3, 0, constants::tileSprite::w, constants::tileSprite::h));
			else if(right)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w*2, 0, constants::tileSprite::w, constants::tileSprite::h));
			else if(top)
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(constants::tileSprite::w, 0, constants::tileSprite::w, constants::tileSprite::h));
			else	
				p_tiles[rowIndex][columnIndex]->setSrc(utils::createRect(0, 0, constants::tileSprite::w, constants::tileSprite::h));
		}
	}
}



bool utils::isInWindow(const GameObject* p_gameObject)
{
	if(!p_gameObject)
		return false;

	return(!((p_gameObject->getX() > constants::window::w) || (p_gameObject->getX() < -constants::largestSpriteWidth) 
			|| (p_gameObject->getY() > constants::window::h) || (p_gameObject->getY() < -constants::largestSpriteHeight)));
}