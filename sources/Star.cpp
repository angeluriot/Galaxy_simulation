#include "star.h"
#include "utils.h"
#include "block.h"

// Construit une étoile

Star::Star()
{
	previous_position.clear();
	position.clear();
	speed.clear();
	acceleration.clear();
	density = 0.f;
	block_index = NULL;
}

// Construit une étoile à partir des propriétés de la simulation

Star::Star(const Float& initial_speed, const Float& area, const Float& galaxy_thickness, const Float& step)
{
	position = Vector_spherical(random_Float(0.01f, 1.f) * (area / 2.f), PI / 2.f, random_Float(0.f, 2.f * PI));
	position.z = ((random_Float(0.f, 1.f) - 0.5f) * galaxy_thickness);
	speed = Vector_spherical(initial_speed * cbrt(position.get_norm()), PI / 2.f, position.get_phi() + PI / 2.f);
	previous_position = position - speed * step;
	acceleration.clear();
	density = 0.f;
	color = sf::Color(0, 255, 255);
	block_index = NULL;
}

// Construit une étoile à partir d'une autre étoile

Star::Star(const Star& star)
{
	*this = star;
}

// Assignation

void Star::operator=(const Star& star)
{
	previous_position = star.previous_position;
	position = star.position;
	speed = star.speed;
	acceleration = star.acceleration;
	density = star.density;
	color = star.color;
	block_index = star.block_index;
}

// Met à jour la position

void Star::update_position(const Float& step)
{
	Vector temp = position;
	position = 2.f * position - previous_position + acceleration * step * step; // Intégration de Verlet
	previous_position = temp;
}

// Met à jour la vitesse

void Star::update_speed(const Float& step)
{
	speed += acceleration * step;
}

// Met à jour l'accélération et la densité

void Star::update_acceleration(Galaxy& galaxy, const Float& acc_max, const Block& block, const Float& precision)
{
	acceleration.clear();
	density = 0.;

	// Force des autres étoiles
	force_calculation(block, precision);

	// Force supplémentaire vers le centre (matière noire)
	acceleration += Vector_spherical((galaxy.size()) / get_distance_2(position, Vector()), get_theta(position, Vector()), get_phi(position, Vector()));

	// Gestion de l'accélération maximum
	if (acceleration.get_norm() > acc_max)
		acceleration.set_norm(acc_max);
}

// Calcule la densité et la force exercée sur une étoile

void Star::force_calculation(const Block& block, const Float& precision)
{
	Float distance = get_distance(position, block.mass_center);

	if (block.stars.size() == 1)
	{
		if (distance != 0.f)
		{
			acceleration += Vector_spherical(1.f / get_distance_2(position, block.mass_center), get_theta(position, block.mass_center), get_phi(position, block.mass_center));
			density += acceleration.get_norm();
		}
	}

	else
	{
		if (block.size / distance < precision && distance != 0.f)
		{
			acceleration += Vector_spherical(static_cast<Float>(block.stars.size()) / get_distance_2(position, block.mass_center),
				get_theta(position, block.mass_center), get_phi(position, block.mass_center));
			
			density += acceleration.get_norm();
		}

		else
			for (const Block& b : block.children)
				force_calculation(b, precision);
	}
}

// Met à jour la couleur

void Star::update_color(uint32_t nb_stars)
{
	int color_nb = cbrt((density / (static_cast<Float>(nb_stars) / 100000.f)) * 100.f) + 200;

	if (color_nb > 255 * 3)
		color_nb = 255 * 3;

	if (color_nb < 255)
		color = sf::Color(0, 0, color_nb);

	else if (color_nb < 255 * 2)
		color = sf::Color(0, color_nb - 255, 255);

	else
		color = sf::Color(color_nb - 255 * 2, 255, 255);
}

// Dessine l'étoile

void Star::draw(const Float& area, sf::Image& image, View view) const
{
	sf::Vector2f screen_pos = simu_to_screen(position, area, view);

	if (screen_pos.x >= 0 && screen_pos.x < image.getSize().x && screen_pos.y >= 0 && screen_pos.y < image.getSize().y)
		image.setPixel(screen_pos.x, screen_pos.y,
			sf::Color(std::max(color.r, image.getPixel(screen_pos.x, screen_pos.y).r), std::max(color.g, image.getPixel(screen_pos.x, screen_pos.y).g), color.b));
}