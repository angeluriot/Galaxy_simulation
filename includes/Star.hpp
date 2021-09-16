#ifndef STAR_HPP
#define STAR_HPP

#include "libraries.hpp"

class Block;

class Star
{
	public:

		dim::Vector3			previous_pos;
		dim::Vector3			position;
		dim::Vector3			speed;
		dim::Vector3			previous_acc;
		dim::Vector3			acceleration;
		std::array<float, 5>	closest_stars;
		bool					alive;

		Star();
		Star(const Star& other) = default;

		Star& operator=(const Star& other) = default;

		void force_calculation(const Block& block);
		void update_acceleration();
		void update_position();
		float get_brightness() const;
};

#endif
