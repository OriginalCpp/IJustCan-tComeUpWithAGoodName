#include "Camera.hpp"
#include "Constants.hpp"
#include "FrameStatistics.hpp"
#include "GameObject.hpp"
#include "Levels.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Slime.hpp"
#include "Tests.hpp"
#include "Tiles.hpp"
#include "utils.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <vector>



/**
 * @brief Contains the initialization of the game and the game loop.
 * 
 * ? class for (mathematical) vectors in objects so that you can overload the operators for vector arithmetics ?
 * 
 * !sprites have to be in the bottom left corner !!! is there a fix for this ?
 *
 * TODO: refactor resolveCollision()
 * TODO: make all the functions which return non fundamental times return a pointer
 * TODO: rename private members of a class/struct m_name
 * TODO: const after all member functions where possible
 * TODO: Slime can kill player and player can kill slime 
 * TODO: make camera go smooth
 * TODO: make animations
 * TODO: make function to add smth to X/Y (GAmeObject) so that I dont have to set everytime + use that in move functions
 * TODO: make an offset var in GameObject to hold the value of dst.h - collR.h or smth like that
 * TODO: rewrite GameObject::GameObject() so that one can do the textures in every corner
 * TODO: delete collisionPoints completely
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

	RenderWindow window("JumpyMagician.exe", constants::window::w, constants::window::h);

	SDL_Rect playerSrcRect {0, 0, constants::playerSprite::w, constants::playerSprite::h};
	SDL_Rect playerDstRect {100, 100, playerSrcRect.w*constants::scale, playerSrcRect.h*constants::scale};
	Player player(utils::loadTexture("../res/player/MCSpriteSheet.png", window.getRenderer()), playerSrcRect, playerDstRect);

	Camera camera(utils::createFRect((constants::window::w/2) - (constants::camera::w/2), 10*constants::scale*constants::tileSprite::h - constants::camera::h, 
				  constants::camera::w, constants::camera::h), &player);

	SDL_Rect slimeDstRect{1100, 600, 64, 64};
	SDL_FRect slimeCollisionRect {0, 0, 16*constants::scale, 10*constants::scale};
	Slime larry(utils::loadTexture("../res/enemies/greenslime.png", window.getRenderer()), utils::createRect(0, 0, 16, 16), slimeDstRect, slimeCollisionRect);

	std::vector<std::vector<Tile*>>* tiles = levels::setUpLevel(level, window.getRenderer());

	if (!tiles)
	{
		std::cout << "Error: levels::setUpLevel() failed\n Could not load level " << level << "\n";
		return(1);
	}
	else
		std::cout << "Level " << level << " was loaded succesfully!\n";


	SDL_Event event;
	int amountOfJumps {constants::maxAmountOfJumps};
	bool grounded {false};
	float offsetToApply[2] {0, 0};

	float currentFrameTimeInSeconds{static_cast<float>(SDL_GetTicks())/1000};
	float previousFrameTimeInSeconds{0.0f};
	float elapsedTimeInSeconds {0.0f};
	FrameStatistics frameStatistics;

	std::cout << "Loading time: " << (static_cast<float>(SDL_GetTicks())/1000) << " seconds\n";

	while (gameRunning) 
	{
		previousFrameTimeInSeconds = currentFrameTimeInSeconds;
		currentFrameTimeInSeconds = static_cast<float>(SDL_GetTicks())/1000;
		elapsedTimeInSeconds = currentFrameTimeInSeconds - previousFrameTimeInSeconds; 

		frameStatistics.addFrameTime(elapsedTimeInSeconds);
		if(frameStatistics.getNumberOfFrameTimes() > 100)
		{
			frameStatistics.printAverageFrameTime();
			frameStatistics.reset();
		}

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
								player.jump();
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

		player.move(elapsedTimeInSeconds);
		larry.move(elapsedTimeInSeconds);

		//Collision
		grounded = false;

		for(std::vector<Tile*>& row : (*tiles))
		{
			for(Tile* tile : row)
			{
				if(player.handleCollision(tile))
				{
					amountOfJumps = constants::maxAmountOfJumps;		
					grounded = true;
				}

				larry.handleCollision(tile);
			}
		}	

		if(!grounded && (amountOfJumps == constants::maxAmountOfJumps))
			--amountOfJumps;
		
		//CAMERA
		camera.hasToTrack();
		camera.trackObject(offsetToApply);
		if(offsetToApply[0] || offsetToApply[1])
		{
			for(const std::vector<Tile*>& row : (*tiles))
				for(Tile* tile : row)
					if (tile)
					{
						tile->setX(tile->getX() + offsetToApply[0]);
						tile->setY(tile->getY() + offsetToApply[1]);
					}

			larry.setX(larry.getX() + offsetToApply[0]);
			larry.setY(larry.getY() + offsetToApply[1]);
			player.setX(player.getX() + offsetToApply[0]);
			player.setY(player.getY() + offsetToApply[1]);
		}

		window.clear();

		for (std::vector<Tile*> row : (*tiles)) 
			for(Tile* tile : row)
				if(tile)
					window.render(tile);
		
		window.render(&larry);
		window.render(&player);

		window.display();
	}

	frameStatistics.printAverageFrameTime();

	window.cleanup();
	SDL_Quit();

	return(0);
}
