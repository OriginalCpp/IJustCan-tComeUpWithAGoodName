#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include <SDL.h>
#include <iostream>

RenderWindow::RenderWindow()
{}


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(nullptr), renderer(nullptr)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_FULLSCREEN);
	if (!window)
		std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		std::cout << "Renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
}


SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}


void RenderWindow::render(GameObject* p_object) 
{
	SDL_Texture* tex {nullptr};
	tex = p_object->getTexture();
	SDL_Rect src = p_object->getSrc();
	SDL_Rect dst = p_object->getDst();

	//DEBUG
	if(p_object->getObjectType() == ObjectType::slime)
		std::cout << "dst in RenderWindow::render(): " << dst.x << ", " << dst.y << ", " << dst.w << ", " << dst.h << '\n';

	SDL_RendererFlip flip = p_object->getFlip();
	if(flip == SDL_FLIP_NONE)
		SDL_RenderCopy(renderer, tex, &src, &dst);
	else
		SDL_RenderCopyEx(renderer, tex, &src, &dst, 0, nullptr, flip);
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
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
