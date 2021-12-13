#pragma once
#include "GameObject.hpp"
#include <SDL.h>

class Player: public GameObject{
public:
	Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst);
	void move(float p_dt, int p_speed, int p_gravity);
	float* detectCollision(GameObject* p_gameObject);
	void setGoalX(int goalX);
	int getGoalX();
private:
	int Goal[2] = {0, 0};
};