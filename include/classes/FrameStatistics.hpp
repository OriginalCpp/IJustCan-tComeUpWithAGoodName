/**
 * @file FrameStatistics.hpp
 * @brief Contains the FrameStatistics class.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <vector>

/* A class that manages frame times (in seconds) to create statistics*/
class FrameStatistics
{
public:

    FrameStatistics();

    /* 
    Adds a frame time.
    
    \param p_frameTimeInSeconds The frame time to add in seconds
    */
    void addFrameTime(float p_frameTimeInSeconds);

    /* Get the number of frame times currently recorded. */
    int getNumberOfFrameTimes() const;

    /* 
    Print the average frame time. 
    Remarks: Uses arithmetic mean. 
    */
    void printAverageFrameTime() const;

    /* Deletes all frame times currently recorded. */
    void reset();

private:

    /* Holds the FrameTimes of multiple frames (in seconds). */
    std::vector<float> m_FrameTimesInSeconds;
};