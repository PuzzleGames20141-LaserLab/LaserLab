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
	label = 'b';
	cost = 20;
}

void Splitter::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	float sAngle = getRotation();
	float pAngle = (float)(360 - 45*(photon.getDirection()-1));
	int newDir_1;
	int newDir_2;
	float x = photon.getPosition().x;
	float y = photon.getPosition().y;
	if((int)(360 + pAngle - sAngle)%360 == 0)
	{
		float newAngle = pAngle + 90;
		if(newAngle < 0) newAngle += 360;
		if(newAngle >= 360) newAngle -= 360;
		if(newAngle > 0)
		{
			newAngle = 360-newAngle;
		}
		newDir_1 = (int)(newAngle/45)+1;
		Photon newPhoton(photon.getDirection(), photon.getColor());
		newPhoton.setPosition(x, y);
		newPhoton.myRotate(newDir_1);
		std::vector<Photon> newLight;
		newLight.push_back(newPhoton);
		lightPaths.push_back(newLight);
		photon.myMove();
		return;
	}
	else if((int)(pAngle - sAngle + 90 + 360)%360 == 0)
	{
		float newAngle_1 = pAngle+90;
		if(newAngle_1 < 0) newAngle_1 += 360;
		if(newAngle_1 >= 360) newAngle_1 -= 360;
		if(newAngle_1 > 0)
		{
			newAngle_1 = 360-newAngle_1;
		}
		newDir_1 = (int)(newAngle_1/45)+1;

		float newAngle_2 = pAngle - 90;
		if(newAngle_2 < 0) newAngle_2 += 360;
		if(newAngle_2 >= 360) newAngle_2 -= 360;
		if(newAngle_2 > 0)
		{
			newAngle_2 = 360-newAngle_2;
		}
		newDir_2 = (int)(newAngle_2/45)+1;
		Photon newPhoton(photon.getDirection(), photon.getColor());
		newPhoton.setPosition(x, y);
		newPhoton.myRotate(newDir_1);
		std::vector<Photon> newLight;
		newLight.push_back(newPhoton);
		lightPaths.push_back(newLight);
		photon.myRotate(newDir_2);
		return;
	}
	else if((int)(pAngle - sAngle + 540)%360 == 0)
	{
		float newAngle = pAngle - 90;
		if(newAngle < 0) newAngle += 360;
		if(newAngle >= 360) newAngle -= 360;
		if(newAngle > 0)
		{
			newAngle = 360-newAngle;
		}
		newDir_1 = (int)(newAngle/45)+1;
		Photon newPhoton(photon.getDirection(), photon.getColor());
		newPhoton.setPosition(x, y);
		newPhoton.myRotate(newDir_1);
		std::vector<Photon> newLight;
		newLight.push_back(newPhoton);
		lightPaths.push_back(newLight);
		photon.myMove();
		return;
	}
	else 
	{
		photon.setVelocity(0.0);
		return;
	}
}

void Splitter::clone(std::shared_ptr<Equipment>& ePtr)
{
	Splitter copySplitter = *this;
	ePtr = std::make_shared<Splitter>(copySplitter);
	
}

void Splitter::myRotate()
{
	setRotation(this->getRotation()+90);
}

void Splitter::myRotate_E()
{
	myRotate();
}

void Splitter::loadTexture()
{
	if(!(Splitter::sTexture.loadFromFile("Equipments_Image/Splitter.png")))
	{
		std::cout << "Error: could not load Mirror image!" << std::endl;
	}

}

bool Splitter::isHit()
{
	return true;
}

bool Splitter::isLaserSource()
{
	return false;
}

void Splitter::lightOff(){}