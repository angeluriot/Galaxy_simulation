#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <thread>
#include <atomic>
#include <variant>
#include <iostream>
#include <array>
#include <functional>


#define GLM_FORCE_INLINE
#define GLM_FORCE_SIZE_T_LENGTH

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

glm::dvec3 create_spherical(const double &radius, const double &phi, const double &theta);

double get_x(const double radius, const double phi, const double theta);

double get_y(const double radius, const double phi, const double theta);

double get_z(const double radius, const double phi, const double theta);

namespace glm {
	[[nodiscard]] double get_phi(const glm::dvec3 &vecteur);

	[[nodiscard]] double get_theta(const glm::dvec3 &vecteur);
}

#endif