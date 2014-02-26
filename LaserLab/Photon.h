#ifndef PHOTON_H
#define PHOTON_H

#include <SFML\Graphics.hpp>
#include "Macro.h"



class Photon : public sf::Sprite
{

	std::string color;
	int dir;
	float velocity;

public:
	Photon(int initialDir);
	int getDirection();
	float getVelocity();
	void setVelocity(float v);
	void setColor(std::string& newColor);
	void myRotate(int newDir);
	void myMove();
	int getIndex();
	static sf::Texture lightTexture;
	static void loadTexture(std::string color);

};

#endif