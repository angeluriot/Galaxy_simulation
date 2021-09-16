#include "Block.hpp"
#include "Simulation.hpp"

std::array<dim::Vector3, 8>	Block::locations =
{
	dim::Vector3(-1.f, -1.f, -1.f),
	dim::Vector3(-1.f, -1.f,  1.f),
	dim::Vector3(-1.f,  1.f, -1.f),
	dim::Vector3(-1.f,  1.f,  1.f),
	dim::Vector3( 1.f, -1.f, -1.f),
	dim::Vector3( 1.f, -1.f,  1.f),
	dim::Vector3( 1.f,  1.f, -1.f),
	dim::Vector3( 1.f,  1.f,  1.f)
};

Block::Block()
{
	clear();
}

Block::Block(Block& parent, const dim::Vector3& location)
{
	this->parent = &parent;
	position = parent.position + (location * (parent.size / 4.f));
	size = parent.size / 2.f;
	stars.clear();
	children.clear();
	mass_center.clear();

	for (Star* star : parent.stars)
		if (is_in(star->position))
			stars.push_back(star);

	if (stars.empty())
		return;

	if (stars.size() > 1)
		for (dim::Vector3& location : locations)
		{
			children.emplace_back(*this, location);

			if (children.back().stars.empty())
				children.pop_back();
		}

	for (Star* star : stars)
		mass_center += star->position;

	mass_center /= static_cast<float>(stars.size());
}

void Block::reload()
{
	clear();
	size = Simulation::galaxy_diameter * 3.f;

	for (Star& star : Simulation::galaxy)
	{
		if (is_in(star.position))
			stars.push_back(&star);

		else
			star.alive = false;
	}

	for (dim::Vector3& location : locations)
	{
		children.emplace_back(*this, location);

		if (children.back().stars.empty())
			children.pop_back();
	}
}

bool Block::is_in(const dim::Vector3& position) const
{
	return (this->position.x + size / 2.f > position.x && this->position.x - size / 2.f < position.x &&
			this->position.y + size / 2.f > position.y && this->position.y - size / 2.f < position.y &&
			this->position.z + size / 2.f > position.z && this->position.z - size / 2.f < position.z);
}

void Block::clear()
{
	parent = nullptr;
	children.clear();
	position.clear();
	mass_center.clear();
	stars.clear();
	size = 0.f;
}

void Block::draw() const
{
	
}
