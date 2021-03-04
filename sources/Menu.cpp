#include "Menu.h"

// -------------------- Ligne --------------------

// Construit une ligne

Line::Line()
{
}

// Construit une ligne à partir d'une autre ligne

Line::Line(const Line& line)
{
	*this = line;
}

// Construit une ligne à partir de ces propriétés

Line::Line(const double& width, const sf::Vector2f& position_1, const sf::Vector2f& position_2, const sf::Color& color)
{
	double size = sqrt(pow(position_2.x - position_1.x, 2) + pow(position_2.y - position_1.y, 2));

	rectangle.setSize(sf::Vector2f(size, width));
	
	for (auto& circle : circles)
		circle.setRadius(width / 2.);

	rectangle.setOrigin(0., width / 2.);

	for (auto& circle : circles)
		circle.setOrigin(width / 2., width / 2.);

	rectangle.setPosition(position_1);
	circles[0].setPosition(position_1);
	circles[1].setPosition(position_2);

	rectangle.setFillColor(color);

	for (auto& circle : circles)
		circle.setFillColor(color);

	rectangle.setRotation(atan2(position_2.y - position_1.y, position_2.x - position_1.x) * (180. / MENU_PI));
}

// Assignation

void Line::operator=(const Line& line)
{
	rectangle = line.rectangle;
	circles = line.circles;
}

// Renvoie la taille

double Line::get_size() const
{
	return rectangle.getSize().x;
}

// Renvoie l'épaisseur

double Line::get_width() const
{
	return rectangle.getSize().y;
}

// Renvoie la position

sf::Vector2f Line::get_position(uint8_t index) const
{
	return circles[index].getPosition();
}

// Affiche la ligne

void Line::draw(sf::RenderWindow& window) const
{
	window.draw(rectangle);

	for (auto& circle : circles)
		window.draw(circle);
}

// -------------------- Case --------------------

// Construit une case

Box::Box()
{
}

// Construit une case à partir d'une autre case

Box::Box(const Box& box)
{
	*this = box;
}

// Construit une case à partir de ces propriétés

Box::Box(const double& size, const double& width, const sf::Vector2f& position, const sf::Color& square_color, const sf::Color& check_color)
{
	square[0] = Line(width, sf::Vector2f(position.x - size / 2., position.y - size / 2.), sf::Vector2f(position.x + size / 2., position.y - size / 2.), square_color);
	square[1] = Line(width, sf::Vector2f(position.x + size / 2., position.y - size / 2.), sf::Vector2f(position.x + size / 2., position.y + size / 2.), square_color);
	square[2] = Line(width, sf::Vector2f(position.x + size / 2., position.y + size / 2.), sf::Vector2f(position.x - size / 2., position.y + size / 2.), square_color);
	square[3] = Line(width, sf::Vector2f(position.x - size / 2., position.y + size / 2.), sf::Vector2f(position.x - size / 2., position.y - size / 2.), square_color);

	check[0] = Line(width * 1.5, sf::Vector2f(position.x - 0.60 * size, position.y - 0.15 * size), sf::Vector2f(position.x - 0.15 * size, position.y + 0.30 * size), check_color);
	check[1] = Line(width * 1.5, sf::Vector2f(position.x - 0.15 * size, position.y + 0.30 * size), sf::Vector2f(position.x + 0.70 * size, position.y - 0.55 * size), check_color);

	hitbox.setSize(sf::Vector2f(size + width, size + width));
	hitbox.setOrigin((size + width) / 2., (size + width) / 2.);
	hitbox.setPosition(position);
}

// Assignation

void Box::operator=(const Box& box)
{
	square = box.square;
	check = box.check;
	hitbox = box.hitbox;
}

// Donne la hitbox

std::array<sf::Vector2f, 2> Box::get_hitbox() const
{
	return { sf::Vector2f(hitbox.getPosition().x - hitbox.getSize().x / 2., hitbox.getPosition().y - hitbox.getSize().y / 2.),
			 sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2., hitbox.getPosition().y + hitbox.getSize().y / 2.) };
}

// Affiche la case

