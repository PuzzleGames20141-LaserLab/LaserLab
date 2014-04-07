#ifndef BOMB_H
#define BOMB_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Bomb : public Equipment
{
	sf::Color col;

public:
	Bomb();
	bool isLaserSource() override; // always return false;
	int curState(){ return -1;}; // dummy curState function always return -1;
	bool isHit() override; //dummy isHit function always return true;
	void lightOff() override; // dummy lightOff function
	void myRotate() override; // dummy rotation function
	void myRotate_E() override; // valid rotation function for Editor mode
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void clone(std::shared_ptr<Equipment>& ePtr) override; // dummy clone function
	static sf::Texture bTexture;
	static void loadTexture();
};


#endif