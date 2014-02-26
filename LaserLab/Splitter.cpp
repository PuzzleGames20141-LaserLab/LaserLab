#include "Splitter.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>

sf::Texture Splitter::sTexture;
Splitter::Splitter()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Splitter::sTexture);
}

void Splitter::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	float sAngle = getRotation();
	float pAngle = (float)(360 - 45*(photon.getDirection()-1));
	float pAngle_r = pAngle+180 >= 360 ? pAngle-180 : pAngle+180;
	if(fabs(sAngle - pAngle_r) < 90 || fabs(sAngle - pAngle_r) > 270)
	{
		pAngle = pAngle_r + 2 * (sAngle-pAngle_r);
		if(pAngle < 0) pAngle += 360;
		if(pAngle >= 360) pAngle -= 360;
		if(pAngle > 0)
		{
			pAngle = 360-pAngle;
		}
		int newDir = (int)(pAngle/45)+1;
		std::vector<Photon> newLight;
		newLight.push_back(photon);
		photon.myRotate(newDir);
	}
	else 
	{
		photon.setVelocity(0.0);
	}
}

void Splitter::clone(std::shared_ptr<Equipment>& ePtr)
{
	Splitter copySplitter = *this;
	ePtr = std::make_shared<Splitter>(copySplitter);
	
}

void Splitter::myRotate()
{
	setRotation(this->getRotation()+45);
}

void Splitter::loadTexture()
{
	if(!(Splitter::sTexture.loadFromFile("Equipments_Image/Splitter.png")))
	{
		std::cout << "Error: could not load Mirror image!" << std::endl;
	}

}