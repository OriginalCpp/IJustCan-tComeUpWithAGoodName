#pragma once
#include <SDL.h>
#include <vector>

enum class ObjectType
{
	none,
	tile,
	player,
	slime,
};

class GameObject {
public:
	GameObject();
	GameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst);
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* p_tex);
	SDL_FRect getCollisionRect();
	SDL_Rect getSrc();
	void setSrc(SDL_Rect p_src);
	SDL_Rect getDst();
	void setDst(SDL_Rect p_dst);
	float getX();
	float getY();
	int getW();
	int getH();
	float* getPosition();
	void setX(float p_x);
	void setY(float p_y);
	SDL_RendererFlip getFlip();
	void setFlip(SDL_RendererFlip p_flip);
	ObjectType getObjectType();
	float* getVector();
	void setVector(float p_x, float p_y);
	float* getpP();
	std::vector<std::vector<float>>* detectCollision(GameObject* p_gameObject);
	
protected:
	SDL_Texture* texture {nullptr};
	float pos[2];
	float previousPos[2];
	SDL_FRect collisionRect;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_RendererFlip flipFlag {SDL_FLIP_NONE};
	ObjectType objectType {ObjectType::none};
	float vector[2] = { 0, 0 };
};