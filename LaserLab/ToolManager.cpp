#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <map>

#include "ToolManager.h"
#include "GameScreen.h"

ToolManager::ToolManager()
{
	mouseBounds_.width = 1.f;
	mouseBounds_.height = 1.f;
	state = 0;
	state_right = 0;
	changeIdx = 0;
}

void ToolManager::update(sf::RenderWindow& window)
{
	
	mouseBounds_.left = (float)sf::Mouse::getPosition(window).x;
	mouseBounds_.top = (float)sf::Mouse::getPosition(window).y;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(ToolManager::getState() == 0)
		{
			//check if the equipments on the toolbar is been selected
			std::map<std::string, std::shared_ptr<Equipment>>::iterator it = equipments_.begin();
			for(; it!= equipments_.end(); it++)
			{
				if((*it).second->getGlobalBounds().intersects(mouseBounds_))
				{
					if((currentScore - (*it).second->cost) < 0)
						break;
					std::shared_ptr<Equipment> new_equipment;
					((*it).second)->clone(new_equipment);
					ToolManager::setCopyEquipment(new_equipment);
					ToolManager::setState(1);
					break;
				}
			}

			//check if the equipment on the grid is selected
			std::map<int, std::shared_ptr<Equipment>>::iterator it_grid = equipments_on_grid_move_.begin();
			int flag_find = 0;
			for(; it_grid!= equipments_on_grid_move_.end(); it_grid++)
			{
				if(ToolManager::getState() == 1)
					break;

				if((*it_grid).second->getGlobalBounds().intersects(mouseBounds_))
				{
					ToolManager::setCopyEquipment((*it_grid).second);
					ToolManager::setState(2);
					flag_find = 1;
					break;
				}

			}
			if(flag_find == 1)
			{
				int key = (*it_grid).first;
				currentScore += ((*it_grid).second)->cost;
				equipments_on_grid_move_.erase(key);
				equipments_on_grid_.erase(key);
				changeIdx  = key;

			}


		}

		if(ToolManager::getState() == 1 || ToolManager::getState() == 2)
		{
			ToolManager::getCopyEquipment()->setPosition((sf::Vector2f) sf::Mouse::getPosition(window) );
		}

	}

	if( !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(ToolManager::state == 1 || ToolManager::state == 2)
		{
			unsigned int x = sf::Mouse::getPosition(window).x;
			unsigned int y = sf::Mouse::getPosition(window).y;
			if(x>20&&x<620&&y>20&&y<500)
			{
				int row = (y-MARGIN)/BLOCK_SIZE;
				int col = (x-MARGIN)/BLOCK_SIZE;
				std::shared_ptr<Equipment> new_equipment;
				(ToolManager::copy_equipment)->clone(new_equipment);
				ToolManager::equipments_on_grid_.insert(std::pair<int, std::shared_ptr<Equipment>>((row*GRID_WIDTH + col), new_equipment));
				ToolManager::equipments_on_grid_move_.insert(std::pair<int, std::shared_ptr<Equipment>>((row*GRID_WIDTH + col), new_equipment));
				currentScore -= new_equipment->cost;
				changeIdx = row*GRID_WIDTH + col;
			}

		}

		ToolManager::setState(0);
					
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) || ToolManager::getStateRight() == 1)
	{		
		ToolManager::setStateRight(1);
		if(!(sf::Mouse::isButtonPressed(sf::Mouse::Right)))
		{
			ToolManager::setStateRight(0);
		}
		
		if(ToolManager::getStateRight() == 0)
		{
			std::map<int, std::shared_ptr<Equipment>>::iterator it_on_grid = ToolManager::equipments_on_grid_.begin();
			for(; it_on_grid!=ToolManager::equipments_on_grid_.end(); it_on_grid ++)
			{
				if((*it_on_grid).second->getGlobalBounds().intersects(mouseBounds_))
				{	
					(*it_on_grid).second->myRotate();
					changeIdx = (*it_on_grid).first;
				}
			}
		}
	}
}

// display the equipment, equipment itself can display
void ToolManager::render(sf::RenderWindow& window)
{

}

void ToolManager::addEquipment(const std::string& id, std::shared_ptr<Equipment>& equipment)
{
	equipments_[id] = equipment;
}

void ToolManager::removeEquipment(const std::string& id)
{
	equipments_.erase(id);
}

int ToolManager::getState()
{
	return ToolManager::state;
}

void ToolManager::setState(int val)
{
	ToolManager::state = val;
}

int ToolManager::getStateRight()
{
	return ToolManager::state_right;
}

void ToolManager::setStateRight(int val)
{
	ToolManager::state_right = val;
}

std::shared_ptr<Equipment> ToolManager::getCopyEquipment()
{
	return ToolManager::copy_equipment;
}

void ToolManager::setCopyEquipment(std::shared_ptr<Equipment>& new_copy)
{
	ToolManager::copy_equipment = new_copy;
}

