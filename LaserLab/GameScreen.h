#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML\Graphics.hpp>

#include <memory>

#include "Screen.h"
#include "Equipment.h"
#include "ToolManager.h"


class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	void loadEquipment();


private:
	void drawGrid(sf::RenderWindow& window);
	void drawEquitment(sf::RenderWindow& window);
	void drawLaser(sf::RenderWindow& window);
	ToolManager tool_manager;
};

std::string* loadEquipmentTXT(const char* fileName);

#endif