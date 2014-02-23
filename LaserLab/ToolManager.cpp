#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <map>

#include "ToolManager.h"

ToolManager::ToolManager()
{
	mouseBounds_.width = 1.f;
	mouseBounds_.height = 1.f;
}

void ToolManager::update(sf::RenderWindow& window)
{
	mouseBounds_.left = sf::Mouse::getPosition(window).x;
	mouseBounds_.top = sf::Mouse::getPosition(window).y;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::map<std::string, std::shared_ptr<Equipment>>::iterator it = equipments_.begin();
		for(; it!= equipments_.end(); it++)
		{
			if((*it).second->getGlobalBounds().intersects(mouseBounds_))
			{
				//clone a equipment


				//move

				//while(mouse.isPressed)

				//mouse.isReleased, place the equipment

				//vector.add(equipment)

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