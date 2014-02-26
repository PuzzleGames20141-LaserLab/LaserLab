#include "LaserSource.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture LaserSource::lTexture;
LaserSource::LaserSource()
{
	col = sf::Color::Red;
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(LaserSource::lTexture);
}
void LaserSource::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setVelocity(0.0);
}

void LaserSource::setColor(sf::Color myCol)
{
	col = myCol;
}

Photon LaserSource::getPhoton()
{
	float angle = getRotation();
	if(angle > 0)
	{
		angle = 360 - angle;
	}
	int direction  = (int)(angle/45)+1;
	Photon startP(direction);
	float deltaX = 0;
	float deltaY = 0;
	if(direction == 1 || direction == 5)
	{
		deltaX = (float)(BLOCK_SIZE*(3-direction)/4);
	}
	else if(direction == 3 || direction == 7)
	{
		deltaY = (float)(BLOCK_SIZE*(direction-5)/4);
	}
	sf::Vector2f delta(deltaX, deltaY);
	startP.setPosition(LaserSource::getPosition() + delta);
	return startP;
}

void LaserSource::loadTexture()
{
	if(!(LaserSource::lTexture.loadFromFile("Equipments_Image/LaserSource.png")))
	{
		std::cout << "Error: could not load LaserSource image!" << std::endl;
	}
}
void LaserSource::clone(std::shared_ptr<Equipment>& ePtr){}
void LaserSource::myRotate(){}