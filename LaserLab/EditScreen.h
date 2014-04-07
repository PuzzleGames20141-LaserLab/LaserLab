#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include <SFML/GRAPHICS.hpp>

#include <memory>
#include <vector>

#include "Photon.h"
#include "Equipment.h"
#include "Screen.h"
#include "ToolManagerEdit.h"
#include "Macro.h"
#include "Grid.h"
#include "ButtonManager.h"


class EditScreen : public Screen
{
public :
	EditScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	void loadGridEdit_();
	void loadEquipmentEdit();
	//void loadUseEquipmentEdit();
	void handleLaserEdit();
	void save(sf::RenderWindow& window);
	void saveToFile(char levelName_arr[], char initMoney_arr[], char twoStarScore_arr[], char threeStarScore_arr[]);

private:
	Grid myGrid_edit;
	void drawGridEdit(sf::RenderWindow& window);
	void drawEquitmentEdit(sf::RenderWindow& window);
	void calculatePathEdit();
	void drawLaserEdit(sf::RenderWindow& window);
	ToolManagerEdit tool_manager_edit;
	std::vector<std::vector<Photon>> lightPaths_edit;
	ButtonManager buttonManager_edit;
	UserButton clearButton_edit;
	UserButton saveButton_edit;
	UserButton goBackButton_edit;
	sf::Texture background_edit;
	sf::Texture background;
	sf::Sprite backgroundSp;
	std::vector<std::vector<Photon>> capLightPaths;
};

std::string* loadEquipmentTXT_edit(const char*fileName);

#endif