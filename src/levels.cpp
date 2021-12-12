#include "Levels.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>
#include <vector>

bool levels::setUpLevel(int p_level, Player& p_player, std::vector<GameObject*>& p_objects, SDL_Renderer* p_renderer)
{
	switch(p_level)
	{
		case 1:
			if (setUpLevel1(p_player, p_objects, p_renderer) != 25)
			{
				std::cout << "Error: Level " << p_level << "was not loaded correctly\n";
				return(1);
			}
            break;
		default:
			std::cout << "Error: Level does not exist: Level " << p_level << "\n";
            return(1);
	}
    return(0);
}

int levels::setUpLevel1(Player& p_player, std::vector<GameObject*>& p_objects, SDL_Renderer* p_renderer)
{
    SDL_Texture* grassTexture = utils::loadTexture("../res/tileset/sortedTileset.png", p_renderer);
	for (int i = 0; i < 20; ++i) {
		p_objects.push_back(new GameObject(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(i*64, 450, 64, 64), 64, 64));
    }
	GameObject* theG = new GameObject(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(320, 386, 64, 64), 64, 64);
	GameObject* theG2 = new GameObject(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(640, 324, 64, 64), 64, 64);
	GameObject* theG3 = new GameObject(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(960, 260, 64, 64), 64, 64);
	GameObject* theG4 = new GameObject(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(1024, 260, 64, 64), 64, 64);
    p_objects.push_back(theG);
	p_objects.push_back(theG2);
	p_objects.push_back(theG3);
	p_objects.push_back(theG4);
	p_objects.push_back(&p_player); //player has to be last object in objects!!!!!!   

	return(static_cast<int>(p_objects.size()));
}