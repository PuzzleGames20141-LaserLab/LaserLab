#include "Filter_Blue.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture Filter_Blue::fTexture;

Filter_Blue::Filter_Blue()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
}

void Filter_Blue::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setColor(sf::Color::Blue);
	photon.myMove();
}

void Filter_Blue::loadTexture()
{
	if(!(Filter_Blue::fTexture.loadFromFile("Equipments_Image/ColorChanger_blue.png")))
	{
		std::cout << "Error: could not load red color changer image!" << std::endl;
	}

}

void Filter_Blue::clone(std::shared_ptr<Equipment>& ePtr)
{
	Filter_Blue copyFilter_Blue = *this;
	ePtr = std::make_shared<Filter_Blue>(copyFilter_Blue);
}

void Filter_Blue::myRotate_E()
{
}

bool Filter_Blue::isHit()
{
	return true;
}

bool Filter_Blue::isLaserSource()
{
	return false;
}

void Filter_Blue::myRotate(){}
void Filter_Blue::lightOff(){}