/**
 * @file game.cpp
 * @brief Definitions of all functions in the "Game" namespace.
 * @see Game.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Game.hpp"

#include "KeyboardState.hpp"
#include "Utils.hpp"
#include <iostream>
#include <SDL.h>

void Game::handleInput(Player& p_player, GameState& p_gameState)
{
    static SDL_Event event;
	static KeyboardState keyboardState;

	while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case (SDL_QUIT):
					p_gameState.gameRunning = false;
				case (SDL_KEYDOWN):
					switch(event.key.keysym.sym)
					{
						case(SDLK_a):
							p_player.setXVelocityGoal(-1);
							p_player.setSrc(utils::createRect(constants::playerSprite::w, 0, constants::playerSprite::w, constants::playerSprite::h));
							break;
						case(SDLK_d):
							p_player.setXVelocityGoal(1);
							p_player.setSrc(utils::createRect(0, 0, constants::playerSprite::w, constants::playerSprite::h));
							break;
						case(SDLK_l):
							if(!keyboardState.lPressed)
							{
								p_player.setMass(0.5*p_player.getMass());
								keyboardState.lPressed = true;
							}
							break;
						case(SDLK_h):
							if(!keyboardState.hPressed)
							{
								p_player.setMass(2*p_player.getMass());
								keyboardState.hPressed = true;
							}
							break;
						case(SDLK_SPACE):
							int currentAmountOfJumps = p_player.getAmountOfJumps();
							if(currentAmountOfJumps > 0)
							{
								p_player.jump();
								p_player.setAmountOfJumps(currentAmountOfJumps - 1);
							}
							break;
					}	
					break;
				case (SDL_KEYUP):
					switch(event.key.keysym.sym)
					{
						case(SDLK_a):
							if(p_player.getXVelocityGoal() < 0)
								p_player.setXVelocityGoal(0);
							break;
						case(SDLK_d):
							if(p_player.getXVelocityGoal() > 0)
								p_player.setXVelocityGoal(0);
							break;
						case(SDLK_h):
							p_player.setMass(0.5*p_player.getMass());
							keyboardState.hPressed = false;
							break;
						case(SDLK_l):
							p_player.setMass(2*p_player.getMass());
							keyboardState.lPressed = false;
							break;
					}
			}
		}
}



void Game::update(Level& p_level, float p_elapsedTimeInSeconds, GameState& p_gameState)
{
	Player& p_player = p_level.getPlayer();
	Camera& p_camera = p_level.getCamera();
	auto& p_map = p_level.getMap();
	auto& p_enemies = p_level.getEnemies();

	if(p_map.empty())
		throw "MAP_EMPTY";

	p_player.update(p_elapsedTimeInSeconds);

	for(DynamicGameObject* enemy : p_enemies)
		if(enemy->isAlive())
			enemy->update(p_elapsedTimeInSeconds);

	//Collision
	p_player.isGrounded(false);

	for(DynamicGameObject* enemy : p_enemies)
		if(enemy->isAlive())
			p_player.handleCollision(enemy);


	int amountOfEnemies = static_cast<int>(p_enemies.size());

	for(int i {0}; i < amountOfEnemies - 1; ++i)
	{	
		if(!p_enemies[i]->isAlive()) continue;

		for(int j {i+1}; j < amountOfEnemies; ++j)
		{
			if(!p_enemies[j]->isAlive()) continue;
			p_enemies[i]->handleCollision(p_enemies[j]);
		}
	} 

	for(std::vector<Tile*>& row : p_map)
		for(Tile* tile : row)
		{
			if(!tile) continue;

			p_player.handleCollision(tile);

			for(DynamicGameObject* enemy : p_enemies)
				if(enemy)
					if(enemy->isAlive())
						enemy->handleCollision(tile);
		}


	
	if(!p_player.isAlive())
	{
		if(p_gameState.gameRunning)
		{
			p_gameState.gameRunning = false;
			p_gameState.deathScreen = true;
		}
	}

	if(p_player.isGrounded())
		p_player.setAmountOfJumps(constants::maxAmountOfJumps);
	else if(p_player.getAmountOfJumps() == constants::maxAmountOfJumps)
		p_player.setAmountOfJumps(constants::maxAmountOfJumps -1);
	

	p_level.resolveLimitRectCollisions();

	//CAMERA

	if(!p_camera.hasToTrack()) return; 
	else p_camera.beginToTrack();

	auto offsetToApply {p_camera.trackObject()};

	p_level.applyOffset(*offsetToApply);
}