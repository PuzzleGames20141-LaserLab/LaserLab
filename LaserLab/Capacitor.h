#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>


class Capacitor : public Equipment
{
	bool hit;

public:
	sf::Color color;
	int state;
	Capacitor();
	bool isLaserSource() override;
	int curState() override; // real curState function;
	bool isHit() override; // real isHit function
	void clone(std::shared_ptr<Equipment>& ePtr) override; // dummy clone function
	void myRotate() override; // dummy rotation function
	void myRotate_E() override; // valid rotation function for Editor mode
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void lightOff() override; // real lightOff function
	static sf::Texture idle_Texture;
	static sf::Texture charged_Texture;
	static void loadTexture();
};

//Target::eTexture.loadFromFile("Target.png");
/*
if(!(Target::eTexture.loadFromFile("Target.png")))
{
	std::cout << "Error: could not load Target image!" << std::endl;
}
*/
#endif