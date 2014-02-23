#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <SFML\Graphics.hpp>
#include "Photon.h"
#include <string.h>

class Equipment : public sf::Sprite
{
public:
	Equipment();
	virtual void reaction(Photon& photon) = 0;
	sf::Texture eTexture;
};

#endif