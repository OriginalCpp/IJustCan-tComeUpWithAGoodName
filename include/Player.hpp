#pragma once
#include "GameObject.hpp"

#include "Constants.hpp"
#include <SDL.h>

class Player: public GameObject{
public:
	Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect = {0, 0, 0, 0});
	void move(float p_dt);
	void jump();
	void setGoalX(int goalX);
	int getGoalX();
private:
	int m_goal[2] = {0, 0};
	int m_speed {constants::normalPlayerSpeed};
};