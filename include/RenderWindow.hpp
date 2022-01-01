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

#include "GameObject.hpp"
#include "Menu.hpp"
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

	SDL_Renderer* getRenderer();

	void render(SDL_Texture* p_texture);
	void render(GameObject* p_object);
	void render(Menu* p_menu);

	void display();	
	void clear();
	
	void cleanup();

private:

	SDL_Window* m_window {nullptr};
	SDL_Renderer* m_renderer {nullptr};
};