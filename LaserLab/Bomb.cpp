#include "Bomb.h"
#include "Photon.h"

#include <string.h>
#include <iostream>
#include <cmath>

sf::Texture Bomb::bTexture;

Bomb::Bomb()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Bomb::bTexture);
	label = BOMB;
}

void Bomb::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.myMove();
}


void Bomb::clone(std::shared_ptr<Equipment>& ePtr)
{
	Bomb copyBomb = *this;
	ePtr = std::make_shared<Bomb>(copyBomb);
}


void Bomb::myRotate()
{
}

void Bomb::myRotate_E()
{
}

void Bomb::loadTexture()
{
	if(!(Bomb::bTexture.loadFromFile("Equipments_Image/Bomb.png")))
	{
		std::cout << "Error: could not load Bomb image!" << std::endl;
	}
}

bool Bomb::isHit()
{
	return true;
}

bool Bomb::isLaserSource()
{
	return false;
}

void Bomb::lightOff(){}