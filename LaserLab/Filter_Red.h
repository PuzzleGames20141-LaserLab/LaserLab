#ifndef FILTER_RED_H
#define FILTER_RED_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Filter_Red : public Equipment
{
	sf::Color color;

public:
	Filter_Red();
	bool isLaserSource() override; // always return true;
	int curState(){ return -1;}; // dummy curState function always return -1;
	bool isHit() override; //dummy isHit function always return true;
	void lightOff() override; // dummy lightOff function
	void myRotate() override; // dummy rotation function
	void myRotate_E() override; // valid rotation function for Editor mode
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void clone(std::shared_ptr<Equipment>& ePtr) override; // dummy clone function
	static sf::Texture fTexture;
	static void loadTexture();
};

//LaserSource::eTexture.loadFromFile("LaserSource.png");

#endif