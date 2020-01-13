#include "Block.h"
#include "Utils.h"
#include "Vector.h"
#include "Star.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <time.h>



// Construit un bloc

Block::Block()
{
	as_stars = false;
	stars.clear();
	mass_center = Vector(0., 0., 0.);
	index = 0;
	as_children = false;
	as_parents = false;
	parents.clear();
	children.clear();
	position = Vector(0., 0., 0.);
	mass = 0.;
	size = 0.;
}



// Construit un bloc à partir d'un autre bloc

Block::Block(const Block& block)
{
	as_stars = block.as_stars;
	stars = block.stars;
	mass_center = block.mass_center;
	index = block.index;
	as_children = block.as_children;
	as_parents = block.as_parents;
	parents = block.parents;
	children = block.children;
	position = block.position;
	mass = block.mass;
	size = block.size;
}



// Assignation

void Block::operator=(const Block& block)
{
	as_stars = block.as_stars;
	stars = block.stars;
	mass_center = block.mass_center;
	index = block.index;
	as_children = block.as_children;
	as_parents = block.as_parents;
	parents = block.parents;
	children = block.children;
	position = block.position;
	mass = block.mass;
	size = block.size;
}



// Met à jour les étoiles contenues dans le bloc

void Block::stars_maj(std::vector<Star>& galaxy, std::vector<Block>& blocks)
{
	stars.clear();

	for (int i = 0; i < blocks.at(parents.at(parents.size() - 1)).stars.size(); i++)
	{
		if (is_in(*this, galaxy.at(blocks.at(parents.at(parents.size() - 1)).stars.at(i))))
		{
			stars.push_back(blocks.at(parents.at(parents.size() - 1)).stars.at(i));
			galaxy.at(blocks.at(parents.at(parents.size() - 1)).stars.at(i)).block_index = index;

			if (!(as_stars))
				as_stars = true;
		}
	}
}



// Met à jour le centre de gravité et la masse du bloc

void Block::mass_center_and_mass_maj(const std::vector<Star>& galaxy)
{
	mass_center = Vector(0., 0., 0.);
	mass = 0.;

	for (int i = 0; i < stars.size(); i++)
	{
		mass_center += galaxy.at(stars.at(i)).position * galaxy.at(stars.at(i)).mass;
		mass += galaxy.at(stars.at(i)).mass;
	}

	mass_center = mass_center / mass;
}



// Divise un bloc en 8 plus petits

void Block::divide(int& index_value, std::vector<Star>& galaxy, std::vector<Block>& blocks, std::vector<Block>& blocks_temp)
{
	as_children = true;

	Block block;

	block.as_parents = true;
	block.parents = parents;
	block.parents.push_back(index);
	block.size = size / 2.;

	// bloc 1
	block.position = Vector(position.x - size / 4., position.y - size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 2
	block.position = Vector(position.x - size / 4., position.y - size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 3
	block.position = Vector(position.x - size / 4., position.y + size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 4
	block.position = Vector(position.x - size / 4., position.y + size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 5
	block.position = Vector(position.x + size / 4., position.y - size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 6
	block.position = Vector(position.x + size / 4., position.y - size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 7
	block.position = Vector(position.x + size / 4., position.y + size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);

	// bloc 8
	block.position = Vector(position.x + size / 4., position.y + size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.stars_maj(galaxy, blocks);
	block.mass_center_and_mass_maj(galaxy);
	blocks_temp.push_back(block);
}



// Dit si l'étoile est dans le bloc

bool is_in(const Block& block, const Star& star)
{
	return (block.position.x + block.size / 2. > star.position.x and block.position.x - block.size / 2. < star.position.x
		and block.position.y + block.size / 2. > star.position.y and block.position.y - block.size / 2. < star.position.y
		and block.position.z + block.size / 2. > star.position.z and block.position.z - block.size / 2. < star.position.z);
}



// Crée le premier bloc

void initialise_blocks(int& index_value, const double& area, std::vector<Star>& galaxy, std::vector<Block>& blocks)
{
	Block block;

	block.index = index_value;
	index_value++;
	block.size = area * 3.;

	for (int i = 0; i < galaxy.size(); i++)
	{
		if (is_in(block, galaxy.at(i)))
		{
			block.stars.push_back(i);
			galaxy.at(i).block_index = block.index;

			if (!(block.as_stars))
				block.as_stars = true;
		}

		else
			galaxy.at(i).is_alive = false;
	}

	block.mass_center_and_mass_maj(galaxy);
	blocks.push_back(block);
}



// Génère les blocs (l'utilisation de "blocks_temp" ne sert qu'à augmenter la limite des "std:::vector<>" pour pouvoir mettre plus d'étoiles)

void create_blocks(const double& area, std::vector<Block>& blocks, std::vector<Star>& galaxy, std::vector<Block>& blocks_temp)
{
	blocks.clear();
	int index_value = 0;

	initialise_blocks(index_value, area, galaxy, blocks);

	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks.at(i).stars.size() > 1)
			blocks.at(i).divide(index_value, galaxy, blocks, blocks_temp);

		if (blocks_temp.size() > 0)
		{
			for (int j = 0; j < blocks_temp.size(); j++)
				blocks.push_back(blocks_temp.at(j));

			blocks_temp.clear();
		}
	}
}