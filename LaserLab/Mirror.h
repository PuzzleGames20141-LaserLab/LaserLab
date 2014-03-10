#ifndef MIRROR_H
#define MIRROR_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Mirror : public Equipment
{
public:
	Mirror();
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void clone(std::shared_ptr<Equipment>& ePtr) override;
	bool isHit() override; //dummy isHit function always return true;
	void lightOff() override; // dummy lightOff function
	void myRotate() override;  // valid rotation function for play mode
	void myRotate_E() override; // valid rotation function for Editor mode
	static sf::Texture mTexture;
	static void loadTexture();
};

//Mirror::eTexture.loadFromFile("Mirror.png");
/*
if(!(Mirror::eTexture.loadFromFile("Mirror.png")))
{
	std::cout << "Error: could not load Mirror image!" << std::endl;
}
*/
#endif