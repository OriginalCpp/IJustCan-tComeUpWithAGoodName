/**
 * @file Menu.hpp
 * @brief The Menu class.
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <SDL.h>

/* Will expand in the future! */
class Menu
{
    SDL_Texture* m_texture;

public:

    Menu(SDL_Texture* p_tex);

    SDL_Texture* getTexture() const;
};