/**
 * @file main.cpp
 * @brief The main function.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Camera.hpp"
#include "Constants.hpp"
#include "DynamicGameObject.hpp"
#include "FrameStatistics.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Slime.hpp"
#include "Tests.hpp"
#include "Tile.hpp"
#include "Utils.hpp"
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
 * !@bug minor: falling in hole with specific level -> Camera is a bit off and does a jump idk why
 * !sprites have to be in the bottom left corner !!! is there a fix for this ?
 * 
 * TODO: make the camera track smooth + make margin on player at the beginning of the level then if he moves either direction make margin slowly into the center (have fun doing this ;) )
 * TODO: clean up gameobject hierarchy, make functions virtual, make destructors to prevent memory leak, etc...
 * TODO: clean up Level class, WERE HOLDING A POINTER TO WINDOW SO TECHNICALLY WE COULD DELETE IT we're getting a non const pointer from a const mem func of renderWindow, could be undefined behaviour if used incorrectly!!!!!!
 * TODO: make animations
 * TODO: make function to add smth to X/Y (GameObject) so that I dont have to set everytime + use that in update functions
 * TODO: make an offset var in GameObject to hold the value of dst.h - collR.h or smth like that
 * TODO: rewrite GameObject::GameObject() so that one can do the textures in every corner
 * TODO: draw better tileSet sprites, make PlayerAnimations, and make a background
 * TODO: REFACTORING
 */
int main(int argc, char* argv[])
{
	try{

	if (utils::initSDL())
	{
		std::cout << "Initialization failed" << std::endl;
		return(1);
	}	
	else
		std::cout << "Initialization complete" << std::endl;

	RenderWindow window("JumpyMagician.exe", constants::window::w, constants::window::h);

	std::cout << "Window loaded succesfully!\n";

	GameState gameState;

	Level level(window);

	std::cout << "Level created succesfully!\n";

	int currentLevel {1};

	level.setUpLevel(currentLevel);

	std::cout << "Loaded level " << currentLevel << " succesfully!\n";

	float currentFrameTimeInSeconds{static_cast<float>(SDL_GetTicks()) * 0.001f};
	float previousFrameTimeInSeconds{0.0f};
	float elapsedTimeInSeconds {0.0f};
	FrameStatistics frameStatistics;

	std::cout << "Loading time: " << (static_cast<float>(SDL_GetTicks()) * 0.001f) << " seconds\n";

	while (gameState.gameRunning) 
	{
		previousFrameTimeInSeconds = currentFrameTimeInSeconds;
		currentFrameTimeInSeconds = static_cast<float>(SDL_GetTicks()) * 0.001f;
		elapsedTimeInSeconds = currentFrameTimeInSeconds - previousFrameTimeInSeconds; 

		frameStatistics.addFrameTime(elapsedTimeInSeconds);
		if(frameStatistics.getNumberOfFrameTimes() > 1000)
		{
			frameStatistics.printAverageFrameTime();
			frameStatistics.reset();
		}

		Game::handleInput(level.getPlayer(), gameState);

		Game::update(level, elapsedTimeInSeconds, gameState);

		window.clear();

		level.renderLevel();
		window.display();
	}

	SDL_Texture* deathScreenTexture = utils::loadTexture("../res/menus/deathScreen.png", window.getRenderer());
	Menu deathScreenMenu(deathScreenTexture);

	SDL_Event deathScreenEvent;

	while (gameState.deathScreen)
	{
		while (SDL_PollEvent(&deathScreenEvent)) 
		{
			switch (deathScreenEvent.type)
			{
				case (SDL_QUIT):
					gameState.deathScreen = false;
					break;
			}
		}

		window.clear();
		window.render(&deathScreenMenu);
		window.display();
	}

	frameStatistics.printAverageFrameTime();

	window.cleanup();
	SDL_Quit();

	}
	catch(const char* error)
	{
		std::cerr << "Error: " << error << '\n';
	}
	catch(const std::string& error)
	{
		std::cerr << "Error: " << error << '\n';
	}

	return(0);
}
