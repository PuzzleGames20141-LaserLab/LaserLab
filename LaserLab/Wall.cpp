#include "Wall.h"
#include "Photon.h"

#include <string.h>
#include <iostream>
#include <cmath>

sf::Texture Wall::wTexture;

Wall::Wall()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Wall::wTexture);
	label = WALL;
}

void Wall::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setVelocity(0.0);
}


void Wall::clone(std::shared_ptr<Equipment>& ePtr)
{
	Wall copyWall = *this;
	ePtr = std::make_shared<Wall>(copyWall);
}


void Wall::myRotate()
{
}

void Wall::myRotate_E()
{
}

void Wall::loadTexture()
{
	if(!(Wall::wTexture.loadFromFile("Equipments_Image/Wall.png")))
	{
		std::cout << "Error: could not load Wall image!" << std::endl;
	}
}

bool Wall::isHit()
{
	return true;
}

bool Wall::isLaserSource()
{
	return false;
}

void Wall::lightOff(){}