/**
 * @file Camera.hpp
 * @brief Contains the Camera Class
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "GameObject.hpp"
#include <SDL.h>
#include <vector>



/*A camera that can track one object at a time.*/
class Camera
{
public:

    /* 
    \param p_margin Represents the area in which the m_objectToTrack will be kept in by the camera.
    \param p_object The GameObject which shall be tracked by the camera.
    \param p_isTracking Starting tracking state of the camera. The tracking state can be changed later with Camera::hasToTrack()
    */
    Camera(SDL_FRect p_margin, GameObject* p_object, bool p_isTracking = false);

    /*
    Checks wether the m_objectToTrack has entered m_margin or not. 
    If yes sets m_isTracking to true, otherwise to false.
    */
    void hasToTrack();

    /*
    Calculate the offset that has to be made to keep the m_objectToTrack in m_margin.

    \param p_offset An array to hold the calculated offset.
    */
    void trackObject(float (&p_offset)[2]);

private:

    /*Represents the area in which the m_objectToTrack will be kept in by the camera.*/
    SDL_FRect m_margin{0, 0, 0, 0};

    /*The GameObject which shall be tracked by the camera.*/
    GameObject* m_objectToTrack {nullptr};

    /*Tracking state of the camera, only tracks the m_objectToTrack if this is true.*/
    bool m_isTracking {false};

};