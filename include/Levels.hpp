/**
 * @file Levels.hpp
 * @brief All level loading functions.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tiles.hpp"
#include <vector>


namespace levels
{
    /*
    Decides which level to call based on p_level.

    \param p_level
    \param p_renderer needed to load the textures of the level

    \returns A 2D vector filed with tiles which represents the map of p_level.
    */
    std::vector<std::vector<Tile*>>* setUpLevel(int p_level, SDL_Renderer* p_renderer);

    /*
    Set up level 1.

    \param p_renderer needed to load the textures of the level
    */
    std::vector<std::vector<Tile*>>* setUpLevel1(SDL_Renderer* p_renderer);
}
