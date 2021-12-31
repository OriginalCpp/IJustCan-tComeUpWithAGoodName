/**
 * @file Slime.hpp
 * @brief The Slime class.
 * @see DynamicGameObject.hpp
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "DynamicGameObject.hpp"

#include "StaticGameObject.hpp"
#include <SDL.h>


class Slime :public DynamicGameObject
{
public:

    /* \param p_vectorX The direction in which the slime will move upon creation */
    Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect = {0, 0, 0, 0}, float p_vectorX = -1);
    
    void update(float p_elapsedTimeInSeconds);

    void resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, const StaticGameObject* const p_staticGameObject);
    void resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_dynamicGameObject);

    void jump();
    void die();
};