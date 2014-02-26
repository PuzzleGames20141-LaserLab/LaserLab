#include "Grid.h"
#include "Macro.h"
#include<fstream>
#include<iostream>
#include <SFML\Graphics.hpp>

Grid::Grid()
{
	if(!gridTexture.loadFromFile("Background/block.png")) 
	{
		std::cout << "Error: could not load grid image!" << std::endl;
	}
	gridVec = std::vector<std::vector<sf::Sprite>>();
	//gridColor = sf::Color(255,255,255,20);
}
void Grid::loadGrid(std::string* layout, std::map<int, std::shared_ptr<Equipment>>& equipMap, std::vector<LaserSource>& my_lasers)
{
	for (int row = 0; row < GRID_HEIGHT; row++) 
	{
		std::vector<sf::Sprite> rowVec = std::vector<sf::Sprite>();
		for (int col = 0; col < GRID_WIDTH; col++)
		{
			sf::Sprite block = sf::Sprite();
			block.setTexture(gridTexture);
			block.setPosition(MARGIN+col*(BLOCK_SIZE), MARGIN+row*(BLOCK_SIZE));
			rowVec.push_back(block);
			
			switch(layout[row][2*col])
			{
				case LASER_SOURCE_U_RED:
				{
					LaserSource myLaser;
					myLaser.setRotation(270);
					myLaser.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myLaser.setColor(sf::Color::Red);
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_D_RED:
				{
					LaserSource myLaser;
					myLaser.setRotation(90);
					myLaser.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myLaser.setColor(sf::Color::Red);
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_L_RED:
				{
					LaserSource myLaser;
					myLaser.setRotation(180);
					myLaser.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myLaser.setColor(sf::Color::Red);
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_R_RED:
				{
					LaserSource myLaser;
					myLaser.setRotation(0);
					myLaser.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myLaser.setColor(sf::Color::Red);
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case DOOR_U_RED:
				{
					Target myTarget;
					myTarget.setRotation(90);
					myTarget.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myTarget.setColor(sf::Color::Red);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					break;
				}
				case DOOR_R_RED:
				{
					Target myTarget;
					myTarget.setRotation(180);
					myTarget.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myTarget.setColor(sf::Color::Red);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					break;
				}
				case DOOR_D_RED:
				{
					Target myTarget;
					myTarget.setRotation(270);
					myTarget.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myTarget.setColor(sf::Color::Red);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					break;
				}
				case DOOR_L_RED:
				{
					Target myTarget;
					myTarget.setRotation(0);
					myTarget.setPosition(2*MARGIN+col*(BLOCK_SIZE), 2*MARGIN+row*(BLOCK_SIZE));
					myTarget.setColor(sf::Color::Red);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					break;
				}
			}
			
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