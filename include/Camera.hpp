#pragma once
#include "Player.hpp"
#include <SDL.h>
#include <vector>

class Camera
{
    SDL_Rect margin{};
    Player* playerToTrack;
public:
    Camera(SDL_Rect p_margin, Player* p_player);
    int* trackPlayer();
};