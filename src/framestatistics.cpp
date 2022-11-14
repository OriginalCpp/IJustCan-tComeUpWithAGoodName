/**
 * @file framestatistics.cpp
 * @brief All definition of functions of the FramStatistics class.
 * @see FrameStatistics.hpp for more documentation.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "classes/FrameStatistics.hpp"

#include "Templates.hpp"
#include "Utils.hpp"
#include <iostream>
#include <vector>

FrameStatistics::FrameStatistics(){}

void FrameStatistics::addFrameTime(float p_frameTime)
{
    m_FrameTimesInSeconds.push_back(p_frameTime);
}

int FrameStatistics::getNumberOfFrameTimes() const
{
    return static_cast<int>(m_FrameTimesInSeconds.size());
}

void FrameStatistics::printAverageFrameTime() const
{
    float average = Template::calculateAverage(m_FrameTimesInSeconds);
    float ms = average * 1000;
    float us = ms * 1000;
    std::cout << "Average frame time is " << average << "seconds (" << ms << "ms, " << us << "us)" << "\nThis corresponds to " << (1/average) << "frames per second!\n";
}

void FrameStatistics::reset()
{
    m_FrameTimesInSeconds.clear();
}