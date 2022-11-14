/**
 * @file Camera.hpp
 * @brief Contains the Camera Class
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "classes/GameObject.hpp"
#include <memory>
#include <SDL.h>


/*A camera that can track one object at a time.*/
class Camera
{
public:

    /* 
    \param p_margin Represents the area in which the m_objectToTrack will be kept in by the camera.
    \param p_object The GameObject which shall be tracked by the camera.
    \param p_limit Represents the area that the camera is limited to, so with this camera active we won't see outside of this rectangle.
    \param p_isTracking Starting tracking state of the camera.
    */
    Camera(SDL_Rect p_margin, GameObject* p_object, SDL_Rect p_limit);

    void applyOffsetToLimitRect(const SDL_Point& p_offset);

    const SDL_Rect& getLimitRect();
    void setLimitRect(SDL_Rect p_newLimitRect);
    
    int getLimitRectX();
    void setLimitRectX(int p_newXValue);

    int getLimitRectY();
    void setLimitRectY(int p_newYValue);

    /*
    Checks wether the m_objectToTrack has yet entered m_margin (true) or not (false).
    */
    bool hasToTrack() const;

    /*
    Set m_isTracking to true, the Camera now tracks m_objectToTrack.
    */
    void beginToTrack();

    /*
    Set m_isTracking to false, the Camera stops to track m_objectToTrack.
    */
   void stopToTrack();

    /*
    Calculate the offset that has to be made to keep the m_objectToTrack in m_margin.

    \param p_offset A pointer to an SDL_Point that holds the offset.
    */
    std::unique_ptr<SDL_Point> trackObject();

    /*
    Calculates the offset like Camera::trackObject() but neglects m_limit. The m_objectToTrack will be (whatever his position is) at the left side of the screen after the rearrangement.
    Remarks: Designed to be used exactly once after setting up a level!
    */
    std::unique_ptr<SDL_Point> setUpCameraForBeginningOfLevel();

private:

    /*Represents the area in which the m_objectToTrack will be kept in by the camera.*/
    SDL_Rect m_margin{0, 0, 0, 0};

    /*The GameObject which shall be tracked by the camera.*/
    GameObject* m_objectToTrack {nullptr};

    /*Represents the area that the camera is limited to (most of the time this will be the represent the borders of the map), 
      so while this camera is active we won't see outside of this rectangle */
    SDL_Rect m_limit{0, 0, 0, 0};

    /*Tracking state of the camera, only tracks the m_objectToTrack if this is true.*/
    bool m_isTracking {false};
};