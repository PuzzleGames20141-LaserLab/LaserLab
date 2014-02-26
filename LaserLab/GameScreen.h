#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML\Graphics.hpp>

#include <memory>
#include <vector>

#include "Photon.h"
#include "Screen.h"
#include "Equipment.h"
#include "ToolManager.h"
#include "Macro.h"
#include "Grid.h"


class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	void loadGrid();
	void loadEquipment();
	void handleLaser();

private:
	Grid myGrid;
	void drawGrid(sf::RenderWindow& window);
	void drawEquitment(sf::RenderWindow& window);
	void calculatePath();
	void drawLaser(sf::RenderWindow& window);
	ToolManager tool_manager;
	std::vector<std::vector<Photon>> lightPaths;
};

std::string* loadEquipmentTXT(const char* fileName);

#endif