/**
 * @file Tests.hpp
 * @brief All test functions.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <SDL.h>

namespace test
{
    /**
     * @brief Test utils::isPointInRect().
     * 
     * @sa utils::isPointInRect()
     */
    void utils_isPointInRect();

    /**
     * @brief Test utils::getIntersectionCornerFPoints().
     * 
     * @sa utils::getIntersectionCornerFPoints()
     */
    void utils_getIntersectionCornerFPoints();

    /**
     * @brief Test GameObject::GameObject().
     * 
     * @sa GameObject::GameObject()
     * 
     * @param p_renderer A renderer which is needed to call utils::loadTexture().
     */
    void GameObject_Constructor(SDL_Renderer* p_renderer);

    /**
     * @brief Test GameObject::setX() and GameObject::getX()
     * 
     * @sa GameObject::setX()
     */
    void GameObject_setXgetX(SDL_Renderer* p_renderer);
}