#include "Pit.h"
#include "Photon.h"

#include <string.h>
#include <iostream>
#include <cmath>

sf::Texture Pit::pTexture;

Pit::Pit()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Pit::pTexture);
	label = PIT;
}

void Pit::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.myMove();
}


void Pit::clone(std::shared_ptr<Equipment>& ePtr)
{
	Pit copyPit = *this;
	ePtr = std::make_shared<Pit>(copyPit);
}


void Pit::myRotate()
{
}

void Pit::myRotate_E()
{
}

void Pit::loadTexture()
{
	if(!(Pit::pTexture.loadFromFile("Equipments_Image/Pit.png")))
	{
		std::cout << "Error: could not load Pit image!" << std::endl;
	}
}

bool Pit::isHit()
{
	return true;
}

bool Pit::isLaserSource()
{
	return false;
}

void Pit::lightOff(){}