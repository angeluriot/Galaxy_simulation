#include "Vector.h"

// Construit un vecteur

Vector::Vector()
{
	x = 0.;
	y = 0.;
	z = 0.;
}

// Construit un vecteur à partir d'un autre vecteur

Vector::Vector(const Vector& vector)
{
	*this = vector;
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector::Vector(const Float& x, const Float& y, const Float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

// Assignations

void Vector::operator=(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector::operator+=(const Vector& vector)
{
	*this = *this + vector;
}

void Vector::operator-=(const Vector& vector)
{
	*this = *this - vector;
}

void Vector::operator*=(const Float& number)
{
	*this = *this * number;
}

void Vector::operator/=(const Float& number)
{
	*this = *this / number;
}

// Donne la norme du vecteur

Float Vector::get_norm() const
{
	return sqrt(x * x + y * y + z * z);
}

// Donne la norme du vecteur au carré

Float Vector::get_norm_2() const
{
	return x * x + y * y + z * z;
}

// Donne l'angle theta du vecteur

Float Vector::get_theta() const
{
	if (get_norm() == 0.)
		throw std::logic_error("null vector does not have theta");

	return acos(z / get_norm());
}

// Donne l'angle phi du vecteur

Float Vector::get_phi() const
{
	if (get_norm() == 0.)
		throw std::logic_error("null vector does not have phi");

	Vector vector = *this;
	vector.z = 0.;

	if (vector.y > 0)
		return acos(vector.x / vector.get_norm());

	if (vector.y < 0)
		return 2 * PI - acos(vector.x / vector.get_norm());
}

// Modifie la norme du vecteur

void Vector::set_norm(const Float& norm)
{
	*this = normalized(*this) * norm;
}

// Modifie l'angle theta du vecteur

void Vector::set_theta(const Float& theta)
{
	*this = Vector_spherical(get_norm(), theta, get_phi());
}

// Modifie l'angle phi du vecteur

void Vector::set_phi(const Float& phi)
{
	*this = Vector_spherical(get_norm(), get_theta(), phi);
}

// Normalise le vecteur

void Vector::normalize()
{
	if (get_norm() != 0.)
		*this /= get_norm();
}

// Met toutes les composantes à zéro

void Vector::clear()
{
	*this = Vector();
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector Vector_cartesian(const Float& x, const Float& y, const Float& z)
{
	return Vector(x, y, z);
}

// Construit un vecteur à partir de ses coordonnées sphériques

Vector Vector_spherical(const Float& norm, const Float& theta, const Float& phi)
{
	return Vector(get_x(norm, theta, phi), get_y(norm, theta, phi), get_z(norm, theta, phi));
}

// Addition

Vector operator+(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z);
}

// Soustraction

Vector operator-(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z);
}

// Inversion

Vector operator-(const Vector& vector)
{
	return Vector(0., 0., 0.) - vector;
}

// Produits

Vector operator*(const Vector& vector, const Float& number)
{
	return Vector(vector.x * number, vector.y * number, vector.z * number);
}

Vector operator*(const Float& number, const Vector& vector)
{
	return Vector(number * vector.x, number * vector.y, number * vector.z);
}

// Produit scalaire

Float operator*(const Vector& vector_1, const Vector& vector_2)
{
	return vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
}

// Produit vectoriel

Vector operator^(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.y * vector_2.z - vector_1.z * vector_2.y, vector_1.z * vector_2.x - vector_1.x * vector_2.z, vector_1.x * vector_2.y - vector_1.y * vector_2.x);
}

// Division

Vector operator/(const Vector& vector, const Float& number)
{
	if (number == 0.)
		throw std::invalid_argument("division by 0");

	return Vector(vector.x / number, vector.y / number, vector.z / number);
}

// Egalités

bool operator==(const Vector& vector_1, const Vector& vector_2)
{
	return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z);
}

bool operator!=(const Vector& vector_1, const Vector& vector_2)
{
	return (!(vector_1 == vector_2));
}

// Affichage

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
	os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return os;
}

// Donne la valeur cartésienne x à partir des coordonnées sphériques

Float get_x(const Float& norm, const Float& theta, const Float& phi)
{
	return sin(theta) * cos(phi) * norm;
}

// Donne la valeur cartésienne y à partir des coordonnées sphériques

Float get_y(const Float& norm, const Float& theta, const Float& phi)
{
	return sin(theta) * sin(phi) * norm;
}

// Donne la valeur cartésienne z à partir des coordonnées sphériques

Float get_z(const Float& norm, const Float& theta, const Float& phi)
{
	return cos(theta) * norm;
}

// Donne la distance entre deux points

Float get_distance(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_norm();
}

// Donne la distance entre deux points au carré

Float get_distance_2(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_norm_2();
}

// Donne l'angle theta entre deux points

Float get_theta(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_theta();
}

// Donne l'angle phi entre deux points

Float get_phi(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_phi();
}

// Donne le vecteur normalisé

Vector normalized(const Vector& vector)
{
	if (vector.get_norm() != 0.)
		return vector / vector.get_norm();
}