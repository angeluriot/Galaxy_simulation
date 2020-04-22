#ifndef BLOCK_H
#define BLOCK_H

#include "vector.h"
#include "star.h"



// Classe définissant une zone de l'algorithme de Barnes–Hut. EDIT : commentaire de doc :
/**
 * \class Block
 * \brief Une zone de l'algorithme de Barnes-Hut
 */
class Block {

public:

	bool as_stars;        // Présence d'étoiles dans le bloc
	bool as_children;    // Présence de blocs enfants
	bool as_parents;        // Présence de blocs parents
	int parent;            // Indice du bloc parent
	Vector position;        // Position du bloc
	double mass;            // Masse contenue dans le bloc (en kilogrames)
	Vector mass_center;    // Centre de gravité du bloc
	size_t nb_stars;        // Nombre d'étoiles contenues dans le block
	double size, halfsize;    // Taille du bloc (en mètres)

	std::variant<Star::container::iterator, std::vector<Block>> contains;

	Block();

	virtual ~Block() = default;

	Block(const Block &block) = default;

	Block &operator=(const Block &block) = default;

	void update_mass_center_and_mass(const Star::range &stars);

	void divide(Star::range galaxy);

	void set_size(const double &size);
};

/**
 * \brief Permet de savoir si l'étoile est dans un bloc.
 * \param block
 * \param star
 * \return
 */
bool is_in(const Block &block, const Star &star);

/**
 * \brief Génère les blocs.
 * \param area
 * \param block
 * \param galaxy
 */
void create_blocks(const double &area, Block &block, Star::range &galaxy);

#endif