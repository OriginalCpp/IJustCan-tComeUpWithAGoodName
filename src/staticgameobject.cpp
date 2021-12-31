/**
 * @file staticgameobject.cpp
 * @brief Definitions of all function of the StaticGameObject class.
 * @see StaticGameObject.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "StaticGameObject.hpp"

StaticGameObject::StaticGameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox)
    :GameObject(p_texture, p_src, p_dst, p_hitbox)
{}