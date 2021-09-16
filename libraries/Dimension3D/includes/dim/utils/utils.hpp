#ifndef DIM_UTILS_HPP
#define DIM_UTILS_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	constexpr float pi = 3.14159265359f; // The mathematical constant pi.

	/**
	 * @brief Clamp a number between two values.
	 *
	 * @param number the number to clamp
	 * @param min the minimum value
	 * @param max the maximum value
	 * @return the clamped number
	 */
	template <typename T> T clamp(const T& number, const T& min, const T& max)
	{
		return std::min(std::max(number, min), max);
	}

	/**
	 * @brief Give a random integer between two values.
	 *
	 * @param min the minimum value
	 * @param max the maximum value
	 * @return the random integer
	 */
	int random_int(int min, int max);

	/**
	 * @brief Give a random float number between two values.
	 *
	 * @param min the minimum value
	 * @param max the maximum value
	 * @return the random float number
	 */
	float random_float(float min, float max);

	/**
	 * @brief Return true with the given probability.
	 *
	 * @param probability the probability
	 * @return true with the given probability, false otherwise
	 */
	bool random_probability(float probability);

	/**
	 * @brief Return true every time the time is up.
	 *
	 * @param milliseconds the time (in milliseconds)
	 * @return true every time the time is up, false otherwise
	 */
	bool sleep_every(unsigned int milliseconds);
}

#endif
