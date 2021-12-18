#include "Tiles.hpp"
#include "GameObject.hpp"
#include <SDL.h>


Tile::Tile(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, TileType p_type, bool p_collidable)
    :GameObject(p_texture, p_src, p_dst), collidable{p_collidable}, type{p_type}
{}