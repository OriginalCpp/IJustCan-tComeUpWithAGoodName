#include "Camera.hpp"
#include "Player.hpp"
#include "Globals.hpp"
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
        float objectPoint[2] = {objectToTrack->getX(), objectToTrack->getY()};

        std::cout << "Object: " << objectPoint[0] << ", " << objectPoint[1] << '\n';
        std::cout << "Margin: " << margin.x << ", " << margin.y << ", " << margin.w << ", " << margin.h << '\n'; 

        if(!utils::collision_PointVsRect(objectPoint, margin))
        {
            float* offset = new float[2]{0, 0};

            //std::cout << "Probably garbage values: " << offset[0] << ", " << offset[1] << '\n';

            bool check {};
            // bool o0changed{};
            // bool o1changed{};

            if (objectPoint[0] < margin.x)
            {
                //std::cout << "objectPoint[0] < margin.x \n";
                offset[0] = (margin.x - objectPoint[0]);
                //o0changed = true;
                //std::cout << "margin.x - objectPoint[0] = " << (margin.x - objectPoint[0]) << '\n';
                check = true;
            }
            else if (objectPoint[0] > (margin.x + margin.w))
            {
                //std::cout << "objectPoint[0] > (margin.x + margin.w) \n";
                offset[0] = ((margin.x + margin.w) - objectPoint[0]);
                //o0changed = true;
                //std::cout << "(margin.x + margin.w) - objectPoint[0] = " << ((margin.x + margin.w) - objectPoint[0]) << '\n';
                check = true;
            }

            if (objectPoint[1] < margin.y)
            {
                //std::cout << "objectPoint[1] < margin.y \n";
                offset[1] = (margin.y - objectPoint[1]);
                //o1changed = true;
                //std::cout << "margin.y - objectPoint[1] = " << (margin.y - objectPoint[1]) << '\n';
                check = true;
            }
            else if(objectPoint[1] > (margin.y + margin.h))
            {
                //std::cout << "objectPoint[1] > (margin.y + margin.h)\n";
                offset[1] = ((margin.y + margin.h) - objectPoint[1]);
                //o1changed = true;
                //std::cout << "(margin.y + margin.h) - objectPoints[1] = " << ((margin.y + margin.h) - objectPoint[1]) << '\n';
                check = true;
            }


            if(check)
            {
                //std::cout << "Offset: " << offset[0] << ',' << offset[1] << '\n';
                //std::cout << "o0changed: " << o0changed << ", o1changed: " << o1changed << '\n';
                return(offset);
            }
            else
            {
                std::cout << "Error: in trackObject(): object is in margin, even though collision_PointVsRect false\n";
                return(nullptr);
            }

        }
    }

    return(nullptr);
}