#include "Target.h"
#include "Photon.h"
#include "Capacitor.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture Capacitor::idle_Texture;
sf::Texture Capacitor::charged_Texture;

Capacitor::Capacitor()
{
	hit = false;
	state = 0;
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Capacitor::idle_Texture);
	label = 't';
}

void Capacitor::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setVelocity(0.0);
	if(state == 0)
	{
		state = 10;
		if(photon.getColor() == sf::Color::Red)
		{
			state += 1;
		}
		else
		{
			state += 2;
		}
		setTexture(Capacitor::charged_Texture);
	}
	else if(state/10 == 1)
	{
		if(photon.getColor() == sf::Color::Red)
		{
			state = 11;
		}
		else
		{
			state = 12;
		}
	}
	hit = true;
}

void Capacitor::lightOff()
{
	hit = false;
}
bool Capacitor::isHit()
{
	return hit;
}
void Capacitor::loadTexture()
{
	if(!(Capacitor::idle_Texture.loadFromFile("Equipments_Image/Capacitor.png")))
	{
		std::cout << "Error: could not load Capacitor image!" << std::endl;
	}
	if(!Capacitor::charged_Texture.loadFromFile("Equipments_Image/Capacitor_Charge.png"))
	{
		std::cout << "Error: could not load Capacitor_Charge image!" << std::endl;
	}
}

void Capacitor::clone(std::shared_ptr<Equipment>& ePtr)
{
	Capacitor copyCapacitor = *this;
	ePtr = std::make_shared<Capacitor>(copyCapacitor);
}

void Capacitor::myRotate()
{
}

void Capacitor::myRotate_E()
{
	setRotation(this->getRotation()+90);
}

bool Capacitor::isLaserSource()
{
	return false;
}

int Capacitor::curState()
{
	if(state/10 == 1 || state/10 == 2)
	{
		state += 10;
	}
	return state;
}