#pragma once
#include "GameObject.hpp"
#include "Tiles.hpp"
#include "Player.hpp"
#include <vector>


namespace levels
{
    bool setUpLevel(int p_level, Player& p_player, std::vector<std::vector<Tile*>>& p_tiles, SDL_Renderer* p_renderer);
    bool setUpLevel1(Player& p_player, std::vector<std::vector<Tile*>>& p_tiles, SDL_Renderer* p_renderer);
}
