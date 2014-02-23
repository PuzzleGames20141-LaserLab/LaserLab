#include "Target.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

Target::Target()
{
	if(!eTexture.loadFromFile("Target.png"))
	{
		std::cout << "Error: could not load Laser Source image!" << std::endl;
	}
	col = sf::Color::Red;
	isHit = false;
	setTexture(eTexture);
}

void Target::reaction(Photon& photon)
{
	photon.setVelocity(0.0);
	isHit = true;
	if(!eTexture.loadFromFile("Target_Hit.png"))
	{
		std::cout << "Error: could not load Laser Source image!" << std::endl;
	}
}

bool Target::isSuccess()
{
	return isHit;
}
void Target::setColor(sf::Color myCol)
{
	col = myCol;
}