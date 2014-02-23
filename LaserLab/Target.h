#ifndef TARGET_H
#define TARGET_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Target : public Equipment
{
	sf::Color col;
	bool isHit;
public:
	Target();
	bool isSuccess();
	void reaction(Photon &photon) override;
	void setColor(sf::Color myCol);
};

#endif