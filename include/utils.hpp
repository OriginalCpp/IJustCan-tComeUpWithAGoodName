/**
 * @file Utils.hpp
 * @brief All utility functions.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include "Camera.hpp"
#include "DynamicGameObject.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include <memory>
#include <numeric>
#include <SDL.h>
#include <vector>


namespace utils 
{
	/**
	 * @brief Initializes SDL's video subsystem and the PNG library of SDL_image
	 * 
	 * @return 0 on succes; 1 if the init. of the video subsystem failed; 2 if the init of the PNG library of SDL_image failed
	 */
	int initSDL();

	SDL_Rect createRect(int p_x, int p_y, int p_width, int p_height);
	SDL_FRect createFRect(float p_x, float p_y, float p_width, float p_height);
	SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* p_renderer);

	/**
 	* @brief Checks if a SDL_FPoint is in a SDL_FRect. Has a test function.
 	*
	* @see test::utils_collision_PointVsRect() 
	*
 	* @param point
 	* @param rect 
 	* @return Returns true if the point is in the rect, false otherwise.
 	*/
	bool collision_PointVsRect(const SDL_FPoint* point, const SDL_FRect* rect);

	/**
	 * @brief Get the corners of p_rect1 and p_rect2 that reside inside each other. Remarks: Has a test function.
	 * 
	 * @see test::utils_getIntersectionCornerFPoints()
	 * 
	 * @param p_rect1 
	 * @param p_rect2 
	 * @return Returns a pointer to an std::vector<SDL_FPoint> containing the corners of @e both rects that reside inside each other 
	 */
	std::unique_ptr<std::vector<SDL_FPoint>> getIntersectionCornerFPoints(const SDL_FRect* const p_rect1, const SDL_FRect* const p_rect2);


	/**
 	* @brief Checks from which direction the collision of two GameObjects is happening and accordingly adjusts the position and the vector of the p_dynamicGameObject
 	* 
 	* TODO: In mehrere Parts aufteilen damit mehrere Teile des Programms die Funktion besser nutzen können (der Slime z.B.)
 	* 
 	* @param p_dynamicGameObject GameObject which collides with p_staticGameObject
 	* @param p_collisionPoint    Outer Points of the collision rectangle of both GameObjects that that intersect with the collision rectangle of the other GameObject
 	* @param p_staticGameObject  GameObject that the p_dynamicGameObject collides with
 	* @return Returns true if the p_dynamicGameObject is on the floor/ground, otherwise false.
 	*/
	void resolveCollision(DynamicGameObject* const p_dynamicGameObject, const std::vector<SDL_FPoint>* const p_outerPoints, GameObject* const p_staticGameObject);

	void resolveCollision(DynamicGameObject* const p_dynamicGameObject, const std::vector<SDL_FPoint>* const p_outerPoints, DynamicGameObject* const p_staticGameObject);

	void selectTiles(std::vector<std::vector<Tile*>>& p_tiles);

	/* 
	Checks if a GameObject is in the window.
	Remarks: Also checks wether the pointer is a nullptr or not.

	\param p_gameObject
	\returns True if the Object is in the window, false otherwise.
	*/
	bool isInWindow(const GameObject* p_gameObject);
}