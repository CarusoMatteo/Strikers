#pragma once

#include <random>

/// @brief Static class that provides random number generation utilities.
class Random
{
public:
	/// @brief Get a random float in the range [minIncluded, maxExcluded).
	static float getRandomFloat(float minIncluded, float maxExcluded);
	/// @brief Get a random int in the range [minIncluded, maxExcluded).
	static int getRandomInt(int minIncluded, int maxExcluded);

	static std::random_device rd;
	static std::mt19937 gen;

private:
	Random() = default;
	~Random() = default;
};