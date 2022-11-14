/**
 * @file Tile.hpp
 * @brief The Tile class.
 * @see GameObject.hpp
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "classes/StaticGameObject.hpp"

#include <SDL.h>

enum class TileType
{
    grass,
};

/**
 * @brief represents a tile in the game
 */

class Tile :public StaticGameObject
{
public:

    Tile(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, TileType p_type = TileType::grass, bool p_collidable = true);

private:

    bool collidable {true};

    TileType tileType {TileType::grass};
};