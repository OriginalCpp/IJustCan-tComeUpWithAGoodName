#include "Camera.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>



Camera::Camera(SDL_FRect p_margin, GameObject* p_object, bool p_isTracking)
    :margin{p_margin}, objectToTrack{p_object}, isTracking{p_isTracking}
{}

void Camera::hasToTrack()
{
    if(!isTracking)
    {
        if((objectToTrack->getX() >= margin.x) && (objectToTrack->getX() <= margin.x + margin.w))
        {
            isTracking = true;
        }     
    }
}

/**
 * @brief returns the offset that has to be made to center the player again
 * 
 * TODO: make the cam go smooth not so abrupt especially when moving in Y direction
 * 
 * @return int* returns the offset (X,Y) 
 */

float* Camera::trackObject()
{
    if(isTracking)
    {
        SDL_FPoint objectPoint = {objectToTrack->getX(), objectToTrack->getY()};

        if(!utils::collision_PointVsRect(&objectPoint, &margin))
        {
            float* offset = new float[2]{0, 0};

            bool check {};

            if (objectPoint.x <= margin.x)
            {
                offset[0] = (margin.x - objectPoint.x);
                check = true;
            }
            else if (objectPoint.x >= (margin.x + margin.w))
            {
                offset[0] = margin.x + margin.w - objectPoint.x;
                check = true;
            }

            if (objectPoint.y <= margin.y)
            {
                offset[1] = (margin.y - objectPoint.y);
                check = true;
            }
            else if(objectPoint.y >= (margin.y + margin.h))
            {
                offset[1] = ((margin.y + margin.h) - objectPoint.y);
                check = true;
            }


            if(check)
                return(offset);
            else
            {
                std::cout << "Error: in trackObject(): object is in margin, even though collision_PointVsRect false\n";
                return(nullptr);
            }

        }
    }

    return(nullptr);
}