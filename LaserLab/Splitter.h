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
	void myRotate() override;
	static sf::Texture sTexture;
	static void loadTexture();
};

#endif