/**
 * @file gameobject.cpp
 * @brief All definitions of member functions of class GameObject.
 * @see GameObject.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-22
 * 
 * @copyright Copyright (c) 2021
 */

#include "GameObject.hpp"

#include "utils.hpp"
#include <iostream>
#include <memory>
#include <SDL.h>
#include <utility>
#include <vector>


GameObject::GameObject(){}


GameObject::GameObject(SDL_Texture* p_texture, SDL_Rect p_srcRect, SDL_Rect p_dstRect, SDL_FRect p_hitbox)
	:m_texture{p_texture}, m_srcRect{p_srcRect}, m_dstRect{p_dstRect} 
{
	if((!p_hitbox.w) || (!p_hitbox.h))
	{
		m_pos->x = p_dstRect.x;
		m_pos->y = p_dstRect.y;

		m_hitbox.x = p_dstRect.x;
		m_hitbox.y = p_dstRect.y;
		m_hitbox.w = p_dstRect.w;
		m_hitbox.h = p_dstRect.h;
	}
	else
	{
		m_hitbox.x = p_dstRect.x;
		m_pos->x = m_hitbox.x;
		m_hitbox.y = p_dstRect.y + (p_dstRect.h - p_hitbox.h);
		m_pos->y = m_hitbox.y;

		m_hitbox.w = p_hitbox.w;
		m_hitbox.h = p_hitbox.h;
	}
}



SDL_Texture* GameObject::getTexture() const
{
	return(m_texture);
}

void GameObject::setTexture(SDL_Texture* p_tex)
{
	m_texture = p_tex;
}



float GameObject::getX() const
{
	return m_pos->x;
}

void GameObject::setX(float p_x)
{
	m_hitbox.x = p_x;
	m_pos->x = p_x;
	m_dstRect.x = p_x;
}



float GameObject::getY() const
{
	return m_pos->y;
}

void GameObject::setY(float p_y)
{
	m_pos->y = p_y;
	m_hitbox.y = p_y;
	
	m_dstRect.y = p_y - (m_dstRect.h - m_hitbox.h);
}



int GameObject::getW() const
{
	return m_hitbox.w;
}

int GameObject::getH() const
{
	return m_hitbox.h;
}



const SDL_FPoint* GameObject::getPosition() const
{
	return m_pos;
}

const SDL_FPoint* GameObject::getPreviousPosition() const
{
	return m_previousPos;
}

const float* GameObject::getVector() const
{
	return(m_vector);
}

void GameObject::setVector(float p_x, float p_y) 
{
	m_vector[0] = p_x;
	m_vector[1] = p_y;
}




const SDL_Rect* GameObject::getSrc() const
{
	return(&m_srcRect);
}

void GameObject::setSrc(SDL_Rect p_srcRect)
{
	m_srcRect = p_srcRect;
}

const SDL_Rect* GameObject::getDst() const
{
	return(&m_dstRect);
}

const SDL_FRect* GameObject::getHitBox() const
{

	return &m_hitbox;
}



const SDL_RendererFlip* GameObject::getFlip() const
{
	return &m_flipFlag;
}

void GameObject::setFlip(SDL_RendererFlip p_flip)
{
	m_flipFlag = p_flip;
}

const ObjectType* GameObject::getObjectType() const
{
	return &m_objectType;
}



bool GameObject::handleCollision(const GameObject* const p_otherGameObject)
{
	if(m_objectType == ObjectType::player)
	{
		if(!utils::isInWindow(p_otherGameObject))
			return false;
	}
	else if(!p_otherGameObject)
		return false;

	

	std::unique_ptr<std::vector<SDL_FPoint>> cornerPoints {utils::getIntersectionCornerFPoints(&m_hitbox, p_otherGameObject->getHitBox())};

	if(cornerPoints)
	{
		bool grounded {false};

		if (utils::resolveCollision(this, std::move(cornerPoints), p_otherGameObject))
			grounded = true;

		return grounded;
	}

	return false;
}