void Box::draw(sf::RenderWindow& window, bool checked) const
{
	for (auto& line : square)
		line.draw(window);

	if (checked)
		for (auto& line : check)
			line.draw(window);
}

// -------------------- Variable --------------------

// Construit une variable

Variable::Variable()
{
	type = Bool;
	value = 0.;
	min = 0.;
	max = 0.;
	precision = 0;
	percent = false;
	line = Line();
	grabbed = false;
	grab_forbiden = false;
}

// Construit une variable à partir d'une autre variable

Variable::Variable(const Variable& variable)
{
	*this = variable;
}

// Construit une variable à partir de ces Paramètres

Variable::Variable(const std::string& name_id, const std::string& name, VarType type, double initial_value, double min, double max, uint8_t precision, bool percent)
{
	this->type = type;
	this->name_id = name_id;
	this->name.setString(name);
	this->precision = precision;
	this->percent = percent;
	value = initial_value;
	this->min = min;
	this->max = max;

	grabbed = false;
	grab_forbiden = false;

	if (this->type == Int)
		value_text.setString(std::to_string(int(value)));

	else if (this->type == Double)
		value_text.setString(double_to_string(value, this->precision, this->percent));
}

// Assignation

void Variable::operator=(const Variable& variable)
{
	type = variable.type;
	value = variable.value;
	min = variable.min;
	max = variable.max;
	precision = variable.precision;
	percent = variable.percent;
	name_id = variable.name_id;
	name = variable.name;
	value_text = variable.value_text;
	box = variable.box;
	line = variable.line;
	circle = variable.circle;
	grabbed = variable.grabbed;
	grab_forbiden = variable.grab_forbiden;
	previous_mouse_pos = variable.previous_mouse_pos;
}

// Dit si la position se trouve dans la case ou le curseur de la variable

bool Variable::is_in(sf::Vector2f position) const
{
	if (type == Bool)
		return (position.x > box.get_hitbox()[0].x && position.x < box.get_hitbox()[1].x && position.y > box.get_hitbox()[0].y && position.y < box.get_hitbox()[1].y);

	else
		return (position.x > circle.getPosition().x - circle.getRadius() && position.x < circle.getPosition().x + circle.getRadius() &&
				position.y > circle.getPosition().y - circle.getRadius() && position.y < circle.getPosition().y + circle.getRadius());

	return false;
}

// Donne la position du curseur en fonction de la valeur de la variable

sf::Vector2f Variable::get_circle_position() const
{
	return sf::Vector2f(((value - min) / (max - min)) * line.get_size() + line.get_position(0).x, line.get_position(0).y);
}

// Donne la valeur de la variable en fonction de la position du curseur

double Variable::get_value_from_circle() const
{
	return (static_cast<double>(circle.getPosition().x - line.get_position(0).x) / line.get_size()) * (max - min) + min;
}

// Met é jour la variable

void Variable::update(sf::RenderWindow& window)
{
	sf::Vector2i mouse_pos;
	bool left_click = false;

	mouse_pos = sf::Mouse::getPosition(window);
	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if (type == Bool)
	{
		if (!left_click)
		{
			grabbed = false;
			grab_forbiden = false;
		}

		if (!is_in(sf::Vector2f(mouse_pos)) && left_click)
			grab_forbiden = true;

		if (is_in(sf::Vector2f(mouse_pos)) && !grab_forbiden && !grabbed && left_click)
		{
			grabbed = true;
			value = !value;
		}
	}

	else
	{
		if (!left_click)
		{
			grab_forbiden = false;
			grabbed = false;
		}

		if (grabbed && !((mouse_pos.x < line.get_position(0).x && circle.getPosition().x == line.get_position(0).x) ||
						 (mouse_pos.x > line.get_position(1).x && circle.getPosition().x == line.get_position(1).x)))
		{
			circle.move(static_cast<double>(mouse_pos.x) - static_cast<double>(previous_mouse_pos.x), 0.);

			if (circle.getPosition().x > line.get_position(1).x)
				circle.setPosition(line.get_position(1).x, circle.getPosition().y);

			if (circle.getPosition().x < line.get_position(0).x)
				circle.setPosition(line.get_position(0).x, circle.getPosition().y);
			
			value = get_value_from_circle();

			if (type == Int)
				value_text.setString(std::to_string(int(value)));

			else
				value_text.setString(double_to_string(value, precision, percent));

			value_text.setOrigin(value_text.getLocalBounds().width / 2., value_text.getLocalBounds().height);
			value_text.setPosition(circle.getPosition().x, value_text.getPosition().y);
		}

		if (!is_in(sf::Vector2f(mouse_pos)) && left_click && !grabbed)
			grab_forbiden = true;

		if (is_in(sf::Vector2f(mouse_pos)) && !grab_forbiden && left_click)
			grabbed = true;
	}

	previous_mouse_pos = mouse_pos;
}

