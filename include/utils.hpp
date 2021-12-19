#pragma once
#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tiles.hpp"
#include "Camera.hpp"
#include <SDL.h>
#include <vector>


namespace utils {
	int initSDL();
	SDL_Rect createRect(int p_x, int p_y, int p_width, int p_height);
	SDL_FRect createFRect(float p_x, float p_y, float p_width, float p_height);
	SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* p_renderer);
	bool collision_PointVsRect(float* p_point, SDL_FRect rect);
	bool resolveCollision(GameObject* p_dynamicGameObject, std::vector<std::vector<float>>* p_collisionPoint, GameObject* p_staticGameObject);
	void selectTiles(std::vector<std::vector<Tile*>>& p_tiles);
}