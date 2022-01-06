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

#include "Camera.hpp"
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



void Level::setUpLevel1()
{
	m_background = utils::loadTexture("../res/backgrounds/defaultbg.png", m_windowToRenderTo.getRenderer());

	std::ifstream level1;
	level1.open("../res/levels/level1.txt", std::ios::in);

	if(!level1.is_open()) throw "COULD_NOT_OPEN_FILE";

	
	SDL_Texture* playerTexture{utils::loadTexture("../res/player/Maincharacter.png", m_windowToRenderTo.getRenderer())};
	SDL_Rect playerSrcRect {0, 0, constants::playerSprite::w, constants::playerSprite::h};


	SDL_Texture* tileTexture = utils::loadTexture("../res/tileset/outlinedSortedTileset.png", m_windowToRenderTo.getRenderer());
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
			case 'P':
				row.push_back(nullptr);
				m_player = new Player(playerTexture, playerSrcRect, utils::createRect(column*constants::tileSprite::wScaled, line*constants::tileSprite::hScaled,
										constants::playerSprite::wScaled, constants::playerSprite::hScaled));
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

	if(!m_player || m_map->empty() || m_enemies->empty()) throw "FAILED_TO_LOAD_LEVEL_1";


	SDL_Rect DefaultCameraMargin = utils::createRect((constants::window::w/2) - (constants::camera::w/2),
									 11*constants::scale*constants::tileSprite::h - constants::camera::h, constants::camera::w, constants::camera::h);

	SDL_Rect MapLimitRect = utils::createRect(0, 0,(*m_map)[0].size() * constants::tileSprite::wScaled, m_map->size() * constants::tileSprite::hScaled);
	//DEBUG
	std::cout << "m_map->size() * constants::tileSprite::wScaled: " << m_map->size() * constants::tileSprite::wScaled << ", " << "(*m_map)[0].size() * constants::tileSprite::hScaled: " << (*m_map)[0].size() * constants::tileSprite::hScaled << '\n';
	
	m_camera = new Camera(DefaultCameraMargin, m_player, MapLimitRect);

	auto offset {m_camera->setUpCameraForBeginningOfLevel()};
	offset->x -= (constants::window::w/2 - constants::camera::w); //? make clearer
	applyOffset(*offset);

	utils::selectTiles(*m_map);

	level1.close();	
}

void Level::applyOffset(const SDL_Point& p_offset)
{
	m_camera->applyOffsetToLimitRect(p_offset);

	if(p_offset.x || p_offset.y)
	{
		for(const std::vector<Tile*>& row : *m_map)
			for(Tile* tile : row)
				if (tile)
				{
					tile->setX(tile->getX() + p_offset.x);
					tile->setY(tile->getY() + p_offset.y);
				}

		for(DynamicGameObject* enemy : *m_enemies)
		{
			enemy->setX(enemy->getX() + p_offset.x);
			enemy->setY(enemy->getY() + p_offset.y);
		}

		

		m_player->setX(m_player->getX() + p_offset.x);
		m_player->setY(m_player->getY() + p_offset.y);
	}
}



void Level::resolveLimitRectCollisions()
{
	resolveLimitRectCollision(m_player);

	for(DynamicGameObject* enemy : *m_enemies)
		resolveLimitRectCollision(enemy);
}

void Level::resolveLimitRectCollision(DynamicGameObject* p_object)
{
	const SDL_Rect& limit = m_camera->getLimitRect();

	if(p_object->getY() < limit.y)
	{
		p_object->setY(limit.y);
		p_object->setVectorY(0.0f);
	}
	else if(p_object->getX() + p_object->getW() > limit.x + limit.w)
	{
		p_object->setX(limit.x + limit.w - p_object->getW());

		if(p_object->getObjectType() == ObjectType::slime)
			p_object->setVectorX(p_object->getVectorX() * -1);
	}
	else if(p_object->getY() + p_object->getH() > limit.y + limit.h)
	{
		p_object->setY(limit.y + limit.h - p_object->getH());
		p_object->setVectorY(0.0f);
	}
	else if(p_object->getX() < limit.x)
	{	
		p_object->setX(limit.x);
		if(p_object->getObjectType() == ObjectType::slime)
			p_object->setVectorX(p_object->getVectorX() * -1);
	}
}	

void Level::renderLevel()
{
	m_windowToRenderTo.render(m_background);

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
	delete m_player;
	m_player = nullptr;

	delete m_camera;
	m_camera = nullptr;

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


