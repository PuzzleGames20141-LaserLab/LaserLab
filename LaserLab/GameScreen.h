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
#include "ButtonManager.h"


extern int curr_level;
extern int currentScore;
extern  std::string user_curr_level;
extern int canSolve;
extern int changeIdx;

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
	int allHit;
	int renderCount;


private:
	Grid myGrid;
	void drawGrid(sf::RenderWindow& window);
	void drawEquitment(sf::RenderWindow& window);
	void calculatePath();
	void drawLaser(sf::RenderWindow& window);
	void drawEnd(sf::RenderWindow& window);
	void drawScore(sf::RenderWindow& window);
	bool GameScreen::autoSolver(sf::RenderWindow& window);
	ToolManager tool_manager;
	std::vector<std::vector<Photon>> lightPaths;
	std::vector<sf::Sprite> equipments_money;
	ButtonManager buttonManager_game;
	ButtonManager buttonManager_end;
	UserButton clearButton;
	UserButton goBackButton;
	UserButton nextLevelButton;
	UserButton replayButton;
	sf::Texture zero_star;
	sf::Texture one_star;
	sf::Texture two_star;
	sf::Texture three_star;
	sf::Texture transparent_background;
	sf::Texture congratulation;
	sf::Texture background;
	sf::Sprite backgroundSp;
	sf::Font font;
	sf::Texture mirror_money;
	sf::Texture splitter_money;
	sf::Texture filter_red_money;
	sf::Texture filter_blue_money;
	std::vector<std::vector<Photon>> capLightPaths;


};

std::string* loadEquipmentTXT(const char* fileName);

#endif