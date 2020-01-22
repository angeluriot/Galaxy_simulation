#include "block.h"



// Construit un bloc

Block::Block()
{
	as_stars = false;
	stars.clear();
	mass_center = Vector(0., 0., 0.);
	index = 0;
	as_children = false;
	as_parents = false;
	parent = 0;
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
	parent = block.parent;
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
	parent = block.parent;
	children = block.children;
	position = block.position;
	mass = block.mass;
	size = block.size;
}



// Met à jour les étoiles contenues dans le bloc

void Block::update_stars(std::vector<Star>& galaxy, std::vector<Block>& blocks)
{
	stars.clear();

	for (int i = 0; i < blocks[parent].stars.size(); i++)
	{
		if (is_in(*this, galaxy[blocks[parent].stars[i]]))
		{
			stars.push_back(blocks[parent].stars[i]);
			galaxy[blocks[parent].stars[i]].block_index = index;

			if (!(as_stars))
				as_stars = true;
		}
	}
}



// Met à jour la masse et le centre de gravité de chaque blocks

void update_mass_center_and_mass(Block& block, std::vector<Star>& galaxy, std::vector<Block>& blocks)
{
	if (block.stars.size() == 0.)
	{
		block.mass = 0.;
		block.mass_center = block.position;
	}

	else if (block.stars.size() == 1.)
	{
		block.mass = galaxy[block.stars[0]].mass;
		block.mass_center = galaxy[block.stars[0]].position;
	}

	else
	{
		block.mass = 0.;
		block.mass_center = Vector(0., 0., 0.);

		for (int i = 0; i < 8; i++)
		{
			update_mass_center_and_mass(blocks[block.children[i]], galaxy, blocks);
			block.mass += blocks[block.children[i]].mass;

			if (blocks[block.children[i]].stars.size() > 0)
				block.mass_center += blocks[block.children[i]].mass_center;
		}

		block.mass_center /= block.mass;
	}
}



// Divise un bloc en 8 plus petits

void Block::divide(int& index_value, std::vector<Star>& galaxy, std::vector<Block>& blocks, std::vector<Block>& blocks_temp)
{
	as_children = true;

	Block block;

	block.as_parents = true;
	block.parent = index;
	block.size = size / 2.;

	// bloc 1
	block.position = Vector(position.x - size / 4., position.y - size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 2
	block.position = Vector(position.x - size / 4., position.y - size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 3
	block.position = Vector(position.x - size / 4., position.y + size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 4
	block.position = Vector(position.x - size / 4., position.y + size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 5
	block.position = Vector(position.x + size / 4., position.y - size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 6
	block.position = Vector(position.x + size / 4., position.y - size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 7
	block.position = Vector(position.x + size / 4., position.y + size / 4., position.z - size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
	blocks_temp.push_back(block);

	// bloc 8
	block.position = Vector(position.x + size / 4., position.y + size / 4., position.z + size / 4.);
	block.index = index_value;
	index_value++;
	children.push_back(block.index);
	block.update_stars(galaxy, blocks);
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
		if (is_in(block, galaxy[i]))
		{
			block.stars.push_back(i);
			galaxy[i].block_index = block.index;

			if (!(block.as_stars))
				block.as_stars = true;
		}

		else
			galaxy[i].is_alive = false;
	}

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
		if (blocks[i].stars.size() > 1)
			blocks[i].divide(index_value, galaxy, blocks, blocks_temp);

		if (blocks_temp.size() > 0)
		{
			for (int j = 0; j < blocks_temp.size(); j++)
				blocks.push_back(blocks_temp[j]);

			blocks_temp.clear();
		}
	}

	update_mass_center_and_mass(blocks[0], galaxy, blocks);
}