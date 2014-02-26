#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <SFML\Graphics.hpp>
#include "Photon.h"
#include <string.h>

class Equipment : public sf::Sprite
{
public:
	Equipment();
	virtual void reaction(Photon& photon, std::vector<std::vector<Photon>>& lightPaths) = 0;
	virtual void myRotate() = 0;
	virtual void clone(std::shared_ptr<Equipment>& ePtr) = 0;
};

#endif