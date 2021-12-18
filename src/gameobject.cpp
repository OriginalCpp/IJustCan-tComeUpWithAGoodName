#include "GameObject.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <vector>


GameObject::GameObject(){}

GameObject::GameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst)
	:texture{ p_texture }, pos{static_cast<float>(p_dst.x), static_cast<float>(p_dst.y)}, src{p_src}, dst{p_dst}
{
	collisionRect.x = p_dst.x;
	collisionRect.y = p_dst.y;
	collisionRect.w = p_dst.w;
	collisionRect.h = p_dst.h;
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

void GameObject::setSrc(SDL_Rect p_src)
{
	src = p_src;
}

SDL_Rect GameObject::getDst()
{
	return(dst);
}

void GameObject::setDst(SDL_Rect p_dst)
{
	dst = p_dst;
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
	pos[0] = p_x;
	collisionRect.x = p_x;
	dst.x = p_x;
}

void GameObject::setY(float p_y)
{
	pos[1] = p_y;
	collisionRect.y = p_y;
	dst.y = p_y;
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
	return dst.h;
}

int GameObject::getW()
{
	return dst.w;
}

float* GameObject::getPosition()
{
	return pos;
}

float* GameObject::getpP()
{
	return previousPos;
}


/**
 * @brief checks wether this object is colliding with another GameObject or not
 * 
 * !@bug one can bug himself approx. 1 pixel from the right into a block when holding a
 * 
 * ? does it make a difference if I make all the points or just take the dst rect points
 * 
 * @param p_gameObject the object for which we have to check if we collide with it
 * @return std::vector<std::vector<float>>* returns the points of the rectangles that collided with the other object; nullptr for no collision
 */

std::vector<std::vector<float>>* GameObject::detectCollision(GameObject* p_gameObject)
{
	if(!p_gameObject)
	{
		return (nullptr);
	}

	float thisPoints[4][2] = { 	{pos[0], pos[1]},
							   	{pos[0] + dst.w, pos[1]},
							   	{pos[0] + dst.w, pos[1] + dst.h},
						       	{pos[0], pos[1] + dst.h}};

	float objectX	{p_gameObject->getX()};
	float objectY	{p_gameObject->getY()};
	int objectH		{p_gameObject->getH()};
	int objectW 	{p_gameObject->getW()};

	float objectPoints[4][2] = {	{objectX, objectY},
									{objectX + objectW, objectY},
									{objectX + objectW, objectY + objectH},
									{objectX, objectY + objectH}};							
	

	std::vector<std::vector<float>>* collisionPoints = new std::vector<std::vector<float>>;
	
	int count {};

	for(int i = 0; i < 4; i++)
	{
		if(utils::collision_PointVsRect(thisPoints[i], p_gameObject->getCollisionRect()))
		{
			std::vector<float> point;
			point.push_back(thisPoints[i][0]);
			point.push_back(thisPoints[i][1]);
			collisionPoints->push_back(point);
			++count;
		}
		if(utils::collision_PointVsRect(objectPoints[i], collisionRect))
		{
			std::vector<float> point;
			point.push_back(objectPoints[i][0]);
			point.push_back(objectPoints[i][1]);
			collisionPoints->push_back(point);
			++count;
		}
	}

	if(count > 0)
		return(collisionPoints);
	else
		return(nullptr);
}