#pragma once
#include "GameObject.hpp"
#include <SDL.h>

class Tile :public GameObject
{
    bool collidable {};
public:
    Tile(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, bool p_collidable = true);
};