// Affiche la variable

void Variable::draw(sf::RenderWindow& window) const
{
	window.draw(name);
	
	if (type == Bool)
		box.draw(window, value);

	else
	{
		line.draw(window);
		window.draw(circle);
		window.draw(value_text);
	}
}

// -------------------- Menu --------------------

// Construit un menu

Menu::Menu()
{
	variables.clear();
	end = false;
}

// Construit un menu à partir d'un autre menu

Menu::Menu(const Menu& menu)
{
	*this = menu;
}

// Construit un menu à partir de ces Paramètres

Menu::Menu(const sf::Color& background)
{
	reload(background);
}

// Initialise un menu à partir de ces Paramètres 

void Menu::reload(const sf::Color& background)
{
	this->background = background;
	variables.clear();
	end = false;
	texts_font.loadFromFile("dependencies/resources/GoogleSans-Bold.ttf");
}

// Ajoute une variable

void Menu::add_variable(const std::string& name_id, const std::string& name, VarType type, double initial_value, double min, double max, uint8_t precision, bool percent)
{
	variables.push_back(Variable(name_id, name, type, initial_value, min, max, precision, percent));
}

// Initialise le nom des variables

void Menu::init_names(uint16_t name_size, const double& names_position, const sf::Color& name_color, const double& y_edges)
{
	for (uint8_t i = 0; i < variables.size(); i++)
	{
		variables[i].name.setCharacterSize(name_size);
		variables[i].name.setFont(texts_font);
		variables[i].name.setFillColor(name_color);
		variables[i].name.setOrigin(variables[i].name.getLocalBounds().width, name_size / 1.35);
		variables[i].name.setPosition(names_position, (((1080. * MENU_RESIZE - 2. * y_edges) / (variables.size() - 1)) * i) + y_edges);
	}
}

// Initialise la ligne des curseurs

void Menu::init_lines(const double& lines_sizes, const double& lines_widths, const double& lines_positions, const sf::Color& lines_colors)
{
	for (auto& variable : variables)
		if (variable.type != Bool)
			variable.line = Line(lines_widths, sf::Vector2f(lines_positions - lines_sizes / 2., variable.name.getPosition().y),
				sf::Vector2f(lines_positions + lines_sizes / 2., variable.name.getPosition().y), lines_colors);
}

// Initialise les curseurs

void Menu::init_circles(const double& circles_radius, const sf::Color& circles_colors)
{
	for (auto& variable : variables)
		if (variable.type != Bool)
		{
			variable.circle = sf::CircleShape(circles_radius, 50);
			variable.circle.setOrigin(circles_radius, circles_radius);
			variable.circle.setPosition(variable.get_circle_position());
			variable.circle.setFillColor(circles_colors);
		}
}

// Initialise les valeurs affichées

void Menu::init_values(uint16_t values_sizes, const double& values_positions, const sf::Color& values_colors)
{
	for (auto& variable : variables)
		if (variable.type != Bool)
		{
			variable.value_text.setCharacterSize(values_sizes);
			variable.value_text.setFont(texts_font);
			variable.value_text.setFillColor(values_colors);
			variable.value_text.setOrigin(variable.value_text.getLocalBounds().width / 2., variable.value_text.getLocalBounds().height);
			variable.value_text.setPosition(variable.circle.getPosition().x, variable.circle.getPosition().y - values_positions);
		}
}

