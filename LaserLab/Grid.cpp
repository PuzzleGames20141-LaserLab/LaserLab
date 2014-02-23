#include "Grid.h"
#include "Macro.h"
#include<fstream>
#include<iostream>
#include <SFML\Graphics.hpp>

Grid::Grid()
{
	if(!gridTexture.loadFromFile("block.png")) 
	{
		std::cout << "Error: could not load grid image!" << std::endl;
	}
	//if(!laserTexture.loadFromFile("laser.png")) 
	//{
	//	std::cout << "Error: could not load grid image!" << std::endl;
	//}
	gridVec = std::vector<std::vector<sf::Sprite>>();
	gridColor = sf::Color(255,255,255,20);
}
void Grid::loadGrid(std::string* layout)
{
	for (int row = 0; row < GRID_HEIGHT; row++) 
	{
		std::vector<sf::Sprite> rowVec = std::vector<sf::Sprite>();
		for (int col = 0; col < GRID_WIDTH; col++)
		{
			sf::Sprite block = sf::Sprite();
			switch(layout[row][2*col])
			{
				case EMPTY:
					block.setTexture(gridTexture);
					block.setPosition(MARGIN+col*(BLOCK_SIZE), MARGIN+row*(BLOCK_SIZE));
					block.setColor(gridColor);
					break;
				case LASER_SOURCE_U:
					block.setTexture(laserTexture);
					block.setPosition(MARGIN+col*(BLOCK_SIZE), MARGIN+row*(BLOCK_SIZE));
					block.setColor(gridColor);
					break;
			}
			rowVec.push_back(block);
		}
		gridVec.push_back(rowVec);
	}
}

std::vector<std::vector<sf::Sprite>> Grid::getSprites() 
{
	return gridVec;
}

std::string* loadTXT(const char* fileName)
{
	std::string* text;
	text = new std::string[GRID_HEIGHT+1];
	std::ifstream myfile(fileName);
	int lineNum = 0;
	while(std::getline(myfile, text[lineNum]))
	{
		lineNum++;
	}
	return text;
}