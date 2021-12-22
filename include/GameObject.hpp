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

	/**
	 * @brief Construct a new GameObject object. Has a test function.
	 * 
	 * @sa Test::GameObject_Constructor()
	 * 
	 * @param p_texture 
	 * @param p_src 
	 * @param p_dst 
	 * @param p_collisionRect 
	 */
	GameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_collisionRect = {0, 0, 0, 0});
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

	/**
 	* @brief Detects wether a collision between this GameObject and another GameObject is happening.
	*
 	* @param p_gameObject Pointer to the other GameObject
 	* @return Returns an std::vector<SDL_FPoint>* containing the outer points(float) of the collisionRectangles that collided with 
 	* 		   another collisionRectangle (points of both GameObjects) or nullptr for no collision.
 	*/
	std::vector<SDL_FPoint>* detectCollision(GameObject* p_gameObject);
	
protected:
	SDL_Texture* texture {nullptr};
	float pos[2] {0, 0};
	float previousPos[2] {0, 0};
	SDL_FRect collisionRect {0, 0, 0, 0};
	SDL_Rect src {0, 0, 0, 0};
	SDL_Rect dst {0, 0, 0, 0};
	SDL_RendererFlip flipFlag {SDL_FLIP_NONE};
	ObjectType objectType {ObjectType::none};
	float vector[2] = {0, 0};
};