#include "LaserSource.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

LaserSource::LaserSource()
{
	if(!eTexture.loadFromFile("LaserSource.png"))
	{
		std::cout << "Error: could not load Laser Source image!" << std::endl;
	}
	col = sf::Color::Red;
	setTexture(eTexture);
}
void LaserSource::reaction(Photon& photon)
{
	photon.setVelocity(0.0);
}

void LaserSource::setColor(sf::Color myCol)
{
	col = myCol;
}

Photon LaserSource::getPhoton(float rad)
{
	float angle = getRotation();
	Photon startP(col, rad, angle);
	startP.setPosition(LaserSource::getPosition());
	return startP;
}