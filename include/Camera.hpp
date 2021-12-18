#pragma once
#include "GameObject.hpp"
#include <SDL.h>
#include <vector>

class Camera
{
    SDL_FRect margin{};
    GameObject* objectToTrack;
    bool isTracking;

public:
    Camera(SDL_FRect p_margin, GameObject* p_object, bool p_isTracking = false);
    void hasToTrack();
    float* trackObject();
};