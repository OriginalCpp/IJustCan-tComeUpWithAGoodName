#pragma once
#include "GameObject.hpp"
#include "Tiles.hpp"
#include "Player.hpp"
#include <vector>


namespace levels
{
    std::vector<std::vector<Tile*>>* setUpLevel(int p_level, SDL_Renderer* p_renderer);
    std::vector<std::vector<Tile*>>* setUpLevel1(SDL_Renderer* p_renderer);
}
