/**
 * @file RenderWindow.hpp
 * @brief The RenderWindow class.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "classes/GameObject.hpp"
#include "classes/Menu.hpp"
#include <SDL.h>

class RenderWindow 
{
public:

	/*
	Creates a window with a given title, width and height.

	\param p_title
	\param p_w
	\param p_h
	*/
	RenderWindow(const char* p_title, int p_w, int p_h);

	SDL_Renderer* getRenderer() const;

	void render(SDL_Texture* p_texture) const;
	void render(const GameObject& p_object) const;
	void render(const Menu& p_menu) const;

	void display();	
	void clear();
	
	void cleanup();

private:

	SDL_Window* m_window {nullptr};
	mutable SDL_Renderer* m_renderer {nullptr};
};