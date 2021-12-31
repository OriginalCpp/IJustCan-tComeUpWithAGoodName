/**
 * @file levels.cpp
 * @brief Definitions of all functions of the Level class.
 * @see Level.hpp for more documentation.
 * @version 1.0
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Level.hpp"

#include "Constants.hpp"
#include "DynamicGameObject.hpp"
#include "Player.hpp"
#include "Slime.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <vector>

Level::Level(RenderWindow& p_window)
	:m_map{new std::vector<std::vector<Tile*>>}, m_enemies{new std::vector<DynamicGameObject*>}, m_windowToRenderTo{p_window}
{
	if(!m_map || !m_enemies) throw "LEVEL(): BAD_ALLOC";
}

Level::~Level()
{
	delete m_player;

	delete m_camera;

	for(std::vector<Tile*>& row : *m_map)
		for(Tile*& tile : row)
			delete tile;

	for(DynamicGameObject*& enemy: *m_enemies)
		delete enemy;
}



void Level::setUpLevel(int p_level)
{
	try
	{
		if(!m_map->empty() && !m_enemies->empty())
			throw "LEVEL_NOT_CLEARED";

		switch(p_level)
		{
			case 1:
				setUpLevel1();
				break;
			default:
				throw "UNKNOWN_LEVEL";
		}
	}
	catch(const char* error)
	{
		std::cerr << "setUpLevel(): " << error << '\n';
	}
}



void Level::setUpLevel1()
{
	std::ifstream level1;
	level1.open("../res/levels/level1.txt", std::ios::in);

	if(!level1.is_open()) throw "COULD_NOT_OPEN_FILE";

	SDL_Rect playerSrcRect {0, 0, constants::playerSprite::w, constants::playerSprite::h};
	SDL_Rect playerDstRect {100, 100, playerSrcRect.w*constants::scale, playerSrcRect.h*constants::scale};
	SDL_Texture* playerTexture{utils::loadTexture("../res/player/MCSpriteSheet.png", m_windowToRenderTo.getRenderer())};
	m_player = new Player(playerTexture, playerSrcRect, playerDstRect);

	m_camera = new Camera(utils::createFRect((constants::window::w/2) - (constants::camera::w/2), 10*constants::scale*constants::tileSprite::h - constants::camera::h, 
				  		  constants::camera::w, constants::camera::h), m_player);


	SDL_Texture* tileTexture = utils::loadTexture("../res/tileset/sortedTileset.png", m_windowToRenderTo.getRenderer());
	SDL_Rect standardTileSrcRect {0, 0, constants::tileSprite::w, constants::tileSprite::h};
	SDL_Texture* slimeTexture = utils::loadTexture("../res/enemies/greenslime.png", m_windowToRenderTo.getRenderer());
	SDL_Rect slimeSrcRect{0, 0, 16, 16};
	SDL_FRect slimeHitBox{0, 0, 16*constants::scale, 10*constants::scale};

	char bit {};
	int line {0};
	std::vector<Tile*> row;
	int column {0};

	while(level1.get(bit))
	{
		switch(bit)
		{
			case '\n':
				m_map->push_back(row);
				row.clear();
				++line;
				column = 0;
				continue;
				break;
			case '0':
				row.push_back(nullptr);
				break;
			case '1':
				row.push_back(new Tile(tileTexture, standardTileSrcRect
							, utils::createRect(column*constants::tileSprite::wScaled
							, line*constants::tileSprite::hScaled, constants::tileSprite::wScaled, constants::tileSprite::hScaled)));
				break;
			case 'S':
				row.push_back(nullptr);
				m_enemies->push_back(new Slime(slimeTexture, slimeSrcRect
									, utils::createRect(column*constants::tileSprite::wScaled
									, line*constants::tileSprite::hScaled, constants::slimeSprite::wScaled, constants::slimeSprite::hScaled), slimeHitBox));
				break;
			case 's':
				row.push_back(nullptr);
				m_enemies->push_back(new Slime(slimeTexture, slimeSrcRect
									, utils::createRect(column*constants::tileSprite::wScaled
									, line*constants::tileSprite::hScaled, constants::slimeSprite::wScaled, constants::slimeSprite::hScaled), slimeHitBox, 1));
				break;
			default:
				throw "CANNOT_INTERPRET_UNKNOWN_CHAR";
		}

		++column;
	}

	utils::selectTiles(*m_map);

	level1.close();	
}



void Level::renderLevel()
{
	for (std::vector<Tile*> row : *m_map) 
			for(Tile* tile : row)
				if(tile)
					m_windowToRenderTo.render(tile);

	for(DynamicGameObject* enemy : *m_enemies)
		if(enemy)
			if(enemy->isAlive())
				m_windowToRenderTo.render(enemy);

	m_windowToRenderTo.render(m_player);
}

void Level::clearLevel()
{
	for(std::vector<Tile*>& row : *m_map)
		for(Tile*& tile : row)
			delete tile;

	m_map->clear();

	for(DynamicGameObject*& enemy: *m_enemies)
		delete enemy;

	m_enemies->clear();
}


Player& Level::getPlayer()
{
	return *m_player;
}


Camera& Level::getCamera()
{
	return *m_camera;
}



std::vector<std::vector<Tile*>>& Level::getMap() 
{
	return *m_map;
}



std::vector<DynamicGameObject*>& Level::getEnemies()
{
	return *m_enemies;
}