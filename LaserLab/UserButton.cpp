#include <SFML/Graphics.hpp>

#include <string>

#include "UserButton.h"

UserButton::UserButton(const std::string& imageName, sf::Vector2f position)
	:position_(position)
{
	texture_.loadFromFile(imageName);
	sprite_.setTexture(texture_);
	sprite_.setPosition(position_);
}

sf::Vector2u UserButton::getSize() const
{
	return texture_.getSize();
}

sf::FloatRect UserButton::getBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f UserButton::getPosition() const
{
	return sprite_.getPosition();
}

void UserButton::setPosition(sf::Vector2f position)
{
	sprite_.setPosition(position);
}

void UserButton::setPosition(float x, float y)
{
	sprite_.setPosition(x,y);
}

void UserButton::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}