#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include <SDL.h>
#include <vector>


namespace utils {
	SDL_Rect createRect(int p_x, int p_y, int p_width, int p_height);
	bool collision_PointVsRect(float* p_point, float* p_rectOrigin, int p_rectWidth, int p_rectHeight);
	bool resolveCollision(Player* p_dynamicGameObject, float* p_collisionPoint, GameObject* p_staticGameObject);
	SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* p_renderer);
	Player* setUpPlayer(SDL_Renderer* p_renderer);
}