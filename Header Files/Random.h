#pragma once

#include <random>

class Random
{
public:
	static float getRandomFloat(float minIncluded, float maxExcluded);
	static int getRandomInt(int minIncluded, int maxExcluded);

	static std::random_device rd;
	static std::mt19937 gen;

private:
	Random() = default;
	~Random() = default;
};