/**
 * @file Templates.hpp
 * @brief All template functions.
 * @version 0.1
 * @date 2021-12-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <iostream>
#include <numeric>
#include <vector>

namespace Template
{
    /* calculates the average using the arithmetic mean */
	template <typename T>
	inline float calculateAverage(const std::vector<T>& p_vector)
	{
		if(p_vector.empty())
		{
			std::cout << "Error: Call to calculateAverage with empty vector.\n";
			return(0);
		}

		const int numberOfElements {static_cast<int>(p_vector.size())};

		return std::reduce(p_vector.begin(), p_vector.end())/numberOfElements;
	}
}