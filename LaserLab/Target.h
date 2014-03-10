#ifndef TARGET_H
#define TARGET_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Target : public Equipment
{
	sf::Color col;
	bool hit;
public:
	Target();
	bool isHit() override; // real isHit function
	void clone(std::shared_ptr<Equipment>& ePtr) override; // dummy clone function
	void myRotate() override; // dummy rotation function
	void myRotate_E() override; // valid rotation function for Editor mode
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void lightOff() override; // real lightOff function
	void setColor(sf::Color myCol);
	static sf::Texture tTexture;
	static sf::Texture tHitTexture;
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