#include "Target.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture Target::redTexture;
sf::Texture Target::redHitTexture;
sf::Texture Target::blueTexture;
sf::Texture Target::blueHitTexture;
Target::Target(sf::Color col)
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	color = col;
	if(col == sf::Color::Red)
	{
		label = '5';
		setTexture(Target::redTexture);
	}
	if (col == sf::Color::Blue)
	{
		label = 'n';
		setTexture(Target::blueTexture);		
	}
	hit = false;
}

void Target::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setVelocity(0.0);
	/*
	float angle = getRotation();
	if(angle > 0)
	{
		angle = 360-angle;
	}
	int direction = int(angle/45)+1;
	*/
	if(photon.getColor() == color)
	{
		hit = true;
		if(color == sf::Color::Red)
		{
			setTexture(Target::redHitTexture);
		}
		if (color == sf::Color::Blue)
		{
			setTexture(Target::blueHitTexture);		
		}
	}
}

void Target::lightOff()
{
	hit = false;
	if(color == sf::Color::Red)
	{
		setTexture(Target::redTexture);
	}
	if (color == sf::Color::Blue)
	{
		setTexture(Target::blueTexture);		
	}
}
bool Target::isHit()
{
	return hit;
}
void Target::loadTexture()
{
	if(!(Target::redTexture.loadFromFile("Equipments_Image/Target_Red.png")))
	{
		std::cout << "Error: could not load Target_Red image!" << std::endl;
	}
	if(!Target::redHitTexture.loadFromFile("Equipments_Image/Target_Hit_Red.png"))
	{
		std::cout << "Error: could not load Target_Red_Hit image!" << std::endl;
	}
	if(!(Target::blueTexture.loadFromFile("Equipments_Image/Target_Blue.png")))
	{
		std::cout << "Error: could not load Target_Blue image!" << std::endl;
	}
	if(!Target::blueHitTexture.loadFromFile("Equipments_Image/Target_Hit_Blue.png"))
	{
		std::cout << "Error: could not load Target_Hit_Blue image!" << std::endl;
	}
}

void Target::clone(std::shared_ptr<Equipment>& ePtr)
{
	Target copyTarget = *this;
	ePtr = std::make_shared<Target>(copyTarget);
}

void Target::myRotate(){}

void Target::myRotate_E()
{
	setRotation(this->getRotation()+90);
}

bool Target::isLaserSource()
{
	return false;
}