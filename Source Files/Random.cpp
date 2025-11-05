#include "../Header Files/Random.h"

using namespace std;

std::random_device Random::rd;
std::mt19937 Random::gen(Random::rd());

float Random::getRandomFloat(float minIncluded, float maxExcluded)
{
	uniform_real_distribution<float> dis(minIncluded, maxExcluded);
	return dis(Random::gen);
}

int Random::getRandomInt(int minIncluded, int maxExcluded)
{
	uniform_int_distribution<int> dis = uniform_int_distribution<int>(minIncluded, maxExcluded - 1);
	return dis(Random::gen);
}