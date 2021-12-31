/**
 * @file Player.hpp
 * @brief The Player class.
 * @see GameObject.hpp
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "DynamicGameObject.hpp"

#include "Constants.hpp"
#include <SDL.h>

class Player: public DynamicGameObject
{
public:
	Player(SDL_Texture* p_tex, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox = {0, 0, 0, 0});

	void update(float p_elapsedTimeInSeconds);

    /*
	Detect wether a collision between THIS GameObject and p_otherGameObject is happening or not and then handle/resolves the collision.
	Remarks: This function only changes the position/vector of THIS GameObject in order to resolve the collision!

	\param p_otherGameObject
	*/
	void resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_dynamicGameObject);

	void jump();
	void die();

	int getXVelocityGoal();
	void setXVelocityGoal(int goalX);

	int getAmountOfJumps() const;
	void setAmountOfJumps(int p_newAmount);

private:

	int m_xVelocityGoal {0};

	int m_amountOfJumps {constants::maxAmountOfJumps};
};