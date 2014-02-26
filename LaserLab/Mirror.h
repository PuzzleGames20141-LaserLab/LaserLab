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
	void myRotate() override;
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