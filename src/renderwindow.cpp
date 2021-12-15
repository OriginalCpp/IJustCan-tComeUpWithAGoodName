#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include <SDL.h>
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //|| SDL_WINDOW_FULLSCREEN);

	if (window == NULL)
		std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		std::cout << "Renderer failed to initialize. Error: " << SDL_GetError() << std::endl;
}

void RenderWindow::cleanup() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(GameObject* p_object) 
{
	SDL_Texture* tex = NULL;
	tex = p_object->getTexture();
	SDL_Rect src = p_object->getSrc();
	SDL_Rect dst = p_object->getDst();
	SDL_RenderCopy(renderer, tex, &src, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}
