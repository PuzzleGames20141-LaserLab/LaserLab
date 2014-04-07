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

void Grid::loadGrid(std::string* layout, std::map<int, std::shared_ptr<Equipment>>& equipMap, std::vector<LaserSource>& my_lasers, std::vector<std::shared_ptr<Equipment>>& my_targets, std::vector<std::shared_ptr<Equipment>>& my_capacitors)
{
	for (int row = 0; row < GRID_HEIGHT; row++) 
	{
		std::vector<sf::Sprite> rowVec = std::vector<sf::Sprite>();
		for (int col = 0; col < GRID_WIDTH; col++)
		{
			sf::Sprite block = sf::Sprite();
			block.setTexture(gridTexture);
			block.setPosition((float)(MARGIN+col*(BLOCK_SIZE)), (float)(MARGIN+row*(BLOCK_SIZE)));
			rowVec.push_back(block);
			
			switch(layout[row][2*col])
			{
				case LASER_SOURCE_U_RED:
				{
					LaserSource myLaser('r');
					myLaser.setRotation(270);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_D_RED:
				{
					LaserSource myLaser('r');
					myLaser.setRotation(90);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_L_RED:
				{
					LaserSource myLaser('r');
					myLaser.setRotation(180);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_R_RED:
				{
					LaserSource myLaser('r');
					myLaser.setRotation(0);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case DOOR_U_RED:
				{
					Target myTarget(sf::Color::Red);
					myTarget.setRotation(90);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_R_RED:
				{
					Target myTarget(sf::Color::Red);
					myTarget.setRotation(180);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_D_RED:
				{
					Target myTarget(sf::Color::Red);
					myTarget.setRotation(270);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					myTarget.setColor(sf::Color::Red);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_L_RED:
				{
					Target myTarget(sf::Color::Red);
					myTarget.setRotation(0);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case LASER_SOURCE_U_BLUE:
				{
					LaserSource myLaser('b');
					myLaser.setRotation(270);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_D_BLUE:
				{
					LaserSource myLaser('b');
					myLaser.setRotation(90);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_L_BLUE:
				{
					LaserSource myLaser('b');
					myLaser.setRotation(180);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case LASER_SOURCE_R_BLUE:
				{
					LaserSource myLaser('b');
					myLaser.setRotation(0);
					myLaser.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					my_lasers.push_back(myLaser);
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<LaserSource>(myLaser)));
					break;
				}
				case DOOR_U_BLUE:
				{
					Target myTarget(sf::Color::Blue);
					myTarget.setRotation(90);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_R_BLUE:
				{
					Target myTarget(sf::Color::Blue);
					myTarget.setRotation(180);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_D_BLUE:
				{
					Target myTarget(sf::Color::Blue);
					myTarget.setRotation(270);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case DOOR_L_BLUE:
				{
					Target myTarget(sf::Color::Blue);
					myTarget.setRotation(0);
					myTarget.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Target>(myTarget)));
					my_targets.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case PIT:
				{
					Pit myPit;
					myPit.setRotation(0);
					myPit.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Pit>(myPit)));
					break;
				}
				case WALL:
				{
					Wall myWall;
					myWall.setRotation(0);
					myWall.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Wall>(myWall)));
					break;
				}
				case BOMB:
				{
					Bomb myBomb;
					myBomb.setRotation(0);
					myBomb.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Bomb>(myBomb)));
					break;
				}
				case CAPACITOR_U:
				{
					Capacitor myCap;
					myCap.setRotation(270);
					myCap.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Capacitor>(myCap)));
					my_capacitors.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case CAPACITOR_R:
				{
					Capacitor myCap;
					myCap.setRotation(0);
					myCap.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Capacitor>(myCap)));
					my_capacitors.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case CAPACITOR_D:
				{
					Capacitor myCap;
					myCap.setRotation(90);
					myCap.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Capacitor>(myCap)));
					my_capacitors.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}
				case CAPACITOR_L:
				{
					Capacitor myCap;
					myCap.setRotation(180);
					myCap.setPosition((float)(2*MARGIN+col*(BLOCK_SIZE)), (float)(2*MARGIN+row*(BLOCK_SIZE)));
					equipMap.insert(std::pair<int, std::shared_ptr<Equipment>>(row*GRID_WIDTH + col, std::make_shared<Capacitor>(myCap)));
					my_capacitors.push_back(equipMap[row*GRID_WIDTH + col]);
					break;
				}

			}
			
		}
		gridVec.push_back(rowVec);
	}
}

void Grid::loadGridEdit()
{
	for (int row = 0; row < GRID_HEIGHT; row++) 
	{
		std::vector<sf::Sprite> rowVec = std::vector<sf::Sprite>();
		for (int col = 0; col < GRID_WIDTH; col++)
		{
			sf::Sprite block = sf::Sprite();
			block.setTexture(gridTexture);
			block.setPosition((float)(MARGIN+col*(BLOCK_SIZE)), (float)(MARGIN+row*(BLOCK_SIZE)));
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
	text = new std::string[100];
	std::ifstream myfile(fileName);
	int lineNum = 0;
	while(std::getline(myfile, text[lineNum]))
	{
		lineNum++;
	}
	return text;
}