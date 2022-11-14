/**
 * @file GameObject.hpp
 * @brief The GameObject Class (+ ObjectType enum)
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "ObjectType.hpp"
#include <SDL.h>
#include <vector>


/**
 * @brief A class to represent any object in the Game
 */
class GameObject {
public:
	GameObject();

	/*
	Construct a new GameObject. Set texture, position and hitbox.

	Remarks: If no p_hitbox is provided then the hitbox will have the same size as p_dst. Only the width and the height of p_hitbox are considered.
			 The Position of an object is relative to p_dst.x and p_dst.y. Has a test function.

	See: test::GameObject_Constructor()

	\param p_texture
	\param p_src
	\param p_dst
	\param p_hitbox
	*/
	GameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox = {0, 0, 0, 0});

	virtual ~GameObject();

	SDL_Texture* getTexture() const;
	void setTexture(SDL_Texture* p_tex);
	
	/**
	 * @brief Has a test function.
	 * 
	 * @sa test::GameObject_setXgetX()
	 */
	float getX() const;
	void setX(float p_x);

	float getY() const;
	void setY(float p_y);

	int getW() const;
	int getH() const;

	const SDL_FPoint* getPosition() const;
	void setPosition(const SDL_FPoint* p_position);

	const SDL_Rect* getSrc() const;
	void setSrc(SDL_Rect p_src);
	const SDL_Rect* getDst() const;
	const SDL_FRect* getHitBox() const;
	

	const SDL_RendererFlip* getFlip() const;
	void setFlip(SDL_RendererFlip p_flip);

	const ObjectType getObjectType() const;
	void setObjectType(ObjectType p_objectType);

	/*
    True = has adjancent tile in given direction, false = has no adjancent tile in given direction.
    Starts on top and goes on clockwise 
	RESERVED FOR OBJECTTYPE TILE DO NOT USE OTHERWISE
    */
    bool adjancentTiles[4] = {false, false, false, false};
	
private:

	SDL_Texture* m_texture {nullptr};

	SDL_FPoint m_pos[2] {0, 0};

	SDL_Rect m_srcRect {0, 0, 0, 0};
	SDL_Rect m_dstRect {0, 0, 0, 0};
	SDL_FRect m_hitbox {0, 0, 0, 0};

	ObjectType m_objectType {ObjectType::none};

	SDL_RendererFlip m_flipFlag {SDL_FLIP_NONE};
};