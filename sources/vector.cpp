#include "vector.h"
#include "utils.h"

// Construit un vecteur à partir de ses coordonnées sphériques

glm::dvec3 create_spherical(const double &radius, const double &phi, const double &theta) {
	return glm::dvec3(get_x(radius, phi, theta), get_y(radius, phi, theta), get_z(radius, phi, theta));
}

// Donne la valeur cartésienne x à partir des coordonnées sphériques (en mètres)

double get_x(const double radius, const double phi, const double theta) {
	return std::cos(phi) * std::sin(theta) * radius;
}

// Donne la valeur cartésienne y à partir des coordonnées sphériques (en mètres)

double get_y(const double radius, const double phi, const double theta) {
	return sin(phi) * sin(theta) * radius;
}

// Donne la valeur cartésienne z à partir des coordonnées sphériques (en mètres)

double get_z(const double radius, const double phi, const double theta) {
	return cos(theta) * radius;
}

double glm::get_phi(const glm::dvec3 &vecteur) {
	auto vector = vecteur;
	vector.z = 0.;

	if (vecteur.y > 0)
		return acos(vector.x / glm::length(vector));

	if (vector.y < 0)
		return 2 * PI - acos(vector.x / glm::length(vector));
}

double glm::get_theta(const glm::dvec3 &vecteur) {
	return glm::acos(vecteur.z / glm::length(vecteur));
}