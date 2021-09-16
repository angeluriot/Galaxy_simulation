#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "libraries.hpp"

class Star;

class Block
{
	public:

		Block*								parent;
		std::list<Block>					children;
		dim::Vector3						position;
		dim::Vector3						mass_center;
		std::vector<Star*>					stars;
		float								size;

		static std::array<dim::Vector3, 8>	locations;

		Block();
		Block(Block& parent, const dim::Vector3& location);
		Block(const Block& other) = default;

		Block& operator=(const Block& other) = default;

		void reload();
		bool is_in(const dim::Vector3& position) const;
		void clear();
		void draw() const;
};

#endif
