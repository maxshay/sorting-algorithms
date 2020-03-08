#ifndef SORTABLE_HPP
#define SORTABLE_HPP

#include <SFML/Graphics.hpp>

class Sortable {

public:

	// Constructor
	Sortable(const unsigned value);

	void setSize(const float width, const float height);

	void render(sf::RenderWindow& window, const float position);

	void highlight();

	void highlight(const sf::Color& color);

	bool operator >(const Sortable& other)
	{
		return m_value > other.m_value;
	}

	/**
	* Checks if the internal value is smaller then that of a different Sortable
	*/
	bool operator <(const Sortable& other)
	{
		return m_value < other.m_value;
	}

private:

	unsigned m_value;
	sf::RectangleShape m_shape;
	sf::Color m_defaultColor;


};





























#endif // SORTABLE_HPP