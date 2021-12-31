/**
 * @file renderwindow.cpp
 * @brief Definitions of all functions of the RenderWindow class.
 * @see RenderWindow.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "RenderWindow.hpp"

#include "GameObject.hpp"
#include "Menu.hpp"
#include "Utils.hpp"
#include <SDL.h>
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:m_window{nullptr}, m_renderer{nullptr}
{
	m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_FULLSCREEN);
	if (!m_window)
	{
		std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		std::cout << "Renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
		return;
	}
}



SDL_Renderer* RenderWindow::getRenderer()
{
	return m_renderer;
}

void RenderWindow::render(GameObject* p_object)
{
	if(!utils::isInWindow(p_object))
		return;

	SDL_Texture* tex {nullptr};
	tex = p_object->getTexture();

	if(!tex)
		throw "TEX_NOT_LOADED";
	
	const SDL_Rect* src = p_object->getSrc();
	const SDL_Rect* dst = p_object->getDst();
	const SDL_RendererFlip* flip = p_object->getFlip();
	
	if(*flip == SDL_FLIP_NONE)
		SDL_RenderCopy(m_renderer, tex, src, dst);
	else
		SDL_RenderCopyEx(m_renderer, tex, src, dst, 0, nullptr, *flip);
}

void RenderWindow::render(Menu* p_menu)
{
	SDL_Texture* tex{nullptr};

	tex = p_menu->getTexture();

	SDL_RenderCopy(m_renderer, tex, NULL, NULL);
}



void RenderWindow::display() 
{
	SDL_RenderPresent(m_renderer);
}

void RenderWindow::clear() 
{
	SDL_RenderClear(m_renderer);
}



void RenderWindow::cleanup() 
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}
