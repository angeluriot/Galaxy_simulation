#include "dim/dimension3D.hpp"

namespace dim
{
	int random_int(int min, int max)
	{
		return rand() % (max - min) + min;
	}

	float random_float(float min, float max)
	{
		return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min) + min;
	}

	bool random_probability(float probability)
	{
		if (probability < 0.f)
			return false;

		if (probability < 1.f)
			return (rand() / static_cast<float>(RAND_MAX) < probability);

		return true;
	}

	bool sleep_every(unsigned int milliseconds)
	{
		static sf::Clock clock;

		if (clock.getElapsedTime() >= sf::milliseconds(milliseconds))
		{
			clock.restart();
			return true;
		}

		else
			return false;
	}
}
