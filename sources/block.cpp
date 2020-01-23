#include "block.h"


std::array<Star::range, 8> set_octree(Star::range stars, Vector pivot)
{
	std::array<std::function<bool(const Star & star)>, 3> testStarAxis =
	{
		[pivot](const Star& star) {return star.position.x < pivot.x; },
		[pivot](const Star& star) {return star.position.y < pivot.y; },
		[pivot](const Star& star) {return star.position.z < pivot.z; }
	};

	std::array<Star::range, 8> result;
	int iPart = 0;
	Star::container::iterator itX = std::partition(stars.begin, stars.end, testStarAxis[0]);
	auto xParts = std::array{ Star::range{stars.begin, itX}, Star::range{itX, stars.end} };

	for (auto& part : xParts)
	{
		Star::container::iterator itY = std::partition(part.begin, part.end, testStarAxis[1]);
		auto yParts = std::array{ Star::range{part.begin, itY}, Star::range{itY, part.end} };

		for (auto& part : yParts)
		{
			Star::container::iterator itZ = std::partition(part.begin, part.end, testStarAxis[2]);
			result[iPart++] = Star::range{ part.begin, itZ };
			result[iPart++] = Star::range{ itZ, part.end };
		}
	}

	return result;
}



// Construit un bloc

Block::Block()
{
	as_stars = false;
	mass_center = Vector(0., 0., 0.);
	as_children = false;
	as_parents = false;
	position = Vector(0., 0., 0.);
	mass = 0.;
	size = halfsize = 0.;
	nb_stars = 0;
}



// Construit un bloc à partir d'un autre bloc

Block::Block(const Block& block)
{
	as_stars = false;
	mass_center = Vector(0., 0., 0.);
	as_children = false;
	as_parents = false;
	position = Vector(0., 0., 0.);
	mass = 0.;
	size = halfsize = 0.;
	nb_stars = 0;
}



// Assignation

void Block::operator=(const Block& block)
{
	as_stars = block.as_stars;
	mass_center = block.mass_center;
	as_children = block.as_children;
	as_parents = block.as_parents;
	parent = block.parent;
	position = block.position;
	mass = block.mass;
	size = block.size;
	halfsize = block.halfsize;
	contains = block.contains;
	nb_stars = block.nb_stars;
}



// Met à jour la masse et le centre de gravité de chaque blocks

void Block::update_mass_center_and_mass(const Star::range& galaxy)
{
	mass_center = Vector(0., 0., 0.);
	mass = 0.;

	for (auto it = galaxy.begin; it != galaxy.end; ++it)
	{
		mass_center += it->position * it->mass;
		mass += it->mass;
	}
	mass_center = mass_center / mass;
}



// Divise un bloc en 8 plus petits

void Block::divide(Star::range stars)
{
	if (stars.begin == stars.end) // pas d'etoile
	{
		contains = stars.begin; // pas très utile, permet de clear la memoire de array<Block, 8> si c'était sa valeur précédente
		nb_stars = 0;
		mass = 0.;
		mass_center = Vector(0., 0., 0.);
		as_children = false;
	}

	else if (std::next(stars.begin) == stars.end) // une étoile
	{
		contains = stars.begin;
		nb_stars = 1;
		mass = stars.begin->mass;
		mass_center = stars.begin->position;
		as_children = false;
	}

	else
	{
		if (contains.index() != 1)
			contains = std::vector<Block>(8);

		nb_stars = std::distance(stars.begin, stars.end);
		as_children = true;

		Block block;

		block.as_parents = true;
		block.set_size(halfsize);

		Vector posis[] = {
			{position.x - size / 4., position.y - size / 4., position.z - size / 4.},
			{position.x - size / 4., position.y - size / 4., position.z + size / 4.},
			{position.x - size / 4., position.y + size / 4., position.z - size / 4.},
			{position.x - size / 4., position.y + size / 4., position.z + size / 4.},
			{position.x + size / 4., position.y - size / 4., position.z - size / 4.},
			{position.x + size / 4., position.y - size / 4., position.z + size / 4.},
			{position.x + size / 4., position.y + size / 4., position.z - size / 4.},
			{position.x + size / 4., position.y + size / 4., position.z + size / 4.}
		};

		auto& myblocks = std::get<1>(contains);
		auto partitions_stars = set_octree(stars, position);
		double new_mass = 0.;
		Vector new_mass_center = Vector(0., 0., 0.);
		int i_add = 0;

		for (int ibloc = 0; ibloc < 8; ibloc++)
		{
			// bloc 1
			myblocks[ibloc] = block;
			myblocks[ibloc].position = posis[ibloc];
			// block.stars_maj(galaxy, blocks);
			//myblocks[ibloc].mass_center_and_mass_maj(partitions_stars[ibloc]);
			myblocks[ibloc].divide(partitions_stars[ibloc]);

			if (myblocks[ibloc].nb_stars > 0)
			{
				new_mass += myblocks[ibloc].mass;
				new_mass_center += myblocks[ibloc].mass_center * myblocks[ibloc].mass;
				i_add++;
			}
		}

		mass = new_mass;
		mass_center = new_mass_center / new_mass;
	}
}


void Block::set_size(double size)
{
	this->size = size;
	this->halfsize = size / static_cast<double>(2.);
}


// Dit si l'étoile est dans le bloc

bool is_in(const Block& block, const Star& star)
{
	return (block.position.x + block.size / 2. > star.position.x and block.position.x - block.size / 2. < star.position.x
		and block.position.y + block.size / 2. > star.position.y and block.position.y - block.size / 2. < star.position.y
		and block.position.z + block.size / 2. > star.position.z and block.position.z - block.size / 2. < star.position.z);
}



// Génère les blocs

void create_blocks(const double& area, Block& block, Star::range& alive_galaxy)
{
	block.set_size(area * 3.);
	block.divide(alive_galaxy);
}