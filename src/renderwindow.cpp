#include "RenderWindow.hpp"

#include "GameObject.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>

RenderWindow::RenderWindow()
{}


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:m_window(nullptr), renderer(nullptr)
{
	m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_FULLSCREEN);
	if (!m_window)
		std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
	
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		std::cout << "Renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
}


SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}


void RenderWindow::render(GameObject* p_object) 
{
	if(!utils::isInWindow(p_object))
		return;

	SDL_Texture* tex {nullptr};
	tex = p_object->getTexture();
	
	const SDL_Rect* src = p_object->getSrc();
	const SDL_Rect* dst = p_object->getDst();
	const SDL_RendererFlip* flip = p_object->getFlip();
	
	if(*flip == SDL_FLIP_NONE)
		SDL_RenderCopy(renderer, tex, src, dst);
	else
		SDL_RenderCopyEx(renderer, tex, src, dst, 0, nullptr, *flip);
}


void RenderWindow::display() 
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::clear() 
{
	SDL_RenderClear(renderer);
}

void RenderWindow::cleanup() 
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(renderer);
}
