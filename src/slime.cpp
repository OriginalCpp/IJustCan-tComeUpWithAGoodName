#include "Slime.hpp"
#include "constants.hpp"
#include <SDL.h>

Slime::Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect, float p_vectorX)
    :GameObject{p_tex, p_src, p_dst, p_collisionRect}
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

	collisionRect.x = pos[0];
	collisionRect.y = pos[1];

    dst.x = pos[0];
	dst.y = pos[1] - (dst.h - collisionRect.h);
}