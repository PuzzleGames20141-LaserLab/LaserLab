#ifndef PHOTON_H
#define PHOTON_H

#include <SFML\Graphics.hpp>
#include "Macro.h"



class Photon : public sf::Sprite
{
	char color;
	int dir;
	float velocity;

public:
	Photon(int initialDir, sf::Color color);
	int getDirection();
	float getVelocity();
	void setVelocity(float v);
	void myRotate(int newDir);
	void myMove();
	int getIndex();
	static sf::Texture lightTexture;
	static void loadTexture();

};

#endif