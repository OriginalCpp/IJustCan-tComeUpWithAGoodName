#include "Slime.hpp"
#include "Globals.hpp"
#include <SDL.h>

Slime::Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, float p_vectorX)
    :GameObject{p_tex, p_src, p_dst}
{
    objectType = ObjectType::slime;
    vector[0] = p_vectorX;
}



void Slime::move(float p_dt)
{
    previousPos[0] = pos[0];
    previousPos[1] = pos[1];

    pos[0] += speed * p_dt * vector[0];
    pos[1] += p_dt * vector[1];
    
    vector[1] += constants::gravity * p_dt;

    dst.x = pos[0];
	collisionRect.x = pos[0];
	dst.y = pos[1];
	collisionRect.y = pos[1];
}