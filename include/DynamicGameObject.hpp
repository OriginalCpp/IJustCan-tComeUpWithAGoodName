/**
 * @file DynamicGameObject.hpp
 * @brief The DynamicGameObject class
 * @see GameObject.hpp
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include "GameObject.hpp"

#include "StaticGameObject.hpp"
#include <SDL.h>
#include <vector>

class DynamicGameObject :public GameObject
{
public:

    DynamicGameObject(SDL_Texture* p_texture, SDL_Rect p_src, SDL_Rect p_dst, SDL_FRect p_hitbox = {0, 0, 0, 0});

    virtual void update(float p_dt) = 0;

    /*
	Detect wether a collision between THIS GameObject and p_otherGameObject is happening or not and then handle/resolves the collision.
	Remarks: This function only changes the position/vector of THIS GameObject in order to resolve the collision!

	\param p_otherGameObject
	*/
    void handleCollision(const StaticGameObject* const p_otherGameObject);
    void handleCollision(DynamicGameObject* const p_otherGameObject);

    virtual void resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, const StaticGameObject* const p_staticGameObject);
    virtual void resolveCollision(const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_dynamicGameObject) = 0;

    virtual void jump() = 0;
    virtual void die() = 0;

    const float* getVector() const;
	void setVector(float p_x, float p_y);

    float getVectorX() const;
    void setVectorX(float p_newXValue);
    float getVectorY() const;
    void setVectorY(float p_newYValue);


    const SDL_FPoint* getPreviousPosition() const;
    void setPreviousPosition(const SDL_FPoint* p_previousPosition);

	bool isAlive();
    void isAlive(bool p_isAlive);

    int getSpeed() const;
	void setSpeed(int p_speed);

    float getMass() const;
    void setMass(float p_mass);

    bool isGrounded() const; 
    void isGrounded(bool p_grounded);

private:

    /*
    Holds the x and y velocity of the object.
    */
    float m_vector[2] = {0, 0};

    SDL_FPoint m_previousPos[2] {0, 0};

    bool m_alive{true};

    float m_mass {1};

    int m_speed{};

    /*
    Is the object on the ground?
    */
    bool m_grounded {false};
};