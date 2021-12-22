#pragma once
#include <SDL.h>

namespace Test
{
    /**
     * @brief Test utils::collision_PointVsRect().
     * 
     * @sa utils::collision_PointVsRect()
     */
    void utils_collision_PointVsRect();

    /**
     * @brief Test GameObject::GameObject().
     * 
     * @sa GameObject::GameObject()
     * 
     * @param p_renderer A renderer which is needed to call utils::loadTexture().
     */
    void GameObject_Constructor(SDL_Renderer* p_renderer);

    /**
     * @brief Test GameObject::setX()
     * 
     * @sa GameObject::setX()
     */
    void GameObject_setXgetX(SDL_Renderer* p_renderer);
}