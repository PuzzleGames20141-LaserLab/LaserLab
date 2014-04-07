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
	cost = 10;
	label = 'a';
}

void Mirror::reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths)
{
	int mir_Dir = (int)this->getRotation();
	int photon_Dir = photon.getDirection();
	int newDir = 0;
	switch(mir_Dir)
	{
	case 0:
		{
			if(photon_Dir == 1 || photon_Dir == 3)
			{
				newDir = 8 - photon_Dir;
				photon.myRotate(newDir);
			}
			else
			{
				photon.setVelocity(0.0);
			}
			break;
		}
	case 90:
		{
			if(photon_Dir == 1 || photon_Dir == 7)
			{
				newDir = (12 - photon_Dir)%8;
				photon.myRotate(newDir);
			}
			else
			{
				photon.setVelocity(0.0);
			}
			break;
		}
	case 180:
		{
			if(photon_Dir == 5 || photon_Dir == 7)
			{
				newDir = 8 - photon_Dir;
				photon.myRotate(newDir);
			}
			else
			{
				photon.setVelocity(0.0);
			}
			break;
		}
	case 270:
		{
			if(photon_Dir == 3 || photon_Dir == 5)
			{
				newDir = (12 - photon_Dir)%8;
				photon.myRotate(newDir);
			}
			else
			{
				photon.setVelocity(0.0);
			}
			break;
		}
	default: break;
	}
}

void Mirror::clone(std::shared_ptr<Equipment>& ePtr)
{
	Mirror copyMirror = *this;
	ePtr = std::make_shared<Mirror>(copyMirror);
}

void Mirror::myRotate()
{
	setRotation(this->getRotation()+90);
}

void Mirror::myRotate_E()
{
	myRotate();
}

void Mirror::loadTexture()
{
	if(!(Mirror::mTexture.loadFromFile("Equipments_Image/Mirror.png")))
	{
		std::cout << "Error: could not load Mirror image!" << std::endl;
	}

}

bool Mirror::isHit()
{
	return true;
}

bool Mirror::isLaserSource()
{
	return false;
}

void Mirror::lightOff(){}