/**
 * @file levels.cpp
 * @brief Definitions of all functions in the levels namespace.
 * @see Levels.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Levels.hpp"

#include "Constants.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include <iostream>
#include <SDL.h>
#include <vector>

std::vector<std::vector<Tile*>>* levels::setUpLevel(int p_level, SDL_Renderer* p_renderer)
{
	switch(p_level)
	{
		case 1:
			return(setUpLevel1(p_renderer));
            break;
		default:
			std::cout << "Error: Level does not exist: Level " << p_level << "\n";
            return(nullptr);
	}
}



std::vector<std::vector<Tile*>>* levels::setUpLevel1(SDL_Renderer* p_renderer)
{
	int rows {constants::window::h/(constants::tileSprite::h*constants::scale)};
	int columns {6*(constants::window::w/(constants::tileSprite::w*constants::scale))};

	std::vector<std::vector<Tile*>>* tiles = new std::vector<std::vector<Tile*>>(rows, std::vector<Tile*>(columns, nullptr));

    SDL_Texture* grassTexture = utils::loadTexture("../res/tileset/sortedTileset.png", p_renderer);
	SDL_Rect tileSrcRect {0, 0, constants::tileSprite::w, constants::tileSprite::h};


	for (int i = 0; i < rows; ++i) 
	{
		switch(i)
		{
			case 8:
				for(int j = 13; j < 15; ++j)
				{
					tiles->at(i).at(j) = new Tile(grassTexture, tileSrcRect, utils::createRect(j*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				}
				break;	
			case 9:
				tiles->at(i).at(10) = new Tile(grassTexture, tileSrcRect
										  	  , utils::createRect(10*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				for(int j = 13; j < 15; ++j)
				{
					tiles->at(i).at(j) = new Tile(grassTexture, tileSrcRect
										  	  , utils::createRect(j*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				}
				break;
			case 10:
				tiles->at(i).at(7) = new Tile(grassTexture, tileSrcRect
										  	  , utils::createRect(7*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				tiles->at(i).at(30) = new Tile(grassTexture, tileSrcRect
										  	  , utils::createRect(30*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				break;
			case 11:
				for (int j = 5; j < columns; ++j)
				{
					tiles->at(i).at(j) = new Tile(grassTexture, tileSrcRect
										  	  , utils::createRect(j*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
				}	
				break;
			default:
				if(i >= 12)
				{
					for(int j = 0; j < columns; ++j)
					{
							tiles->at(i).at(j) = new Tile(grassTexture, tileSrcRect
										  			  , utils::createRect(j*constants::scale*constants::tileSprite::w, i*constants::scale*constants::tileSprite::h
										  		 	  , constants::tileSprite::w*constants::scale, constants::tileSprite::h*constants::scale));
					}
				}
				break;	
		}
    }

	utils::selectTiles(*tiles);	

	return(tiles);
}