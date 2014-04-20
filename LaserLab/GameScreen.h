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
#include "MyNode.h"
#include "queue"

extern int curr_level;
extern int currentScore;
extern  std::string user_curr_level;
extern int changeIdx;
extern int hint_time;

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
	int total_target;
	int curr_hit;
	std::vector<std::vector<MyNode>> result_paths;

private:
	Grid myGrid;
	void drawGrid(sf::RenderWindow& window);
	void drawEquitment(sf::RenderWindow& window);
	void calculatePath();
	void GameScreen::calculateAuto(int laserIdx, int laserDir, std::vector<std::vector<Photon>> &autoLights);
	void drawLaser(sf::RenderWindow& window);
	void drawEnd(sf::RenderWindow& window);
	void drawScore(sf::RenderWindow& window);
	void GameScreen::initialize(std::vector<std::vector<MyNode>> &nodeGrid, std::queue<MyNode> &myQueue, bool visited[12][15]);
	void GameScreen::autoSolver(sf::RenderWindow& window);
	void GameScreen::calculateAuto(int laserIdx, int laserDir, std::vector<std::vector<Photon>> &autoLights, std::vector<std::vector<MyNode>> & nodeGrid);
	void GameScreen::copyOfNode(MyNode &copy_curr1, MyNode &curr);
	void GameScreen::storePath(MyNode *end, std::vector<std::vector<MyNode>> &paths);
	void GameScreen::showPath(sf::RenderWindow& window,  std::vector<std::vector<MyNode>> paths);
	bool GameScreen::checkPassLevel(std::vector<std::vector<MyNode>> paths);
	void GameScreen::drawHint(sf::RenderWindow& window);
	ToolManager tool_manager;
	std::vector<std::vector<Photon>> lightPaths;
	std::vector<sf::Sprite> equipments_money;
	ButtonManager buttonManager_game;
	ButtonManager buttonManager_end;
	UserButton clearButton;
	UserButton goBackButton;
	UserButton nextLevelButton;
	UserButton replayButton;
	UserButton hintButton;
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