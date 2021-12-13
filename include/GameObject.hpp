#pragma once
#include <SDL.h>

class GameObject {
public:
	GameObject();
	GameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst);
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* p_tex);
	SDL_Rect* getSrc();
	void setSrc(SDL_Rect p_src);
	SDL_Rect* getDst();
	float getX();
	float getY();
	void setX(float p_x);
	void setY(float p_y);
	float* getVector();
	void setVector(float p_x, float p_y);
	int getW();
	int getH();
	float* getpP();
	
protected:
	SDL_Texture* texture = NULL;
	float x{};
	float y{};
	float previousPos[2] = {0, 0};
	SDL_Rect src;
	SDL_Rect dst;
	int w{};
	int h{};
	float vector[2] = { 0, 0 };
};