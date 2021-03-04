#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include <math.h> // sqrt atan2 pow : Nécessaire pour la compilation sous linux

extern uint16_t	screen_width;								// Largeur de l'�cran
#define			MENU_RESIZE ((1. / 1920.) * screen_width)	// Co�fficient en fonction de la taille de l'�cran
#define			MENU_PI 3.14159265359						// Pi

// Classe d�finissant une ligne

class Line
{
private:

	sf::RectangleShape				rectangle;	// Ligne
	std::array<sf::CircleShape, 2>	circles;	// Bouts de la ligne

public:

									Line();
									Line(const Line& line);
									Line(const double& width, const sf::Vector2f& position_1, const sf::Vector2f& position_2, const sf::Color& color);

	void							operator=(const Line& line);

	double							get_size() const;
	double							get_width() const;
	sf::Vector2f					get_position(uint8_t index) const;
	void							draw(sf::RenderWindow& window) const;
};

// Clase d�finissant une case � cocher

class Box
{
private:

	std::array<Line, 4>			square;	// La boite
	std::array<Line, 2>			check;	// Boite coch�e
	sf::RectangleShape			hitbox; // Hitbox

public:

								Box();
								Box(const Box& box);
								Box(const double& size, const double& width, const sf::Vector2f& position, const sf::Color& square_color, const sf::Color& check_color);

	void						operator=(const Box& box);
	
	std::array<sf::Vector2f, 2>	get_hitbox() const;
	void						draw(sf::RenderWindow& window, bool checked) const;
};

// Types de curseurs

enum Cursor_type { arrow, hand, resize };

// Types de variables

enum VarType { Bool, Int, Double };

// Clase d�finissant une variable

class Variable
{
public:

	VarType							type;				// Type de la variable
	double							value;				// Valeur stock�e
	double							min;				// Valeur maximum
	double							max;				// Valeur minimum
	uint8_t							precision;			// Nombre de chiffres apr�s la virgule
	bool							percent;			// Si c'est un pourcentage ou non
	std::string						name_id;			// Nom utilis� pour la recherche
	sf::Text						name;				// Nom affich�
	sf::Text						value_text;			// Texte de l'affichage de la valeur
	Box								box;				// Boite � cocher
	Line							line;				// Ligne du curseur
	sf::CircleShape					circle;				// Rond du curseur
	bool							grabbed;			// Est cliqu�
	bool							grab_forbiden;		// Clic interdit
	sf::Vector2i					previous_mouse_pos;	// Position pr�c�dente de la souris

									Variable();
									Variable(const Variable& variable);
									Variable(const std::string& name_id, const std::string& name, VarType type, double initial_value, double min = 0., double max = 1., uint8_t precision = 0, bool percent = false);

	void							operator=(const Variable& variable);

	bool							is_in(sf::Vector2f position) const;
	sf::Vector2f					get_circle_position() const;
	double							get_value_from_circle() const;
	void							update(sf::RenderWindow& window);
	void							draw(sf::RenderWindow& window) const;
};

// Clase d�finissant le menu

class Menu
{
public:

	std::vector<Variable>		variables;				// Les variables du menu
	sf::Color					background;				// Le fond
	sf::Font					texts_font;				// La police du texte
	sf::Texture					start_texture;			// Texture du bouton start
	sf::Texture					start_texture_grabbed;	// Texture du bouton start appuy�
	sf::RectangleShape			start_button;			// Bouton start
	bool						end;					// Fin du menu

								Menu();
								Menu(const Menu& menu);
								Menu(const sf::Color& background);

	void						reload(const sf::Color& background);
	void						add_variable(const std::string& name_id, const std::string& name, VarType type, double initial_value, double min = 0., double max = 1., uint8_t precision = 0, bool percent = false);
	void						init_names(uint16_t name_size, const double& names_position, const sf::Color& name_color, const double& y_edges);
	void						init_lines(const double& lines_sizes, const double& lines_widths, const double& lines_positions, const sf::Color& lines_colors);
	void						init_circles(const double& circles_radius, const sf::Color& circles_colors);
	void						init_values(uint16_t value_size, const double& values_position, const sf::Color& value_color);
	void						init_boxes(const double& boxes_sizes, const double& boxes_widths, const double& boxes_positions, const sf::Color& squares_colors, const sf::Color& checks_colors);
	void						init_start(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color);

	void						operator=(const Menu& menu);
	double						operator[](const std::string& name_id) const;

	bool						is_in(sf::Vector2f position) const;
	void						update(sf::RenderWindow& window);
	void						draw(sf::RenderWindow& window) const;
};

// Classe d�finissant un bouton pour recommencer

class Restart
{
public :

	bool				is_active;			// Est actif
	sf::RectangleShape	button;				// Bouton recommencer
	sf::Texture			texture;			// Texture du bouton recommencer
	sf::Texture			texture_grabbed;	// Texture du bouton recommencer appuy�

						Restart();
						Restart(const Restart& restart);
						Restart(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color);

	void				operator=(const Restart& restart);

	bool				is_in(sf::Vector2f position);
	bool				update(sf::RenderWindow& window);
	void				draw(sf::RenderWindow& window);
};

std::string double_to_string(const double& value, uint8_t precision, bool percent);

#endif