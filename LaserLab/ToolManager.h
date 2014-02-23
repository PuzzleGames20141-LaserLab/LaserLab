#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H


#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>

#include "Equipment.h"

class ToolManager
{
public:
	ToolManager();

	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	void addEquipment(const std::string& id, std::shared_ptr<Equipment>& equipment);
	void removeEquipment(const std::string& id);
	std::map<std::string,  std::shared_ptr<Equipment>> equipments_;
	std::vector<std::shared_ptr<Equipment>> equipments_on_grid_;

private:
	sf::FloatRect mouseBounds_;

};


#endif