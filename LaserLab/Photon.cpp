#include "Photon.h"
#include "Macro.h"
#include<iostream>
#include<cmath>

Photon::Photon(sf::Color col, float rad, float angle)
{
	setRadius(rad);
	setFillColor(col);
	pAngle = angle;
	velocity = 1.0;
}

float Photon::getDirection()
{
	return pAngle;
}

void Photon::setDirection(float angle)
{
	pAngle = angle;
}

float Photon::getVelocity()
{
	return velocity;
}

void Photon::setVelocity(float v)
{
	velocity = v;
}

void Photon::move()
{
	float deltaX = velocity * cos(PI*(pAngle/180));
	float deltaY = velocity * sin(PI*(pAngle/180));
	CircleShape::move(deltaX, deltaY);
}