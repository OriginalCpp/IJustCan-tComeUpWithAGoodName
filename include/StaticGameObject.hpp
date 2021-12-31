/**
 * @file StaticGameObject.hpp
 * @brief The StaticGameObject class.
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "GameObject.hpp"

#include <SDL.h>

class StaticGameObject : public GameObject
{
public:
    StaticGameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox = {0, 0, 0, 0});
};