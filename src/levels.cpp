#include "Levels.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Globals.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>
#include <vector>

//calls the function fitting for the stage
// 0 = everything went fine
// >0 = something went wrong

bool levels::setUpLevel(int p_level, Player& p_player, std::vector<std::vector<Tile*>>& p_tiles, SDL_Renderer* p_renderer)
{
	switch(p_level)
	{
		case 1:
			if (!setUpLevel1(p_player, p_tiles, p_renderer))
			{
				std::cout << "Error: Level " << p_level << "was not loaded correctly\n";
				return(1);
			}
			else 
				std::cout << "Level " << p_level << " loaded succesfully!\n";
            break;
		default:
			std::cout << "Error: Level does not exist: Level " << p_level << "\n";
            return(1);
	}
    return(0);
}

bool levels::setUpLevel1(Player& p_player, std::vector<std::vector<Tile*>>& p_tiles, SDL_Renderer* p_renderer)
{
	int rows {1280/(16*constants::scale)};
	int columns {2*1920/(16*constants::scale)};
    SDL_Texture* grassTexture = utils::loadTexture("../res/tileset/sortedTileset.png", p_renderer);

	for (int i = 0; i < rows; ++i) 
	{
		std::vector<Tile*>* row = new std::vector<Tile*>;
		if(i >= 12)
		{
			for(int j = 0; j < columns; ++j)
			{
					row->push_back(new Tile(grassTexture, utils::createRect(0, 0, 16, 16), utils::createRect(j*constants::scale*16, i*constants::scale*16, 16*constants::scale, 16*constants::scale)));
			}
		}
		else
		{
			for(int j = 0; j < columns; ++j)
			{
				row->push_back(NULL);
			}
		}
		p_tiles.push_back(*row);
    }

	utils::selectTiles(p_tiles);	

	return(1);
}