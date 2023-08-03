#include "RandomBetween.h"

int RandomBetween(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(engine);
}; // temp place for randombe