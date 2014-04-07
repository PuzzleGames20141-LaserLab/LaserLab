#ifndef GRID_H
#define GRID_H

#include <SFML\Graphics.hpp>
#include <vector>
#include "Macro.h"
#include <string.h>
#include "Equipment.h"
#include "LaserSource.h"
#include "Target.h"
#include "Pit.h"
#include "Wall.h"
#include "Bomb.h"
#include "Capacitor.h"

class Grid 
{
	sf::Texture gridTexture;
	sf::Color gridColor;
	std::vector<std::vector<sf::Sprite>> gridVec;
	
public:
	Grid();
	void loadGrid(std::string* layout, std::map<int, std::shared_ptr<Equipment>>& equipMap, std::vector<LaserSource>& my_lasers, std::vector<std::shared_ptr<Equipment>>& my_targets, std::vector<std::shared_ptr<Equipment>>& my_capacitors);
	void loadGridEdit();
	std::vector<std::vector<sf::Sprite>> getSprites();

};

std::string* loadTXT(const char* fileName);

#endif