#include "Mirror.h"
#include "Photon.h"
#include <string.h>
#include <iostream>
#include <cmath>

Mirror::Mirror()
{
	if(!eTexture.loadFromFile("Mirror.png"))
	{
		std::cout << "Error: could not load mirror image!" << std::endl;
	}
	setTexture(eTexture);
}

void Mirror::reaction(Photon& photon)
{
	float mAngle = getRotation();
	float pAngle = photon.getDirection();
	float pAngle_r = pAngle+180 >= 360 ? pAngle-180 : pAngle+180;
	if(fabs(mAngle - pAngle_r) < 90 || fabs(mAngle - pAngle_r) > 270)
	{
		pAngle = pAngle_r + 2 * (mAngle-pAngle_r);
		if(pAngle < 0) pAngle += 360;
		if(pAngle >= 360) pAngle -= 360;
		photon.setDirection(pAngle);
	}
	else 
	{
		photon.setVelocity(0.0);
	}
}