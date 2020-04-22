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

	bool as_stars{ false };        // Présence d'étoiles dans le bloc
	bool as_children{ false };    // Présence de blocs enfants
	bool as_parents{ false };        // Présence de blocs parents
	std::size_t parent{ 0 };            // Indice du bloc parent. EDIT : 0 par défaut, ou une autre valeur ? Genre le max de int.
	glm::dvec3 position{ 0, 0, 0 };        // Position du bloc
	double mass{ 0 };            // Masse contenue dans le bloc (en kilogrames)
	glm::dvec3 mass_center{ 0, 0, 0 };    // Centre de gravité du bloc
	size_t nb_stars{ 0 };        // Nombre d'étoiles contenues dans le block
	double size{ 0 }, halfsize{ 0 };    // Taille du bloc (en mètres)

	std::variant<Star::container::iterator, std::vector<Block>> contains;

	Block() = default;

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