#include "Mirror.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>

sf::Texture Mirror::mTexture;
Mirror::Mirror()
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(Mirror::mTexture);
}

void Mirror::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	float mAngle = getRotation();
	float pAngle = 360 - 45*(photon.getDirection()-1);
	float pAngle_r = pAngle+180 >= 360 ? pAngle-180 : pAngle+180;
	if(fabs(mAngle - pAngle_r) < 90 || fabs(mAngle - pAngle_r) > 270)
	{
		pAngle = pAngle_r + 2 * (mAngle-pAngle_r);
		if(pAngle < 0) pAngle += 360;
		if(pAngle >= 360) pAngle -= 360;
		if(pAngle > 0)
		{
			pAngle = 360-pAngle;
		}
		int newDir = (int)(pAngle/45)+1;
		photon.myRotate(newDir);
	}
	else 
	{
		photon.setVelocity(0.0);
	}
}

void Mirror::clone(std::shared_ptr<Equipment>& ePtr)
{
	Mirror copyMirror = *this;
	ePtr = std::make_shared<Mirror>(copyMirror);
	
}

void Mirror::myRotate()
{
	setRotation(this->getRotation()+45);
}

void Mirror::loadTexture()
{
	if(!(Mirror::mTexture.loadFromFile("Equipments_Image/Mirror.png")))
	{
		std::cout << "Error: could not load Mirror image!" << std::endl;
	}

}