// Initialise les cases à cocher

void Menu::init_boxes(const double& boxes_sizes, const double& boxes_widths, const double& boxes_positions, const sf::Color& squares_colors, const sf::Color& checks_colors)
{
	for (auto& variable : variables)
		if (variable.type == Bool)
			variable.box = Box(boxes_sizes, boxes_widths, sf::Vector2f(boxes_positions, variable.name.getPosition().y - boxes_sizes / 10.), squares_colors, checks_colors);
}

// Initialise le bouton start

void Menu::init_start(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color)
{
	start_texture.loadFromFile("dependencies/resources/start_texture.png");
	start_texture_grabbed.loadFromFile("dependencies/resources/start_texture_grabbed.png");

	start_texture.setSmooth(true);
	start_texture_grabbed.setSmooth(true);

	start_button.setTexture(&start_texture);
	start_button.setSize(sf::Vector2f(start_size, start_size));
	start_button.setOrigin(start_size / 2., start_size / 2.);
	start_button.setPosition(start_x_position, start_y_position);
	start_button.setFillColor(start_color);
}

// Assignation

void Menu::operator=(const Menu& menu)
{
	variables = menu.variables;
	background = menu.background;
	start_texture = menu.start_texture;
	start_button = menu.start_button;
	start_texture_grabbed = menu.start_texture_grabbed;
	texts_font = menu.texts_font;
	end = menu.end;
}

// Donne la valeur d'une variable à partir de son nom

double Menu::operator[](const std::string& name_id) const
{
	for (auto& variable : variables)
		if (variable.name_id == name_id)
			return variable.value;

	throw std::invalid_argument(name_id + " does not exist");
}

// Dit si la position est sur le bouton start

bool Menu::is_in(sf::Vector2f position) const
{
	return (position.x > start_button.getPosition().x - start_button.getSize().x / 2. && position.x < start_button.getPosition().x + start_button.getSize().x / 2. &&
			position.y > start_button.getPosition().y - start_button.getSize().y / 2. && position.y < start_button.getPosition().y + start_button.getSize().x / 2.);
}

// Met é jour le menu

void Menu::update(sf::RenderWindow& window)
{
	static sf::Vector2i mouse_pos;
	static sf::Vector2i previous_mouse_pos;
	static bool left_click = false;
	static bool grabbed = false;
	static bool grab_forbiden = false;
	static Cursor_type cursor_type = arrow;
	static Cursor_type temp;
	static sf::Cursor cursor;

	mouse_pos = sf::Mouse::getPosition(window);
	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	temp = cursor_type;
	cursor_type = arrow;

	for (auto& variable : variables)
	{
		variable.update(window);

		if (variable.type == Bool)
		{
			if (variable.is_in(sf::Vector2f(mouse_pos)) && !variable.grab_forbiden)
				cursor_type = hand;
		}

		else
			if ((variable.grabbed || variable.is_in(sf::Vector2f(mouse_pos))) && !variable.grab_forbiden)
				cursor_type = resize;
	}

	if (!left_click)
	{
		if (is_in(sf::Vector2f(mouse_pos)) && grabbed)
			end = true;

		grabbed = false;
		grab_forbiden = false;
	}

	if (!is_in(sf::Vector2f(mouse_pos)))
	{
		start_button.setTexture(&start_texture);

		if (left_click && !grabbed)
			grab_forbiden = true;
	}

	if (is_in(sf::Vector2f(mouse_pos)) && !grab_forbiden)
	{
		start_button.setTexture(&start_texture_grabbed);
		cursor_type = hand;

		if (left_click)
			grabbed = true;
	}

	if (temp != cursor_type)
	{
		if (cursor_type == arrow)
			cursor.loadFromSystem(sf::Cursor::Arrow);

		if (cursor_type == hand)
			cursor.loadFromSystem(sf::Cursor::Hand);

		if (cursor_type == resize)
			cursor.loadFromSystem(sf::Cursor::SizeHorizontal);

		window.setMouseCursor(cursor);
	}

	previous_mouse_pos = mouse_pos;
}

