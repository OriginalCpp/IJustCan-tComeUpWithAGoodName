#pragma once
#include "RenderWindow.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tiles.hpp"
#include "Camera.hpp"
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
 	* @brief Checks if a SDL_Point is in a SDL_Rect. Has a test function.
 	*
	* @sa Test::utils_collision_PointVsRect() 
	*
 	* @param point
 	* @param rect 
 	* @return True if point is in rect, false otherwise.
 	*/
	bool collision_PointVsRect(SDL_FPoint* point, SDL_FRect* rect);


	/**
	 * @brief Checks from which direction the collision of two GameObjects is happening and accordingly adjusts the position and the vector of the p_dynamicGameObject
	 * 
	 * TODO: In mehrere Parts aufteilen damit mehrere Teile des Programms die Funktion besser nutzen können (der Slime z.B.)
	 * 
	 * @param p_dynamicGameObject GameObject which collides with p_staticGameObject
	 * @param p_collisionPoint    Outer Points of the collision rectangle of both GameObjects that that intersect with the collision rectangle of the other GameObject
	 * @param p_staticGameObject  GameObject that the p_dynamicGameObject collides with
	 * @return Returns a bool. True if the player is on the floor/ground or false if he is not.
	 */
	bool resolveCollision(GameObject* p_dynamicGameObject, std::vector<SDL_FPoint>* p_collisionPoint, GameObject* p_staticGameObject);




	void selectTiles(std::vector<std::vector<Tile*>>& p_tiles);
}