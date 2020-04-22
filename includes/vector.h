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



// Classe définissant un vecteur

class Vector {

public:

	double x; // coordonnée x (en mètres)
	double y; // coordonnée y (en mètres)
	double z; // coordonnée z (en mètres)

	Vector();

	Vector(const Vector &vector);

	Vector(const double &x, const double &y, const double &z);

	Vector &operator=(const Vector &vector) = default;

	void operator+=(const Vector &vector);

	void operator-=(const Vector &vector);

	void operator*=(const double &number);

	void operator/=(const double &number);

	[[nodiscard]] double get_radius() const;

	[[nodiscard]] double get_phi() const;

	[[nodiscard]] double get_theta() const;
};

Vector create_spherical(const double &radius, const double &phi, const double &theta);

Vector operator+(const Vector &vector_1, const Vector &vector_2);

Vector operator-(const Vector &vector_1, const Vector &vector_2);

Vector operator*(const Vector &vector, const double &number);

Vector operator*(const double &number, const Vector &vector);

double operator*(const Vector &vector_1, const Vector &vector_2);

Vector operator^(const Vector &vector_1, const Vector &vector_2);

Vector operator/(const Vector &vector, const double &number);

bool operator==(const Vector &vector_1, const Vector &vector_2);

bool operator!=(const Vector &vector_1, const Vector &vector_2);

double get_x(const double &radius, const double &phi, const double &theta);

double get_y(const double &radius, const double &phi, const double &theta);

double get_z(const double &radius, const double &phi, const double &theta);

double get_distance(const Vector &point_1, const Vector &point_2);

double get_phi(const Vector &point_1, const Vector &point_2);

double get_theta(const Vector &point_1, const Vector &point_2);

Vector normalize(const Vector &vector);

#endif