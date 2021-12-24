#include "Player.hpp"
#include "GameObject.hpp"
#include "Constants.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>

Player::Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect)
	:GameObject{p_tex, p_src, p_dst, p_collisionRect}
{
	m_objectType = ObjectType::player;
}

void Player::setGoalX(int goal)
{
	m_goal[0] = goal;
}

int Player::getGoalX()
{
	return m_goal[0];
}

void Player::move(float p_elapsedTimeInMs) 
{
	m_previousPos->x = m_pos->x;
	m_previousPos->y = m_pos->y;

	m_pos->x += m_speed * p_elapsedTimeInMs * m_vector[0];
	m_pos->y += p_elapsedTimeInMs * m_vector[1];

	m_hitbox.x = m_pos->x;
	m_hitbox.y = m_pos->y;

	m_dstRect.x = m_pos->x;
	m_dstRect.y = m_pos->y - (m_dstRect.h - m_hitbox.h);

	float neededToReachGoal = m_goal[0] - m_vector[0]; 
	float accelerationX = p_elapsedTimeInMs * 7;

	if (neededToReachGoal > accelerationX)
		m_vector[0] += accelerationX;
	else if (neededToReachGoal < -accelerationX)
		m_vector[0] -= accelerationX;
	else
		m_vector[0] = m_goal[0];

	m_vector[1] += constants::gravity * p_elapsedTimeInMs;
}

void Player::jump()
{
	constexpr int simplification = -2*constants::normalJumpHeight/(constants::normalJumpWidth/2); 
	m_vector[1] = simplification*m_speed;
}

