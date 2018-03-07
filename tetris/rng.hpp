#pragma once
#include <random>
#include <cstdint>

// rand() IS NOT SECURE
// THIS IS THE PROPER C++ WAY
// TO GENERATE RANDOM NUMBERS
namespace rng
{
	// GET RNG ENGINE
	inline std::mt19937& get_generator()
	{
		thread_local std::mt19937 generator(std::random_device{}());
		return generator;
	}

	// GENERATE RANDOM INTEGER OF TYPE T
	template <typename T>
	inline T get_int(T min, T max)
	{
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(get_generator());
	}
}
