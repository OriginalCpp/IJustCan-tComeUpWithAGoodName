#pragma once
#include "GameObject.hpp"
#include <SDL.h>

enum class TileType
{
    grass,
};

/**
 * @brief represents a tile in the game
 */

class Tile :public GameObject
{
    bool collidable {};
    TileType type{};
public:
    Tile(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, TileType p_type = TileType::grass, bool p_collidable = true);
};