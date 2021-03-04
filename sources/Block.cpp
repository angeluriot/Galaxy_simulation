#include "Block.h"
#include "Simulation.h"

// Construit un bloc

Block::Block()
{
	clear();
}

// Construit le bloc originel

Block::Block(Simulation& simulation)
{
	reload(simulation);
}

// Constuit un bloc enfant

Block::Block(Block& parent, uint8_t location)
{
	this->parent = &parent;
	position = parent.position + (locate(location) * (parent.size / 4.f));
	size = parent.size / 2.f;
	stars.clear();
	children.clear();
	mass_center.clear();

	for (Star* star : parent.stars)
		if (is_in(star->position))
			stars.push_back(star);

	if (stars.size() == 0)
		return;

	if (stars.size() > 1)
		for (uint8_t location = 0; location < 8; location++)
		{
			children.push_back(Block(*this, location));

			if (children.back().stars.size() == 0)
				children.pop_back();
		}

	for (Star* star : stars)
		mass_center += star->position;

	mass_center /= static_cast<Float>(stars.size());
}

// Construit un bloc é partir d'un autre bloc

Block::Block(const Block& block)
{
	*this = block;
}

// Assignation

void Block::operator=(const Block& block)
{
	parent = block.parent;
	children = block.children;
	position = block.position;
	mass_center = block.mass_center;
	stars = block.stars;
	size = block.size;
}

// Recrée le bloc

void Block::reload(Simulation& simulation)
{
	clear();
	parent = NULL;
	size = simulation.area * 3.f;

	for (auto it = simulation.galaxy.begin(); it != simulation.galaxy.end();)
	{
		if (is_in(it->position))
		{
			stars.push_back(&(*it));
			++it;
		}

		else
		{
			auto temp = it;
			++it;
			simulation.galaxy.erase(temp);
		}
	}

	for (uint8_t location = 0; location < 8; location++)
	{
		children.push_back(Block(*this, location));

		if (children.back().stars.size() == 0)
			children.pop_back();
	}
}

// Dit si l'étoile est dans le bloc

bool Block::is_in(const Vector& star_position) const
{
	return (position.x + size / 2.f > star_position.x && position.x - size / 2.f < star_position.x &&
			position.y + size / 2.f > star_position.y && position.y - size / 2.f < star_position.y &&
			position.z + size / 2.f > star_position.z && position.z - size / 2.f < star_position.z);
}

// Nettoie les infos du bloc

void Block::clear()
{
	parent = NULL;
	children.clear();
	position.clear();
	mass_center.clear();
	stars.clear();
	size = 0.f;
}

// Affiche les blocs (Ne marche pas en vue par défaut)

void Block::draw(const Float& area, sf::Image& image, View view) const
{
	sf::Vector2f screen_size = simu_to_screen(size, area);
	sf::Vector2f screen_pos = simu_to_screen(position, area, view);

	for (uint16_t i = 0; i < 2; i++)
		for (uint16_t j = 0; j < screen_size.y; j++)
		{
			int16_t x = screen_pos.x - screen_size.x / 2.f + i * screen_size.x;
			int16_t y = screen_pos.y - screen_size.y / 2.f + j;

			if (x >= 0 && x < image.getSize().x && y >= 0 && y < image.getSize().y)
				image.setPixel(x, y, sf::Color::Green);
		}

	for (uint16_t j = 0; j < 2; j++)
		for (uint16_t i = 0; i < screen_size.x; i++)
		{
			int16_t x = screen_pos.x - screen_size.x / 2.f + i;
			int16_t y = screen_pos.y - screen_size.y / 2.f + j * screen_size.y;

			if (x >= 0 && x < image.getSize().x && y >= 0 && y < image.getSize().y)
				image.setPixel(x, y, sf::Color::Green);
		}

	for (const Block& block : children)
		block.draw(area, image, view);
}

// Donne la position d'un bloc enfant é partir de son indice

Vector locate(uint8_t location)
{
	switch (location)
	{
	case 0:
		return Vector(-1.f, -1.f, -1.f);
	case 1:
		return Vector(-1.f, -1.f, 1.f);
	case 2:
		return Vector(-1.f, 1.f, -1.f);
	case 3:
		return Vector(-1.f, 1.f, 1.f);
	case 4:
		return Vector(1.f, -1.f, -1.f);
	case 5:
		return Vector(1.f, -1.f, 1.f);
	case 6:
		return Vector(1.f, 1.f, -1.f);
	case 7:
		return Vector(1.f, 1.f, 1.f);
	default:
		throw std::invalid_argument("0 <= location <= 7");
	}
}