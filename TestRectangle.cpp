#include "TestRectangle.hpp"

void TestRectangle::update(sf::RenderWindow& window){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		position = sf::Vector2f(sf::Mouse::getPosition());
	}
	collider.left = position.x;
	collider.top = position.y;

}

void TestRectangle::render(sf::RenderWindow& window){
	window.draw(rectangle);
}

