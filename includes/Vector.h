#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#include <stdexcept>
#include <iostream>

#define PI 3.14159265359 // Pi

typedef float Float;

// Classe définissant un vecteur

class Vector
{
public:

	Float		x;	// coordonnée x
	Float		y;	// coordonnée y
	Float		z;	// coordonnée z

	// Constructeurs

				Vector();
				Vector(const Vector& vector);
				Vector(const Float& x, const Float& y, const Float& z);

	// Assignations

	void		operator=(const Vector& vector);
	void		operator+=(const Vector& vector);
	void		operator-=(const Vector& vector);
	void		operator*=(const Float& number);
	void		operator/=(const Float& number);

	// Récupérer

	Float		get_norm() const;
	Float		get_norm_2() const;
	Float		get_theta() const;
	Float		get_phi() const;

	// Modifier

	void		set_norm(const Float& norm);
	void		set_theta(const Float& theta);
	void		set_phi(const Float& phi);
	void		normalize();
	void		clear();
};

// Constructeurs

Vector			Vector_cartesian(const Float& x, const Float& y, const Float& z);
Vector			Vector_spherical(const Float& norm, const Float& theta, const Float& phi);

// Opérateurs

Vector			operator+(const Vector& vector_1, const Vector& vector_2);
Vector			operator-(const Vector& vector_1, const Vector& vector_2);
Vector			operator-(const Vector& vector);
Vector			operator*(const Vector& vector, const Float& number);
Vector			operator*(const Float& number, const Vector& vector);
Float			operator*(const Vector& vector_1, const Vector& vector_2);
Vector			operator^(const Vector& vector_1, const Vector& vector_2);
Vector			operator/(const Vector& vector, const Float& number);
bool			operator==(const Vector& vector_1, const Vector& vector_2);
bool			operator!=(const Vector& vector_1, const Vector& vector_2);
std::ostream&	operator<<(std::ostream& os, const Vector& vector);

// Récupérer

Float			get_x(const Float& norm, const Float& theta, const Float& phi);
Float			get_y(const Float& norm, const Float& theta, const Float& phi);
Float			get_z(const Float& norm, const Float& theta, const Float& phi);
Float			get_distance(const Vector& point_1, const Vector& point_2);
Float			get_distance_2(const Vector& point_1, const Vector& point_2);
Float			get_theta(const Vector& point_1, const Vector& point_2);
Float			get_phi(const Vector& point_1, const Vector& point_2);
Vector			normalized(const Vector& vector);

#endif