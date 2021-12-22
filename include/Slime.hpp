#pragma once
#include "GameObject.hpp"
#include <SDL.h>


class Slime :public GameObject
{
    int speed{100};

public:
    Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect = {0, 0, 0, 0}, float p_vectorX = -1);
    void move(float p_dt);
};