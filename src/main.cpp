#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tiles.hpp"
#include "utils.hpp"
#include "Levels.hpp"
#include "Globals.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


int init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_INIT_VIDEO has failed. Error:" << SDL_GetError() << std::endl;
		return(1);
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "IMG_INIT_PNG has failed. Error:" << SDL_GetError() << std::endl;
		return(1);
	}	
	return(0);
}


int main(int argc, char* argv[])
{
	if (init())
		std::cout << "Initialization failed" << std::endl;
	else
		std::cout << "Initialization complete" << std::endl;
	
	RenderWindow window("JumpyMagician", 1920, 1280);

	bool gameRunning {true};

	int level {1};

	Player player(utils::loadTexture("../res/player/maincharacter.png", window.getRenderer()), utils::createRect(0,0,16, 23), utils::createRect(200, 200, 16*constants::scale, 23*constants::scale));
	std::vector<std::vector<Tile*>> tiles;
	if (levels::setUpLevel(level, player, tiles, window.getRenderer()) > 0)
	{
		std::cout << "Error: levels::setUpLevel() failed\n";
		gameRunning = false;
	}

	SDL_Event event;
	float dt {};
	float* collisionPointPtr {NULL};
	int player_speed {350};
	int amountOfJumps {constants::maxAmountOfJumps};
	bool grounded {};
	int gravity {3500};
	float currentFrameTime{static_cast<float>(SDL_GetTicks())/1000};
	float previousFrameTime{};

	while (gameRunning) {
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
							break;
						case(SDLK_d):
							player.setGoalX(1);
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
		player.move(dt, player_speed, gravity);
		grounded = false;
		for(int i = 0; i < (static_cast<int>(tiles.size())); i++)
		{
			for(int j = 0; j < (static_cast<int>(tiles[0].size())); ++j)
			{
				collisionPointPtr = player.detectCollision(tiles[i][j]);
				if(collisionPointPtr != NULL)
				{
					if (utils::resolveCollision(&player, collisionPointPtr, tiles[i][j]))
					{
						amountOfJumps = constants::maxAmountOfJumps;
						grounded = true;
					}
					delete collisionPointPtr;
				}
				collisionPointPtr = NULL;
			}
			
			
		}
		if(!grounded)
		{
			if(amountOfJumps == constants::maxAmountOfJumps)
			{
				--amountOfJumps;
			}
		}
		window.clear();
		for (int i = 0; i < (static_cast<int>(tiles.size())); ++i) 
		{
			for(int j = 0; j < static_cast<int>(tiles[0].size()); ++j)
			{
				if(tiles[i][j] != NULL)
				{
					window.render(tiles[i][j]);
				}
			}
			
		}
		window.render(&player);
		window.display();
	}

	window.cleanup();
	SDL_Quit();
	
	/*for(int i = 0; i < (static_cast<int>(objects.size())); ++i)
	{
		delete objects[i];
	}*/

	return(0);
}