// Affiche le menu

void Menu::draw(sf::RenderWindow& window) const
{
	window.clear(background);

	for (auto& variable : variables)
		variable.draw(window);

	window.draw(start_button);
	window.display();
}

// -------------------- Bouton recommencer --------------------

// Construit un bouton recommencer

Restart::Restart()
{
	is_active = false;
}

// Construit un bouton recommencer à partir d'un autre

Restart::Restart(const Restart& restart)
{
	*this = restart;
}

// Construit un bouton recommencer à partir de ces Paramètres

Restart::Restart(const double& start_size, const double& start_x_position, const double& start_y_position, const sf::Color& start_color)
{
	is_active = false;

	texture.loadFromFile("dependencies/resources/restart_texture.png");
	texture_grabbed.loadFromFile("dependencies/resources/restart_texture_grabbed.png");

	texture.setSmooth(true);
	texture_grabbed.setSmooth(true);

	button.setTexture(&texture);
	button.setSize(sf::Vector2f(start_size, start_size));
	button.setOrigin(start_size / 2., start_size / 2.);
	button.setPosition(start_x_position, start_y_position);
	button.setFillColor(start_color);
}

// Assignation

void Restart::operator=(const Restart& restart)
{
	is_active = restart.is_active;
	button = restart.button;
	texture = restart.texture;
	texture_grabbed = restart.texture_grabbed;
}

// Dit si la position est sur le bouton

bool Restart::is_in(sf::Vector2f position)
{
	return (position.x > button.getPosition().x - button.getSize().x / 2. && position.x < button.getPosition().x + button.getSize().x / 2. &&
			position.y > button.getPosition().y - button.getSize().y / 2. && position.y < button.getPosition().y + button.getSize().x / 2.);
}

// Met é jour le bouton recommencer

bool Restart::update(sf::RenderWindow& window)
{
	static sf::Vector2i mouse_pos;
	static sf::Vector2i previous_mouse_pos;
	static bool left_click = false;
	static bool grabbed = false;
	static bool grab_forbiden = false;
	static Cursor_type cursor_type = arrow;
	static Cursor_type temp;
	static sf::Cursor cursor;

	mouse_pos = sf::Mouse::getPosition(window);
	left_click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	temp = cursor_type;
	cursor_type = arrow;

	if (!left_click)
	{
		if (is_in(sf::Vector2f(mouse_pos)) && grabbed)
		{
			grabbed = false;
			grab_forbiden = false;
			return true;
		}

		else
			grabbed = false, grab_forbiden = false;
	}

	if (!is_in(sf::Vector2f(mouse_pos)))
	{
		button.setTexture(&texture);

		if (left_click && !grabbed)
			grab_forbiden = true;
	}

	if (is_in(sf::Vector2f(mouse_pos)) && !grab_forbiden)
	{
		button.setTexture(&texture_grabbed);
		cursor_type = hand;

		if (left_click)
			grabbed = true;
	}

	if (temp != cursor_type)
	{
		if (cursor_type == arrow)
			cursor.loadFromSystem(sf::Cursor::Arrow);

		if (cursor_type == hand)
			cursor.loadFromSystem(sf::Cursor::Hand);

		if (cursor_type == resize)
			cursor.loadFromSystem(sf::Cursor::SizeHorizontal);

		window.setMouseCursor(cursor);
	}

	previous_mouse_pos = mouse_pos;
	return false;
}

// Affiche le bouton recommencer

void Restart::draw(sf::RenderWindow& window)
{
	window.draw(button);
}

// -------------------- Fonctions --------------------

// Transforme un nombre réel en text

std::string double_to_string(const double& value, uint8_t precision, bool percent)
{
	std::string text = std::to_string(value);
	uint16_t i = 0;

	while (text[i] != '.')
	{
		i++;

		if (i == text.size())
			return text;
	}

	text[i] = ',';

	i += precision + 1;

	while (text.size() != i)
		text.pop_back();

	if (precision == 0)
		text.pop_back();

	if (percent)
	{
		text.push_back(' ');
		text.push_back('%');
	}

	return text;
}