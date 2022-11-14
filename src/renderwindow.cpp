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
#include "classes/RenderWindow.hpp"

#include "classes/GameObject.hpp"
#include "classes/Menu.hpp"
#include "Utils.hpp"
#include <iostream>
#include <SDL.h>
#include <string>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:m_window{nullptr}, m_renderer{nullptr}
{
	m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_FULLSCREEN);
	if (!m_window)
	{
		std::string error {"Window failed to initialize. Error: "};
		error.append(SDL_GetError());
		throw error;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		std::string error {"Renderer failed to initialize. Error: "};
		error.append(SDL_GetError());
		throw error;
	}
}



SDL_Renderer* RenderWindow::getRenderer() const 
{
	return m_renderer;
}


void RenderWindow::render(SDL_Texture* p_texture) const
{
	if(!p_texture) throw "TEX_IS_NULLPTR";
	
	SDL_RenderCopy(m_renderer, p_texture, NULL, NULL);
}

void RenderWindow::render(const GameObject& p_object) const
{
	if(!utils::isInWindow(p_object))
		return;

	SDL_Texture* tex {nullptr};
	tex = p_object.getTexture();

	if(!tex)
		throw "OBJECT_HAS_NO_TEXTURE";
	
	const SDL_Rect* src = p_object.getSrc();
	const SDL_Rect* dst = p_object.getDst();
	const SDL_RendererFlip* flip = p_object.getFlip();
	
	if(*flip == SDL_FLIP_NONE)
		SDL_RenderCopy(m_renderer, tex, src, dst);
	else
		SDL_RenderCopyEx(m_renderer, tex, src, dst, 0, nullptr, *flip);
}

void RenderWindow::render(const Menu& p_menu) const
{
	SDL_Texture* tex{nullptr};
	tex = p_menu.getTexture();

	if(!tex)
		throw "MENU_HAS_NO_TEXTURE";
	
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
