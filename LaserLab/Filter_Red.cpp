#include "Filter_Red.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

sf::Texture Filter_Red::fTexture;

Filter_Red::Filter_Red()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
}

void Filter_Red::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	photon.setColor(sf::Color::Red);
	photon.myMove();
}

void Filter_Red::loadTexture()
{
	if(!(Filter_Red::fTexture.loadFromFile("Equipments_Image/ColorChanger_red.png")))
	{
		std::cout << "Error: could not load red color changer image!" << std::endl;
	}

}

void Filter_Red::clone(std::shared_ptr<Equipment>& ePtr)
{
	Filter_Red copyFilter_Red = *this;
	ePtr = std::make_shared<Filter_Red>(copyFilter_Red);
}

void Filter_Red::myRotate_E()
{
}

bool Filter_Red::isHit()
{
	return true;
}

bool Filter_Red::isLaserSource()
{
	return false;
}

void Filter_Red::myRotate(){}
void Filter_Red::lightOff(){}