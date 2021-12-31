/**
 * @file camera.cpp
 * @brief Definitions of all functions of the Camera class.
 * @see Camera.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Camera.hpp"

#include "Constants.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include <iostream>
#include <SDL.h>



Camera::Camera(SDL_FRect p_margin, GameObject* p_object, bool p_isTracking)
    :m_margin{p_margin}, m_objectToTrack{p_object}, m_isTracking{p_isTracking}
{}



bool Camera::hasToTrack() const
{
    if(m_isTracking) return true;

    if((m_objectToTrack->getX() >= m_margin.x) && (m_objectToTrack->getX() <= m_margin.x + m_margin.w))
        return true;

    return false;
}



void Camera::beginToTrack()
{
    m_isTracking = true;
}



void Camera::trackObject(float (&p_offset)[2])
{
    p_offset[0] = 0;
    p_offset[1] = 0;

    if(!m_isTracking)
    {
        std::cout << "Error: in Camera::trackObject(): Camera is not tracking\n";
        return;
    }
    if(!m_objectToTrack)
    {
        std::cout << "Error: in Camera::trackObject(): Camera has no object to track\n";
        return;
    }

    SDL_FPoint objectPoint {m_objectToTrack->getX(), m_objectToTrack->getY()};

    if(!utils::collision_PointVsRect(&objectPoint, &m_margin))
    {
        bool check {};
        if (objectPoint.x <= m_margin.x)
        {
            p_offset[0] = (m_margin.x - objectPoint.x);
            check = true;
        }
        else if (objectPoint.x >= (m_margin.x + m_margin.w))
        {
            p_offset[0] = m_margin.x + m_margin.w - objectPoint.x;
            check = true;
        }
        if (objectPoint.y <= m_margin.y)
        {
            p_offset[1] = (m_margin.y - objectPoint.y);
            check = true;
        }
        else if(objectPoint.y >= (m_margin.y + m_margin.h))
        {
            p_offset[1] = ((m_margin.y + m_margin.h) - objectPoint.y);
            check = true;
        }
        if(!check)
            std::cout << "Error: in Camera::trackObject(): object is in margin, even though condition was that it is not\n";
    }
}