#pragma once
#include <random>

class Random {
	public:
		Random(int seed = -1);
		float range(float min, float max);
		int range(int min, int max);
	private:
		std::mt19937 mt;
};

