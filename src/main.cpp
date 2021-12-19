#include "RenderWindow.hpp"
#include "utils.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Slime.hpp"
#include "Tiles.hpp"
#include "Camera.hpp"
#include "Levels.hpp"
#include "Globals.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


/**
 * @brief initialization + game loop 
 * 
 * ? class for vectors in objects so that you can overload the operators for vector arithmetics ?
 * 
 * !@bug collision: if standing next to a two tiles tall tile thats not on the ground and pressing a direction you cannot jump
 * 
 * TODO: test if you can remove the + 0.01 in resolveCollision without sticking to ceilings
 * TODO: refactor big portions of code in the GameLoop
 * TODO: draw better tileSet sprites, make PlayerAnimations, an enemy, and make a background
 * TODO: delete all objects in tiles after a level is completed/game exits to prevent memory leak
 */

int main(int argc, char* argv[])
{

	if (utils::initSDL())
	{
		std::cout << "Initialization failed" << std::endl;
		return(1);
	}	
	else
		std::cout << "Initialization complete" << std::endl;
	


	bool gameRunning {true};
	int level {1};

	RenderWindow window("JumpyMagician", constants::window::w, constants::window::h);

	

	Player player(utils::loadTexture("../res/player/MCSpriteSheet.png", window.getRenderer()), utils::createRect(0, 0, constants::playerSprite::w, constants::playerSprite::h)
				  , utils::createRect(100, 100, constants::playerSprite::w*constants::scale, constants::playerSprite::h*constants::scale));

	Camera camera(utils::createFRect((constants::window::w/2) - (constants::camera::w/2), 10*constants::scale*constants::tileSprite::h - constants::camera::h
				  , constants::camera::w, constants::camera::h), &player);

	Slime larry(utils::loadTexture("../res/enemies/greenslime.png", window.getRenderer()), utils::createRect(0, 0, 16, 16), utils::createRect(1100, 600, 64, 64));

	std::vector<std::vector<Tile*>>* tiles = levels::setUpLevel(level, window.getRenderer());

	if (!tiles)
	{
		std::cout << "Error: levels::setUpLevel() failed\n Could not load level " << level << "\n";
		return(1);
	}
	else
		std::cout << "Level " << level << " was loaded succesfully!\n";


	SDL_Event event;
	float dt {};
	std::vector<std::vector<float>>* collisionPoints {nullptr};
	int playerSpeed {400};
	int amountOfJumps {constants::maxAmountOfJumps};
	bool grounded {};
	float* offsetToApply {nullptr};
	float currentFrameTime{static_cast<float>(SDL_GetTicks())/1000};
	float previousFrameTime{};

	while (gameRunning) 
	{
		previousFrameTime = currentFrameTime;
		currentFrameTime = static_cast<float>(SDL_GetTicks())/1000;
		dt = currentFrameTime - previousFrameTime; 

		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case (SDL_QUIT):
					gameRunning = false;
					break;
				case (SDL_KEYDOWN):
					switch(event.key.keysym.sym)
					{
						case(SDLK_a):
							player.setGoalX(-1);
							player.setSrc(utils::createRect(0, constants::playerSprite::h, constants::playerSprite::w, constants::playerSprite::h));
							break;
						case(SDLK_d):
							player.setGoalX(1);
							player.setSrc(utils::createRect(0, 0, constants::playerSprite::w, constants::playerSprite::h));
							break;
						case(SDLK_SPACE):
							if(amountOfJumps > 0)
							{
								player.setVector((player.getVector())[0], -1000);
								--amountOfJumps;
							}
							break;
					}	
					break;
				case (SDL_KEYUP):
					switch(event.key.keysym.sym)
					{
						case(SDLK_a):
							if(player.getGoalX() < 0)
								player.setGoalX(0);
							break;
						case(SDLK_d):
							if(player.getGoalX() > 0)
								player.setGoalX(0);
							break;
					}
			}
		}

		player.move(dt, playerSpeed);
		larry.move(dt);

		grounded = false;
		
		for(int i = 0; i < static_cast<int>(tiles->size()); i++)
		{
			for(int j = 0; j < static_cast<int>((*tiles)[0].size()); ++j)
			{
				collisionPoints = player.detectCollision((*tiles)[i][j]);
				if(collisionPoints)
				{
					if (utils::resolveCollision(&player, collisionPoints, (*tiles)[i][j]))
				 	{
						amountOfJumps = constants::maxAmountOfJumps;
			 			grounded = true;
			 		}
					delete collisionPoints;
					collisionPoints = nullptr;
				}
				collisionPoints = larry.detectCollision((*tiles)[i][j]);
				if(collisionPoints)
				{
					utils::resolveCollision(&larry, collisionPoints, (*tiles)[i][j]);
					delete collisionPoints;
					collisionPoints = nullptr;
				}
			}
		}

		if(!grounded)
		{
			if(amountOfJumps == constants::maxAmountOfJumps)
			{
				--amountOfJumps;
			}
		}

		camera.hasToTrack();
		offsetToApply = camera.trackObject();
		if(offsetToApply)
		{
			for(int i = 0; i < static_cast<int>(tiles->size()); ++i)
			{
				for(int j = 0; j < static_cast<int>((*tiles)[0].size()); ++j)
				{
					if ((*tiles)[i][j])
					{
						(*tiles)[i][j]->setX((*tiles)[i][j]->getX() + offsetToApply[0]);
						(*tiles)[i][j]->setY((*tiles)[i][j]->getY() + offsetToApply[1]);
					}
				}
			}
			larry.setX(larry.getX() + offsetToApply[0]);
			larry.setY(larry.getY() + offsetToApply[1]);
			player.setX(player.getX() + offsetToApply[0]);
			player.setY(player.getY() + offsetToApply[1]);
			delete offsetToApply;
			offsetToApply = nullptr;
		}

		window.clear();

		for (int i = 0; i < (static_cast<int>(tiles->size())); ++i) 
		{
			for(int j = 0; j < static_cast<int>((*tiles)[0].size()); ++j)
			{
				if((*tiles)[i][j])
				{
					window.render((*tiles)[i][j]);
				}
			}
			
		}
		window.render(&larry);
		window.render(&player);

		window.display();
	}

	window.cleanup();
	SDL_Quit();

	return(0);
}
