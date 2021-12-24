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
#include "utils.hpp"
#include <iostream>
#include <SDL.h>



Camera::Camera(SDL_FRect p_margin, GameObject* p_object, bool p_isTracking)
    :m_margin{p_margin}, m_objectToTrack{p_object}, m_isTracking{p_isTracking}
{}



void Camera::hasToTrack()
{
    if(!m_isTracking)
    {
        if((m_objectToTrack->getX() >= m_margin.x) && (m_objectToTrack->getX() <= m_margin.x + m_margin.w))
        {
            m_isTracking = true;
        }     
    }
}



void Camera::trackObject(float (&p_offset)[2])
{
    p_offset[0] = 0;
    p_offset[1] = 0;
    
    if(m_isTracking && m_objectToTrack)
    {
        SDL_FPoint objectPoint = {m_objectToTrack->getX(), m_objectToTrack->getY()};

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
                std::cout << "Error: in trackObject(): object is in margin, even though collision_PointVsRect false\n";

        }
    }
}