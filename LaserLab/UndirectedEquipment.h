#ifndef MACHINES_H
#define MACHINES_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Equipment.h"

class Machines : public Equipment
{
	sf::Vector2i direction; // normal vector of equipment surface

public:
	UserEquipment();
	void rotate(); // rotate the equipment by 90 degree clockwise
	sf::Vector2i getDirection();
};

#endif
laser source