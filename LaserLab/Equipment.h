#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <SFML\Graphics.hpp>
#include "Photon.h"
#include <string.h>

class Equipment : public sf::Sprite
{
public:
	Equipment();
	void reaction(Photon& photon){};
	//virtual void render(sf::RenderWindow& window) = 0;
	//void setPosition(float x, float y);
	sf::Texture eTexture;
	//sf::Sprite sprite_equipment;
	
};

#endif