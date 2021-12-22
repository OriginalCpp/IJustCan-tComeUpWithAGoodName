#include "GameObject.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <iostream>
#include <vector>


GameObject::GameObject(){}


/**
 * @sa GameObject.hpp
 * @sa Test::GameObject_Constructor()
 */
GameObject::GameObject(SDL_Texture* p_texture, SDL_Rect p_srcRect, SDL_Rect p_dstRect, SDL_FRect p_collisionRect)
	:texture{p_texture}, src{p_srcRect}, dst{p_dstRect} 
{
	if((!p_collisionRect.w) || (!p_collisionRect.h))
	{
		pos[0] = p_dstRect.x;
		pos[1] = p_dstRect.y;

		collisionRect.x = p_dstRect.x;
		collisionRect.y = p_dstRect.y;
		collisionRect.w = p_dstRect.w;
		collisionRect.h = p_dstRect.h;
	}
	else
	{
		collisionRect.x = p_dstRect.x;
		pos[0] = collisionRect.x;
		collisionRect.y = p_dstRect.y + (p_dstRect.h - p_collisionRect.h);
		pos[1] = collisionRect.y;

		collisionRect.w = p_collisionRect.w;
		collisionRect.h = p_collisionRect.h;
	}
}

SDL_Texture* GameObject::getTexture()
{
	return(texture);
}

void GameObject::setTexture(SDL_Texture* p_tex)
{
	texture = p_tex;
}

SDL_FRect GameObject::getCollisionRect()
{
	return collisionRect;
}

SDL_Rect GameObject::getSrc()
{
	return(src);
}

void GameObject::setSrc(SDL_Rect p_srcRect)
{
	src = p_srcRect;
}

SDL_Rect GameObject::getDst()
{
	//DEBUG
	if(objectType == ObjectType::slime)
		std::cout << "in getDst(): dst.y: " << dst.y << '\n';
	return(dst);
}

void GameObject::setDst(SDL_Rect p_dstRect)
{
	dst = p_dstRect;
}

float GameObject::getX()
{
	return pos[0];
}

float GameObject::getY()
{
	return pos[1];
}

void GameObject::setX(float p_x)
{
	collisionRect.x = p_x;
	pos[0] = p_x;
	dst.x = p_x;
}

void GameObject::setY(float p_y)
{
	pos[1] = p_y;
	collisionRect.y = p_y;
	
	dst.y = p_y - (dst.h - collisionRect.h);

	//DEBUG
	if(objectType == ObjectType::slime)
		std::cout << "(after) setY(): dst.y: " << dst.y << '\n';
}

SDL_RendererFlip GameObject::getFlip()
{
	return flipFlag;
}

void GameObject::setFlip(SDL_RendererFlip p_flip)
{
	flipFlag = p_flip;
}

ObjectType GameObject::getObjectType()
{
	return objectType;
}

float* GameObject::getVector() {
	return(vector);
}

void GameObject::setVector(float p_x, float p_y) {
	vector[0] = p_x;
	vector[1] = p_y;
}

int GameObject::getH()
{
	return collisionRect.h;
}

int GameObject::getW()
{
	return collisionRect.w;
}

float* GameObject::getPosition()
{
	return pos;
}

float* GameObject::getpP()
{
	return previousPos;
}


std::vector<SDL_FPoint>* GameObject::detectCollision(GameObject* p_otherGameObject)
{
	if(!p_otherGameObject)
	{
		return (nullptr);
	}

	SDL_FPoint thisPoints[4] { 	{collisionRect.x, collisionRect.y},
							   	{collisionRect.x + collisionRect.w, collisionRect.y},
							   	{collisionRect.x + collisionRect.w, collisionRect.y + collisionRect.h},
						       	{collisionRect.x, collisionRect.y + collisionRect.h}};

	SDL_FRect objCR {p_otherGameObject->getCollisionRect()};

	SDL_FPoint objectPoints[4] = { 	{objCR.x, objCR.y},
									{objCR.x + objCR.w, objCR.y},
									{objCR.x + objCR.w, objCR.y + objCR.h},
									{objCR.x, objCR.y + objCR.h}};							
	

	std::vector<SDL_FPoint>* collisionPoints = new std::vector<SDL_FPoint>;
	
	int count {0};

	for(int i = 0; i < 4; i++)
	{
		if(utils::collision_PointVsRect(&thisPoints[i], &objCR))
		{
			collisionPoints->push_back(thisPoints[i]);
			++count;
		}
		if(utils::collision_PointVsRect(&objectPoints[i], &this->collisionRect))
		{
			collisionPoints->push_back(objectPoints[i]);
			++count;
		}
	}

	if(count > 0)
	{
		return(collisionPoints);
	}	
	else
		return(nullptr);
}