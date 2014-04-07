#include "Photon.h"
#include "Macro.h"
#include<iostream>
#include<cmath>

sf::Texture Photon::lightTexture;
Photon::Photon(int initialDir, sf::Color col)
{
	setOrigin(BLOCK_SIZE/2, BLOCK_SIZE/2);
	setTexture(lightTexture);
	dir = initialDir;
	setVelocity((float)BLOCK_SIZE);
	setRotation((float)45*(initialDir-1));
	sf::Sprite::setColor(sf::Color::Red);
	setColor(col);
}

int Photon::getDirection()
{
	return dir;
}


void Photon::myRotate(int newDir)
{
	float deltaX = 0;
	float deltaY = 0;
	if(dir == 1 || dir == 5)
	{
		deltaX = (float)(BLOCK_SIZE*(3-dir)/4);
	}
	else if(dir == 3 || dir == 7)
	{
		deltaY = (float)(BLOCK_SIZE*(dir-5)/4);
	}
	sf::Vector2f delta_1(deltaX, deltaY);
	deltaX = 0;
	deltaY = 0;
	if(newDir == 1 || newDir == 5)
	{
		deltaX = (float)(BLOCK_SIZE*(3-newDir)/4);
	}
	else if(newDir == 3 || newDir == 7)
	{
		deltaY = (float)(BLOCK_SIZE*(newDir-5)/4);
	}
	sf::Vector2f delta_2(deltaX, deltaY);
	setPosition(getPosition()+delta_1+delta_2);
	float angle = (float)(newDir-dir)*45;
	rotate(angle);
	dir = newDir;

}
float Photon::getVelocity()
{
	return velocity;
}

void Photon::setVelocity(float v)
{
	velocity = v;
}
void Photon::myMove()
{
	float deltaX = 0;
	float deltaY = 0;
	if(dir == 1 || dir == 5)
	{
		deltaX = (float)(velocity*(3-dir)/2);
	}
	else if(dir == 3 || dir == 7)
	{
		deltaY = (float)(velocity*(dir-5)/2);
	}
	move(deltaX, deltaY);
}

int Photon::getIndex()
{
	int deltaX = 0;
	int deltaY = 0;
	if(dir == 1 || dir == 5)
	{
		deltaX = (int)(velocity*(3-dir)/8);
	}
	else if(dir == 3 || dir == 7)
	{
		deltaY = (int)(velocity*(dir-5)/8);
	}
	int x_coord = (int)getPosition().x + deltaX;
	int y_coord = (int)getPosition().y + deltaY;
	int row = (y_coord-MARGIN)/BLOCK_SIZE;
	int col = (x_coord-MARGIN)/BLOCK_SIZE;
	return row*GRID_WIDTH + col;
}
void Photon::loadTexture()
{
	if(!(Photon::lightTexture.loadFromFile("Equipments_Image/Light.png")))
	{
		std::cout << "Error: could not load light image!" << std::endl;
	}
}