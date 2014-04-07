#include "LaserSource.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture LaserSource::redTexture;
sf::Texture LaserSource::blueTexture;
LaserSource::LaserSource(char col)
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	switch(col)
	{
	case 'r':
		{
			label = '1';
			color = sf::Color::Red;
			setTexture(LaserSource::redTexture);
			break;
		}
	case 'b':
		{
			label = 'j';
			color = sf::Color::Blue;
			setTexture(LaserSource::blueTexture);
			break;		
		}
	default:
		{
			label = '1';
			color = sf::Color::Red;
			setTexture(LaserSource::redTexture);
			break;		
		}
	}
}
void LaserSource::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setVelocity(0.0);
}



Photon LaserSource::getPhoton()
{
	float angle = getRotation();
	if(angle > 0)
	{
		angle = 360 - angle;
	}
	int direction  = (int)(angle/45)+1;
	Photon startP(direction, color);
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
	if(!(LaserSource::redTexture.loadFromFile("Equipments_Image/LaserSource_Red.png")))
	{
		std::cout << "Error: could not load red LaserSource image!" << std::endl;
	}
	if(!(LaserSource::blueTexture.loadFromFile("Equipments_Image/LaserSource_Blue.png")))
	{
		std::cout << "Error: could not load blue LaserSource image!" << std::endl;
	}
}

void LaserSource::clone(std::shared_ptr<Equipment>& ePtr)
{
	LaserSource copyLaserSource = *this;
	ePtr = std::make_shared<LaserSource>(copyLaserSource);
}

void LaserSource::myRotate_E()
{
	setRotation(this->getRotation()+90);
}

bool LaserSource::isHit()
{
	return true;
}

bool LaserSource::isLaserSource()
{
	return true;
}

void LaserSource::myRotate(){}
void LaserSource::lightOff(){}