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
    /* Holds the FrameTimes of multiple frames (in seconds). */
    std::vector<float> m_FrameTimes;

public:

    FrameStatistics();

    /* Adds a frameTime to m_FrameTimes. */
    void addFrameTime(float p_frameTime);

    /* Get the number of elements inside m_FrameTimes */
    int getNumberOfFrameTimes() const;

    /* Print the average frame time (arithmetic mean). */
    void printAverageFrameTime() const;

    /* Deletes all elements of m_FrameTimes */
    void reset();

};