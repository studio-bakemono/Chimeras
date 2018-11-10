#include <SFML/Graphics.hpp>

class TestRectangle{

	public:
		sf::Vector2f position;
		sf::RectangleShape rectangle;
		sf::FloatRect collider;
	
	public:
		TestRectangle(sf::Vector2f position= sf::Vector2f(0,0), const sf::Vector2f size = sf::Vector2f(20,20)):
			position(position)
	{
		rectangle.setFillColor(sf::Color::Red);
		rectangle.setSize(size);
		collider = sf::FloatRect(position, size);
	}
	
	void render(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
};

