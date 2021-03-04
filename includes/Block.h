#ifndef BLOCK_H
#define BLOCK_H
#include "Vector.h"
#include "Star.h"
#include "utils.h"

class Simulation;

// Classe définissant une zone de l'algorithme de Barnes-Hut

class Block
{
public:

	Block*				parent;			// Pointeur vers le bloc parent
	std::list<Block>	children;		// Les blocs enfants
	Vector				position;		// Position du bloc
	Vector				mass_center;	// Centre de gravité du bloc
	std::vector<Star*>	stars;			// Liste de pointeurs vers les étoiles contenues dans le block
	Float				size;			// Taille du bloc
	
						Block();
						Block(Simulation& simulation);
						Block(Block& parent, uint8_t location);
						Block(const Block& block);

	void				operator=(const Block& block);

	void				reload(Simulation& simulation);
	bool				is_in(const Vector& star_position) const;
	void				clear();
	void				draw(const Float& area, sf::Image& image, View view) const;
};

Vector					locate(uint8_t location);

#endif