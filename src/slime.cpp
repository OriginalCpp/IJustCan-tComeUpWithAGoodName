#include "Slime.hpp"
#include "constants.hpp"
#include <SDL.h>

Slime::Slime(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect, float p_vectorX)
    :GameObject{p_tex, p_src, p_dst, p_collisionRect}
{
    m_objectType = ObjectType::slime;
    m_vector[0] = p_vectorX;
}



void Slime::move(float p_dt)
{
    m_previousPos->x = m_pos->x;
    m_previousPos->y = m_pos->y;

    m_pos->x += speed * p_dt * m_vector[0];
    m_pos->y += p_dt * m_vector[1];
    
    m_vector[1] += constants::gravity * p_dt;

	m_hitbox.x = m_pos->x;
	m_hitbox.y = m_pos->y;

    m_dstRect.x = m_pos->x;
	m_dstRect.y = m_pos->y - (m_dstRect.h - m_hitbox.h);
}