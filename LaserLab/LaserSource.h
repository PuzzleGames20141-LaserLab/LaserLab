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
	bool isHit() override; //dummy isHit function always return true;
	void lightOff() override; // dummy lightOff function
	void myRotate() override; // dummy rotation function
	void myRotate_E() override; // valid rotation function for Editor mode
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void clone(std::shared_ptr<Equipment>& ePtr) override; // dummy clone function
	Photon getPhoton();
	static sf::Texture lTexture;
	static void loadTexture();
};

//LaserSource::eTexture.loadFromFile("LaserSource.png");

#endif