#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H


#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>

#include "Equipment.h"
#include "LaserSource.h"
#include "Macro.h"
#include "Capacitor.h"

class ToolManager
{
public:
	ToolManager();

	void update(sf::RenderWindow& window); //used to check if the equipment is selected
	void render(sf::RenderWindow& window);

	void addEquipment(const std::string& id, std::shared_ptr<Equipment>& equipment);
	void removeEquipment(const std::string& id);
    int getState();
	void setState(int val);
	int getStateRight();
	void setStateRight(int val);

	std::shared_ptr<Equipment> getCopyEquipment();
	void setCopyEquipment(std::shared_ptr<Equipment>& new_copy);

	std::map<std::string,  std::shared_ptr<Equipment>> equipments_;
	std::map<int, std::shared_ptr<Equipment>> equipments_on_grid_;
	std::map<int, std::shared_ptr<Equipment>> equipments_on_grid_move_;
	std::vector<LaserSource> my_lasers_;
	std::vector<Photon> my_Photons;
	std::vector<std::shared_ptr<Equipment>> my_targets_;
	std::vector<std::shared_ptr<Equipment>> my_capacitors_;
	int changeIdx;


private:
	sf::FloatRect mouseBounds_;
	int state; //state == 0: button is not pressed, state===1:button is pressed with toolbar equipment, state==2, button is pressed with grid equipment
	int state_right; //right button state
	std::shared_ptr<Equipment> copy_equipment;

};


#endif