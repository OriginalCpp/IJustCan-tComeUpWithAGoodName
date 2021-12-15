#include "Camera.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include <SDL.h>



Camera::Camera(SDL_Rect p_margin, Player* p_player)
    :margin{p_margin}, playerToTrack{p_player}
{}

//checks if the Player is still in the margin where nothing has to move or if everything needs to be offset and returns the offset that has to be made as an array of two integers

int* Camera::trackPlayer()
{
    float playerPoint[2] = {playerToTrack->getX(), playerToTrack->getY()};

    if(utils::collision_PointVsRect(playerPoint, margin))
    {
        return(NULL);
    }
    else
    {
        int* offset = new int[2];
        if (playerToTrack->getX() < margin.x)
            offset[0] = margin.x - playerToTrack->getX();
        else if (playerToTrack->getX() > margin.x + margin.w)
            offset[0] = margin.x + margin.w - playerToTrack->getX();
        if (playerToTrack->getY() < margin.y)
            offset[1] = margin.y - playerToTrack->getY();
        else if(playerToTrack->getY() > margin.y + margin.h)
            offset[1] = margin.y + margin.h - playerToTrack->getY();
        return(offset);
    }
}