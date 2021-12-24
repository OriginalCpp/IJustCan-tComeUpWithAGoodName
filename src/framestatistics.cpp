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
#include "FrameStatistics.hpp"

#include "Templates.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

FrameStatistics::FrameStatistics(){}

void FrameStatistics::addFrameTime(float p_frameTime)
{
    m_FrameTimes.push_back(p_frameTime);
}

int FrameStatistics::getNumberOfFrameTimes() const
{
    return static_cast<int>(m_FrameTimes.size());
}

void FrameStatistics::printAverageFrameTime() const
{
    float average = Template::calculateAverage(m_FrameTimes);
    std::cout << "Average frame time is " << average << "seconds\nThis corresponds to " << (1/average) << "frames per second!\n";
}

void FrameStatistics::reset()
{
    m_FrameTimes.clear();
}