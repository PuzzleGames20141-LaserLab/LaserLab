#ifndef PHOTON_H
#define PHOTON_H

#include <SFML\Graphics.hpp>
#include "Macro.h"

class Photon : public sf::CircleShape
{
	float pAngle;
	float velocity;
	std::string polarization;
	std::string color;

public:
	Photon(sf::Color col, float rad, float angle = 0.0f);
	float getDirection();
	void setDirection(float angle);
	float getVelocity();
	void setVelocity(float v);
	void polarize(std::string &polar);
	void setColor(std::string &col);
	void move();
};

#endif