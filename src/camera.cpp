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

#include "classes/Camera.hpp"

#include "Constants.hpp"
#include "classes/Player.hpp"
#include "Utils.hpp"
#include <iostream>
#include <memory>
#include <SDL.h>



Camera::Camera(SDL_Rect p_margin, GameObject* p_object, SDL_Rect p_limit)
    :m_margin{p_margin}, m_objectToTrack{p_object}, m_limit{p_limit}
{}



void Camera::applyOffsetToLimitRect(const SDL_Point& p_offset)
{
    m_limit.x += p_offset.x;
    m_limit.y += p_offset.y;
}

const SDL_Rect& Camera::getLimitRect()
{
    return m_limit;
}

void Camera::setLimitRect(SDL_Rect p_newLimitRect)
{
    m_limit = p_newLimitRect;
}

int Camera::getLimitRectX()
{
    return m_limit.x;
}

void Camera::setLimitRectX(int p_newXValue)
{
    m_limit.x = p_newXValue;
}

int Camera::getLimitRectY()
{
    return m_limit.y;
}

void Camera::setLimitRectY(int p_newYValue)
{
    m_limit.x = p_newYValue;
}


bool Camera::hasToTrack() const
{
    if(m_isTracking) return true;
    if(!m_objectToTrack) throw "m_objectToTrack_IS_NULLPTR";

    if((m_objectToTrack->getX() >= m_margin.x) && (m_objectToTrack->getX() <= m_margin.x + m_margin.w))
        return true;
        
    return false;
}



void Camera::beginToTrack()
{
    m_isTracking = true;
}

void Camera::stopToTrack()
{
    m_isTracking = false;
}

std::unique_ptr<SDL_Point> Camera::setUpCameraForBeginningOfLevel()
{
    if(!m_objectToTrack)
        throw "In Camera::setUpCameraForBeginningOfLevel(): Camera has no object to track\n";

    auto offset = std::make_unique<SDL_Point>(0, 0);

    SDL_FPoint objectPoint {m_objectToTrack->getX(), m_objectToTrack->getY()};

    if(!utils::isPointInRect(objectPoint, m_margin)) //TODO: Make this a function
    {
        bool check {};
        if (objectPoint.x <= m_margin.x)
        {
            offset->x = (m_margin.x - objectPoint.x);
            check = true;
        }
        else if (objectPoint.x >= (m_margin.x + m_margin.w))
        {
            offset->x = m_margin.x + m_margin.w - objectPoint.x;
            check = true;
        }
        if (objectPoint.y <= m_margin.y)
        {
            offset->y = (m_margin.y - objectPoint.y);
            check = true;
        }
        else if(objectPoint.y >= (m_margin.y + m_margin.h))
        {
            offset->y = ((m_margin.y + m_margin.h) - objectPoint.y);
            check = true;
        }
        if(!check)
            throw "In Camera::trackObject(): object is in margin, even though condition was that it is not\n";
    }

    return offset;
}

std::unique_ptr<SDL_Point> Camera::trackObject()
{
    if(!m_isTracking)
        throw "In Camera::trackObject(): Camera is not tracking\n";
    if(!m_objectToTrack)
        throw "In Camera::trackObject(): Camera has no object to track\n";

    auto offset = std::make_unique<SDL_Point>(0, 0);

    SDL_FPoint objectPoint {m_objectToTrack->getX(), m_objectToTrack->getY()};

    if(!utils::isPointInRect(objectPoint, m_margin))
    {
        bool check {};  //TODO:make this whole thing a function and then check for the stuff with the limit
        if (objectPoint.x <= m_margin.x)
        {
            offset->x = m_margin.x - objectPoint.x;

            if(m_limit.x + offset->x > 0) 
                offset->x = -m_limit.x;

            check = true;
        }
        else if (objectPoint.x >= m_margin.x + m_margin.w)
        {
            offset->x = m_margin.x + m_margin.w - objectPoint.x;

            if(m_limit.x + m_limit.w + offset->x < constants::window::w)
                offset->x = constants::window::w - (m_limit.x + m_limit.w);

            check = true;
        }
        if (objectPoint.y <= m_margin.y)
        {
            offset->y = m_margin.y - objectPoint.y;
            
            if(m_limit.y + offset->y > 0)
                offset->y = -m_limit.y;

            check = true;
        }
        else if(objectPoint.y >= m_margin.y + m_margin.h)
        {
            offset->y = m_margin.y + m_margin.h - objectPoint.y;

            if(m_limit.y + m_limit.h + offset->y < constants::window::h)
                offset->y = constants::window::h - (m_limit.y + m_limit.h);

            check = true;
        }
        if(!check)
            throw "In Camera::trackObject(): object is in margin, even though condition was that it is not\n";
    }

    return offset;
}