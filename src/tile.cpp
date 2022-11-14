/**
 * @file tiles.cpp
 * @brief Definitions of all functions of the Tile class.
 * @see Tile.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "classes/Tile.hpp"

#include <SDL.h>


Tile::Tile(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, TileType p_type, bool p_collidable)
    :StaticGameObject(p_texture, p_src, p_dst), collidable{p_collidable}, tileType{p_type}
{
    setObjectType(ObjectType::tile);
}