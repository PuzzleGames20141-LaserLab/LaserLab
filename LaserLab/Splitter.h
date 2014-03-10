#ifndef SPLITTER_H
#define SPLITTER_H

#include <SFML\Graphics.hpp>
#include "Equipment.h"
#include "Photon.h"
#include <string.h>

class Splitter : public Equipment
{
public:
	Splitter();
	void reaction(Photon &photon, std::vector<std::vector<Photon>>& lightPaths) override;
	void clone(std::shared_ptr<Equipment>& ePtr) override;
	bool isHit() override; //dummy isHit function always return true;
	void lightOff() override; // dummy lightOff function
	void myRotate() override;  // valid rotation function for Play mode
	void myRotate_E() override; // valid rotation function for Editor mode
	static sf::Texture sTexture;
	static void loadTexture();
};

#endif