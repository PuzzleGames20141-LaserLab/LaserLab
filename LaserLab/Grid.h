#ifndef GRID_H
#define GRID_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Macro.h"
#include <string.h>

class Grid 
{
	sf::Texture gridTexture;
	sf::Texture wallTexture;
	sf::Texture laserTexture;
	sf::Texture poweredTexture;
	sf::Texture bombTexture;
	sf::Texture capTexture;
	sf::Color gridColor;
	std::vector<std::vector<sf::Sprite>> gridVec;
	
public:
	Grid();
	void loadGrid(std::string* layout);

	std::vector<std::vector<sf::Sprite>> getSprites();

};

std::string* loadTXT(const char* fileName);

#endif