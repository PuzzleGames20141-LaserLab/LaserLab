#ifndef LASER_SOURCE_H
#define LASER_SOURCE_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class LaserSource : public Equipment
{
	sf::Color col;

public:
	LaserSource();
	void setColor(sf::Color myCol);
	void reaction(Photon &photon) override;
	Photon getPhoton(float rad);
};

#endif