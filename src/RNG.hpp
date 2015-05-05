#pragma once

#include <random>

class RNG
{
public:
	RNG();
	RNG(unsigned long);

	void seed(unsigned long);

	float generate(float a = 0.0, float b = 1.0)
	{
		std::uniform_real_distribution<float> d(a, b);
		return d(generator);
	}

	int generate(int a, int b)
	{
		std::uniform_int_distribution<int> d(a, b);
		return d(generator);
	}

private:
	std::default_random_engine generator;

public:
	static RNG managed;
	static RNG unmanaged;
};