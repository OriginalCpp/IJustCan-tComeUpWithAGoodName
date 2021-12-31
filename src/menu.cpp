/**
 * @file menu.cpp
 * @brief All definitions of functions of the Menu class.
 * @see Menu.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Menu.hpp"

#include <SDL.h>

Menu::Menu(SDL_Texture* p_tex)
    :m_texture{p_tex}
{}

SDL_Texture* Menu::getTexture()
{
    return m_texture;
}