#include <SFML\Graphics.hpp>

#include <memory>
#include<fstream>
#include<iostream>
#include<queue>
#include<unordered_set>
#include <windows.h>

#include "MyNode.h"
#include "GameScreen.h"
#include "Game.h"
#include "Grid.h"
#include "Macro.h"
#include "Mirror.h"
#include "Equipment.h"
#include "Target.h"
#include "LevelSelectScreen.h"
#include "LevelManager.h"
#include "MenuScreen.h"
#include "Splitter.h"
#include "Pit.h"
#include "Wall.h"
#include "Bomb.h"
#include "Filter_Red.h"
#include "Filter_Blue.h"
#include "Capacitor.h"

int curr_hint_num = 0;
int curr_level = 1;
int currentScore  = 0;
std::string user_curr_level = "";
int changeIdx = 0;
bool isHint = false;
int hint_time = 0;

void my_callBack_goBack()
{
	Game::Screen = std::make_shared<LevelSelectScreen>();
}

void my_callBack_hint()
{
    hint_time = 4;
    isHint = true;
}

void my_callBack_clear()
{

	Game::Screen = std::make_shared<GameScreen>();
}

void my_callBack_next()
{
	curr_level++;
	Game::Screen = std::make_shared<GameScreen>();
}

void my_callBack_replay()
{
	//curr_level--;
	Game::Screen = std::make_shared<GameScreen>();
}

GameScreen::GameScreen()
	:goBackButton("Images/go_back.png"), clearButton("Images/clear_button.png"),nextLevelButton("Images/next_level_button.png"),replayButton("Images/replay_button.png"),hintButton("Images/level_hint.png")
{
	//put all the equipments needed in this level.
	goBackButton.callBack = &my_callBack_goBack;
	clearButton.callBack = &my_callBack_clear;
	nextLevelButton.callBack = &my_callBack_next;
	replayButton.callBack = &my_callBack_replay;
	hintButton.callBack = &my_callBack_hint;


	goBackButton.setPosition(300, 520);
	clearButton.setPosition(500, 520);
	buttonManager_game.addButton("goBack", std::make_shared<UserButton>(goBackButton));
	buttonManager_game.addButton("clear", std::make_shared<UserButton>(clearButton));

	nextLevelButton.setPosition(300,400);
	replayButton.setPosition(500,400);
	hintButton.setPosition(620,20);
    if(curr_hint_num < 5)
    {
        buttonManager_game.addButton("hint", std::make_shared<UserButton>(hintButton));
    }
	if(curr_level < LEVEL_NUMBER)
	{
		buttonManager_end.addButton("next_level",std::make_shared<UserButton> (nextLevelButton));
	}
	buttonManager_end.addButton("replay",std::make_shared<UserButton> (replayButton));

	Splitter::loadTexture();
	Mirror::loadTexture();
	LaserSource::loadTexture();
	Target::loadTexture();
	Photon::loadTexture();
	Pit::loadTexture();
	Wall::loadTexture();
	Bomb::loadTexture();
	Filter_Red::loadTexture();
	Filter_Blue::loadTexture();
	Capacitor::loadTexture();


	if(!mirror_money.loadFromFile("Equipments_Image/Mirror_money.png"))
	{
		std::cout << "Error: could not load money file!" << std::endl;
	}

	if(!splitter_money.loadFromFile("Equipments_Image/Splitter_money.png"))
	{
		std::cout << "Error: could not load money file!" << std::endl;
	}

	if(!filter_red_money.loadFromFile("Equipments_Image/Filter_money.png"))
	{
		std::cout << "Error: could not load money file!" << std::endl;
	}

	if(!filter_blue_money.loadFromFile("Equipments_Image/Filter_money.png"))
	{
		std::cout << "Error: could not load money file!" << std::endl;
	}
	changeIdx = 0;
	loadGrid();
	loadEquipment();
	allHit = 0;
	renderCount = 0;
	total_target = 0;
	curr_hit = 0;
	LevelManager * level_manager = LevelManager::getInstance();
	std::string levelKey = "";
	if(load_mode == 0)
	{
		char numStr[10] = {};
		itoa(curr_level, numStr, 10);
		std::string num = std::string(numStr);
		levelKey = "level";
		levelKey += num;
	}
	else
	{
		levelKey = "userlevel" + user_curr_level;
	}
	currentScore = level_manager->levelMap[levelKey].getInitialScore();
	if(!background.loadFromFile("Background/GameScreen.jpg"))
	{
		std::cout<< "load game screen background fail!"	<<std::endl;
	}
	backgroundSp.setTexture(background);

	if(!font.loadFromFile("Font/comic.ttf"))
	{
		std::cout << "Error: could not load font file!" << std::endl;
	}
	


}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	GameScreen::tool_manager.update(window);
	GameScreen::handleLaser();
	buttonManager_game.update(window);
	if(allHit == 1)
	{
		//std::cout<<"come into reset gamescreen"<<std::endl;
		renderCount++;
		//std::cout<<"come into reset gamescreen: "<<renderCount<<std::endl;
		if(renderCount == 1)
		{
			LevelManager *level_manager = LevelManager::getInstance();
			std::map<int, std::shared_ptr<Equipment>> :: iterator it = GameScreen::tool_manager.equipments_on_grid_move_.begin();
			//for(; it != GameScreen::tool_manager.equipments_on_grid_move_.end(); it++)
			//{
				//currentScore -= it->second->cost;
			//}
			level_manager->saveLevelInfo(curr_level-1, currentScore);
		}
		if(renderCount > 150)
		{
			buttonManager_end.update(window);
		}
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.draw(backgroundSp);
	buttonManager_game.render(window);
	drawGrid(window);
	drawEquitment(window);
	if( GameScreen::tool_manager.getState() == 1 || GameScreen::tool_manager.getState() == 2)
	{
		window.draw(*(GameScreen::tool_manager.getCopyEquipment()));
	}

	drawLaser(window);
	if(allHit == 1)
	{
		if(renderCount > 150)
			drawEnd(window);
	}
	
	drawScore(window);
	sf::CircleShape bulb(20);
	if(isHint == true )
	{
		if(lightPaths.size() != 0)
		{
			sf::Clock clock; // starts the clock
			sf::Time elapsed1 = clock.getElapsedTime();
			autoSolver(window);
			sf::Time elapsed2 = clock.getElapsedTime();
			std::cout << (elapsed2-elapsed1).asMilliseconds() << std::endl;
			clock.restart();
			//changeIdx = -1;
		}
	}
	if(checkPassLevel(result_paths))
	{
		bulb.setFillColor(sf::Color::Green);
	}
	else
	{
		bulb.setFillColor(sf::Color::Red);
	}
	bulb.setPosition(720, 20);
	if(isHint == true)
		window.draw(bulb);
	//showPath(window, result_paths);
	if(isHint == true )
    {
        if(hint_time == 0)
        {
            isHint = false;
        }
        else
        {
            if(hint_time%2 == 0)
            {
                drawHint(window);
            }
            hint_time--;
        }
    }
	
}
void GameScreen::drawHint(sf::RenderWindow& window)
{
    sf::Texture hintTexture;
    if(!hintTexture.loadFromFile("Images/hint_mark.png")) 
    {
        std::cout << "Error: could not load hint image!" << std::endl;
    }
    
    sf::Sprite hint_pic = sf::Sprite();
    hint_pic.setTexture(hintTexture);
    
    if(result_paths.size() > 0)
    {
        if(result_paths[0].size() > 1)
        {
            int row = result_paths[0][0].rowIdx;
            int col = result_paths[0][0].colIdx;
 
            hint_pic.setPosition(20 + col * 40, 20 + row*40);
            window.draw(hint_pic);
        } 
    }
}
void GameScreen::update(sf::Time delta)
{

}

void GameScreen::handleLaser()
{

	calculatePath();
}

void GameScreen::loadGrid()
{
	std::string* text;
	std::string level_name;
	if(load_mode == 0)
	{
		level_name = "Level/level_";

		char intStr[10] = {};
		itoa(curr_level, intStr,10);
		std::string str = std::string(intStr);

		level_name += str;
		level_name += ".txt";
	}

	if(load_mode == 1)
	{
		level_name = "UserLevel/" + user_curr_level;
		level_name += ".txt";

	}

	const char* txt_name = level_name.c_str();

	//std::cout<<txt_name<<std::endl;
	text = loadTXT(txt_name);
	GameScreen::myGrid.loadGrid(text,GameScreen::tool_manager.equipments_on_grid_, GameScreen::tool_manager.my_lasers_, GameScreen::tool_manager.my_targets_, GameScreen::tool_manager.my_capacitors_);
}


void GameScreen::drawGrid(sf::RenderWindow& window)
{
	std::vector<std::vector<sf::Sprite>> gridImage = myGrid.getSprites();
	for (int i = 0; i < GRID_HEIGHT; i++) 
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				window.draw(gridImage[i][j]);
			}
		}
}

void GameScreen::loadEquipment()
{
	std::string* text_equipment;
	std::string level_name; 
	if(load_mode == 0)
	{
		level_name	= "Level/level_equipment_";

		char intStr[10] = {};
		itoa(curr_level, intStr,10);
		std::string str = std::string(intStr);

		level_name += str;
		level_name += ".txt";
	}

	if(load_mode == 1)
	{
		level_name = "UserLevel/"+ user_curr_level;
		level_name += "_equipment.txt";

	}

	const char* txt_name = level_name.c_str();

	text_equipment = loadEquipmentTXT(txt_name);
	int i=0;

	while(!text_equipment[i].empty())
	{
		switch( text_equipment[i][0] )
		{
		    case MIRROR : 
				{

					if(tool_manager.equipments_.count("mirror")==0)
					{
						Mirror mirror;
						mirror.setPosition(675,100);
						tool_manager.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("mirror", std::make_shared<Mirror>(mirror)));
						tool_manager.equipments_.at("mirror")->setTexture(Mirror::mTexture);
						
						sf::Sprite mirror_sprite;
						mirror_sprite.setTexture(mirror_money);
						mirror_sprite.setPosition(700,80);
						equipments_money.push_back(mirror_sprite);
						i++;
					}
					break;
				}
			case SPLITTER :
				{

					if(tool_manager.equipments_.count("splitter")==0)
					{
						Splitter splitter;
						splitter.setPosition(675,200);
						tool_manager.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("splitter", std::make_shared<Splitter>(splitter)));
						tool_manager.equipments_.at("splitter")->setTexture(Splitter::sTexture);

						sf::Sprite splitter_sprite;
						splitter_sprite.setTexture(splitter_money);
						splitter_sprite.setPosition(700,180);
						equipments_money.push_back(splitter_sprite);
						i++;
					}
					break;
				}
			case FILTER_R : 
				{
					if(tool_manager.equipments_.count("filter_red")==0)
					{
						Filter_Red filter_red;
						filter_red.setPosition(675,300);
						tool_manager.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("filter_red", std::make_shared<Filter_Red>(filter_red)));
						tool_manager.equipments_.at("filter_red")->setTexture(Filter_Red::fTexture);
						
						sf::Sprite filter_red_sprite;
						filter_red_sprite.setTexture(filter_red_money);
						filter_red_sprite.setPosition(700,280);
						equipments_money.push_back(filter_red_sprite);
						i++;
					}
					break;
				}
			case FILTER_B : 
				{
					if(tool_manager.equipments_.count("filter_blue")==0)
					{
						Filter_Blue filter_blue;
						filter_blue.setPosition(675,400);
						tool_manager.equipments_.insert(std::pair<std::string, std::shared_ptr<Equipment>>("filter_blue", std::make_shared<Filter_Blue>(filter_blue)));
						tool_manager.equipments_.at("filter_blue")->setTexture(Filter_Blue::fTexture);
						
						sf::Sprite filter_blue_sprite;
						filter_blue_sprite.setTexture(filter_blue_money);
						filter_blue_sprite.setPosition(700,380);
						equipments_money.push_back(filter_blue_sprite);
						i++;
					}
					break;
				}
			default:
				break;
		}
	}
}

void GameScreen::drawEquitment(sf::RenderWindow& window)
{	
		std::map<std::string, std::shared_ptr<Equipment>>::iterator it = tool_manager.equipments_.begin();
		for(; it!= tool_manager.equipments_.end(); it++)
		{
			window.draw(*((*it).second));

		}

		for(int i =0; i<equipments_money.size(); i++)
		{
			//mirror_money.loadFromFile("Equipments_Image/Mirror_money");
			//equipments_money[i].setTexture(mirror_money);
			window.draw(equipments_money[i]);
		}

		std::map<int, std::shared_ptr<Equipment>>::iterator it_on_grid = tool_manager.equipments_on_grid_.begin();
		for(; it_on_grid!=tool_manager.equipments_on_grid_.end(); it_on_grid ++)
		{
			int x = (*it_on_grid).first/GRID_WIDTH;
			int y = (*it_on_grid).first - GRID_WIDTH*x;
			((*it_on_grid).second)->setPosition((float)(2*MARGIN+y*(BLOCK_SIZE)), (float)(2*MARGIN+x*(BLOCK_SIZE)));
			window.draw(*((*it_on_grid).second));
		}
}

std::string* loadEquipmentTXT(const char* fileName)
{
	std::string* text;
	text = new std::string[10];
	std::ifstream myfile(fileName);
	int lineNum = 0;
	while(std::getline(myfile, text[lineNum]))
	{
		lineNum++;
	}
	return text;
}

void GameScreen::calculatePath()
{ 
	lightPaths.clear();
	for(int i = 0; i != GameScreen::tool_manager.my_targets_.size(); i++)
	{
		GameScreen::tool_manager.my_targets_[i]->lightOff();
	}
	for(int i = 0; i != GameScreen::tool_manager.my_capacitors_.size(); i++)
	{
		GameScreen::tool_manager.my_capacitors_[i]->lightOff();
	}
	sf::FloatRect windowRect(MARGIN, MARGIN, GRID_WIDTH*(BLOCK_SIZE), GRID_HEIGHT*(BLOCK_SIZE));
	if(lightPaths.size() == 0)
	{
		for(int i = 0; i != tool_manager.my_lasers_.size(); i++)
		{
			std::vector<Photon> lightPath;
			lightPath.push_back(tool_manager.my_lasers_[i].getPhoton());
			lightPaths.push_back(lightPath);
		}
		for(int i = 0; i != capLightPaths.size(); i++)
		{
			lightPaths.push_back(capLightPaths[i]);
		}
	}
	for(int i = 0; i != lightPaths.size(); i++)
	{
		Photon current = lightPaths[i].back();
		while(current.getVelocity() != 0.0 && windowRect.contains(current.getPosition()))
		{
			Photon nextPhoton = current;
			int idx = nextPhoton.getIndex();
			if(tool_manager.equipments_on_grid_.count(idx) > 0)
			{	
				if(tool_manager.equipments_on_grid_[idx]->label == BOMB)
				{
					int row = idx/GRID_WIDTH;
					int col = idx%GRID_WIDTH;
					if(row > 0)
					{
						if(tool_manager.equipments_on_grid_.count(idx-GRID_WIDTH) > 0)
						{
							char lab = tool_manager.equipments_on_grid_[idx-GRID_WIDTH]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager.equipments_on_grid_.erase(idx-GRID_WIDTH);
						}
					}
					if(row < GRID_HEIGHT-1)
					{
						if(tool_manager.equipments_on_grid_.count(idx+GRID_WIDTH) > 0)
						{
							char lab = tool_manager.equipments_on_grid_[idx+GRID_WIDTH]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager.equipments_on_grid_.erase(idx+GRID_WIDTH);
						}
					}
					if(col > 0)
					{
						if(tool_manager.equipments_on_grid_.count(idx-1) > 0)
						{
							char lab = tool_manager.equipments_on_grid_[idx-1]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager.equipments_on_grid_.erase(idx-1);
						}
					}
					if(col < GRID_WIDTH-1)
					{
						if(tool_manager.equipments_on_grid_.count(idx+1) > 0)
						{
							char lab = tool_manager.equipments_on_grid_[idx+1]->label;
							if(lab != LASER_SOURCE_U_RED && lab != LASER_SOURCE_U_BLUE && lab != DOOR_U_RED && lab != DOOR_U_BLUE)
								tool_manager.equipments_on_grid_.erase(idx+1);
						}
					}
					tool_manager.equipments_on_grid_.erase(idx);
					nextPhoton.myMove();
				}
				else
				{
					tool_manager.equipments_on_grid_[idx]->reaction(nextPhoton, lightPaths);
				}
				lightPaths[i].push_back(nextPhoton);

			}
			else
			{
				nextPhoton.myMove();
				lightPaths[i].push_back(nextPhoton);
			}
			current = nextPhoton;
		}
	}
	
	for(int i = 0; i != lightPaths.size(); i++)
	{
		Photon tail = lightPaths[i].back();
		int tailIdx = tail.getIndex();
		if(tool_manager.equipments_on_grid_.count(tailIdx) > 0)
		{
			tool_manager.equipments_on_grid_[tailIdx]->reaction(tail, lightPaths);
		}
	}
	for(int i = 0; i != GameScreen::tool_manager.my_capacitors_.size(); i++)
	{
		if(!GameScreen::tool_manager.my_capacitors_[i]->isHit() && (GameScreen::tool_manager.my_capacitors_[i]->curState())/10 == 2)
		{
			int colorNum = (GameScreen::tool_manager.my_capacitors_[i]->curState())%10;
			sf::Color color;
			if(colorNum == 1)
			{
				color =  sf::Color::Red;
			}
			else
			{
				color = sf::Color::Blue;
			}
			float angle = tool_manager.my_capacitors_[i]->getRotation();
			if(angle > 0)
			{
				angle = 360 - angle;
			}
			int direction = (int)(angle/45)+1;
			Photon newPhoton(direction, color);
			float deltaX = 0;
			float deltaY = 0;
			if(direction == 1 || direction == 5)
			{
				deltaX = (float)(BLOCK_SIZE*(3-direction)/4);
			}
			else if(direction == 3 || direction == 7)
			{
				deltaY = (float)(BLOCK_SIZE*(direction-5)/4);
			}
			sf::Vector2f delta(deltaX, deltaY);
			newPhoton.setPosition(GameScreen::tool_manager.my_capacitors_[i]->getPosition() + delta);
			std::vector<Photon> lightPath;
			lightPath.push_back(newPhoton);
			capLightPaths.push_back(lightPath);
			//GameScreen::tool_manager.my_capacitors_[i]->curState();
		}
	}
	bool isAllHit = true;
	for(int i = 0; i != GameScreen::tool_manager.my_targets_.size(); i++)
	{
		if(!GameScreen::tool_manager.my_targets_[i]->isHit())
		{
			isAllHit = false;
			break;
		}
	}
	if(isAllHit)
	{
		//std::cout<<"come into isAllHit"<<std::endl;
		allHit = 1;
		//curr_level ++;
	}
}

void GameScreen::drawLaser(sf::RenderWindow& window)
{
	for(int i = 0; i != lightPaths.size(); i++)
	{
		for(int j = 0; j != lightPaths[i].size(); j++)
		{
			window.draw(lightPaths[i][j]);
		}
	}
}

void GameScreen::drawEnd(sf::RenderWindow& window)	
{
	//:nextLevelButton("Images/next_level_button.png"), replayButton("Images/replay_button.png")
    //sf::Texture zero_star;
	//sf::Texture one_star;
	//sf::Texture two_star;
	//sf::Texture three_star;
	transparent_background.loadFromFile("Background/transparent_background.png");
	sf::Sprite trans_back;
	trans_back.setTexture(transparent_background);
	sf::Color color(255,255,255,210);
	trans_back.setColor(color);
	window.draw(trans_back);
	congratulation.loadFromFile("Background/congratulation.png");
	sf::Sprite cong;
	cong.setTexture(congratulation);
	cong.setPosition(200,50);
	window.draw(cong);
	buttonManager_end.render(window);

}

void GameScreen::drawScore(sf::RenderWindow& window)
{
	sf::Text score_text;
	score_text.setFont(font);
	std::string score_string = "Money:";
	
	char numStr[10] = {};
	itoa(currentScore, numStr, 10);
	std::string num = std::string(numStr);

	score_string += num;

	score_text.setString(score_string);
	score_text.setStyle(sf::Text::Bold);
	score_text.setCharacterSize(24);
	score_text.setPosition(650,350);
	window.draw(score_text);
}

void GameScreen::autoSolver(sf::RenderWindow& window)
{
	// clear path, initialization
	for(int i = 0; i < result_paths.size(); i++)
	{
		result_paths[i].clear();
	}
	result_paths.clear();
	curr_hit = 0;
	std::vector<std::vector<MyNode>> nodeGrid;
	bool visited[12][15] = {false};
	std::queue<MyNode> myQueue;
	std::vector<std::vector<Photon>> autoLights;
	initialize(nodeGrid, myQueue, visited);

	// main loop for BFS
loop: while(!myQueue.empty())
	{
		MyNode curr = (myQueue.front());
		myQueue.pop();
		visited[curr.rowIdx][curr.colIdx] = true;
		autoLights.clear();
		int parentDir = curr.currDirection;
		int parentRow = curr.rowIdx;
		int parentCol = curr.colIdx;
		MyNode * parentNode = new MyNode(nodeGrid[parentRow][parentCol]);
		float posY = 40 * parentRow + 40;
		float posX = 40 * parentCol + 40;
		LaserSource laser_1('r');
		laser_1.setPosition(posX, posY);
		LaserSource laser_2('r');
		laser_2.setPosition(posX, posY);
		switch(parentDir)
		{
		case 0:
			{
				laser_1.setRotation(90);
				laser_2.setRotation(270);
				break;
			}
		case 1:
			{
				laser_1.setRotation(0);
				laser_2.setRotation(180);
				break;
			}
		case 2:
			{
				laser_1.setRotation(90);
				laser_2.setRotation(270);
				break;
			}
		case 3:
			{
				laser_1.setRotation(0);
				laser_2.setRotation(180);
				break;
			}
		}
		Photon initPhoton_1 = laser_1.getPhoton();
		std::vector<Photon> lightPath_1;
		lightPath_1.push_back(initPhoton_1);
		autoLights.push_back(lightPath_1);

		Photon initPhoton_2 = laser_2.getPhoton();
		std::vector<Photon> lightPath_2;
		lightPath_2.push_back(initPhoton_2);
		autoLights.push_back(lightPath_2);

		sf::FloatRect windowRect(MARGIN, MARGIN, GRID_WIDTH*(BLOCK_SIZE), GRID_HEIGHT*(BLOCK_SIZE));
		for(int i = 0; i != autoLights.size(); i++)
		{
			Photon current = autoLights[i].back();
			while(current.getVelocity() != 0.0 && windowRect.contains(current.getPosition()))
			{
				Photon nextPhoton = current;
				int row = 0, col = 0;
				nextPhoton.getIndex2(row, col);
				if(row > 11 || col > 14 || row < 0 || col < 0)
				{
					current = nextPhoton;
					continue;
				}
				int idx = row * 15 + col;
				if(!visited[row][col] && (tool_manager.equipments_on_grid_.count(idx) == 0 || tool_manager.equipments_on_grid_[idx]->label == DOOR_U_RED))
				{
					if(row > 11 || col > 14 || row < 0 || col < 0)
					{
						std::cout << "out of bound!!" << std::endl;
					}
					nodeGrid[row][col].parent = parentNode;
					nodeGrid[row][col].currDirection = nextPhoton.getDirection()/2;
					int prevLevel = 0;
					switch(parentNode->currDirection)
					{
					case 0:
						{
							prevLevel = parentNode->right;
							break;
						}
					case 1:
						{
							prevLevel = parentNode->up;
							break;
						}
					case 2:
						{
							prevLevel = parentNode->left;
							break;
						}
					case 3:
						{
							prevLevel = parentNode->down;
							break;
						}
					}

					switch(nodeGrid[row][col].currDirection)
					{
					case 0:
						{
							nodeGrid[row][col].right = prevLevel+1;
							break;
						}
					case 1:
						{
							nodeGrid[row][col].up = prevLevel+1;
							break;
						}
					case 2:
						{
							nodeGrid[row][col].left = prevLevel+1;
							break;
						}
					case 3:
						{
							nodeGrid[row][col].down = prevLevel+1;
							break;
						}
					}
					myQueue.push(nodeGrid[row][col]);
					visited[row][col] = true;
				}
				if(tool_manager.equipments_on_grid_.count(idx) > 0)
				{	
					tool_manager.equipments_on_grid_[idx]->reaction(nextPhoton, autoLights);
					autoLights[i].push_back(nextPhoton);
				}
				else
				{
					nextPhoton.myMove();
					int row_1 = 0, col_1 = 0;
					nextPhoton.getIndex2(row_1, col_1);
					if(row > 11 || col > 14 || row < 0 || col < 0)
					{
						current = nextPhoton;
						continue;
					}
					autoLights[i].push_back(nextPhoton);
				}
				current = nextPhoton;
			}
		}
		for(int i = 0; i < autoLights.size(); i++)
		{
			int row = 0, col =0;
			autoLights[i].back().getIndex2(row, col);
			if(row < 0 || row > 11 || col < 0 || col > 14)
			{
				continue;
			}
			int idx = row * 15 + col;
			if(tool_manager.equipments_on_grid_.count(idx)>0 && tool_manager.equipments_on_grid_[idx]->label == DOOR_U_RED)
			{
				if(nodeGrid[idx/15][idx%15].hit == 0)
				{
					nodeGrid[idx/15][idx%15].hit = 1;
					curr_hit ++;
					storePath(&nodeGrid[idx/15][idx%15], result_paths);
					if(curr_hit == total_target)
					{
						return;
					}
				}
			}
		}
	}
}


void GameScreen::initialize(std::vector<std::vector<MyNode>> &nodeGrid, std::queue<MyNode> &myQueue, bool visited[12][15])
{
	total_target = tool_manager.my_targets_.size();
	for(int i = 0; i != 12; i++)
	{
		std::vector<MyNode> rowNode;
		for(int j = 0; j != 15; j++)
		{	
			MyNode curr;
			curr.rowIdx = i;
			curr.colIdx = j;
			rowNode.push_back(curr);
		}
		nodeGrid.push_back(rowNode);
	}
	for(int i = 0; i != lightPaths.size(); i++)
	{
		Photon endPhoton = lightPaths[i].back();
		int row = 0, col = 0;
		endPhoton.getIndex2(row ,col);
		int idx = row*15+col;
		if(tool_manager.equipments_on_grid_.find(idx) != tool_manager.equipments_on_grid_.end())
		{
			if(tool_manager.equipments_on_grid_[idx]->label == DOOR_U_RED)
			{
				curr_hit++;
				nodeGrid[idx/15][idx%15].hit = 1;
			}
		}
		for(int j = 0; j != lightPaths[i].size()-1; j++)
		{
			Photon currPhoton = lightPaths[i][j];
			int row = 0, col = 0;
			currPhoton.getIndex2(row, col);
			if(row < 0 || row > 11 || col < 0 || col > 14)
			{
				continue;
			}
			int dir = currPhoton.getDirection()/2;
			nodeGrid[row][col].currDirection = dir;
			switch(dir)
			{
			case 0:
				{
					nodeGrid[row][col].right = 0;
					break;
				}
			case 1:
				{
					nodeGrid[row][col].up = 0;
					break;
				}
			case 2:
				{
					nodeGrid[row][col].left = 0;
					break;
				}
			case 3:
				{
					nodeGrid[row][col].down = 0;
					break;
				}
			default:
				{
					std::cout << "Initial Photons direction Error!" << std::endl;
					break;
				}
			}
			if(tool_manager.equipments_on_grid_.count(row*15+col) == 0)
			{
				myQueue.push(nodeGrid[row][col]);
				visited[row][col] = 1;
			}
		}
	}
}

void GameScreen::storePath(MyNode* end, std::vector<std::vector<MyNode>> &paths)
{
	std::vector<MyNode> path;
	path.insert(path.begin(), *end);

	while(end->parent != NULL)
	{
		path.insert(path.begin(), *(end->parent));
		end = end->parent;
	}
	paths.push_back(path);
}

void GameScreen::showPath(sf::RenderWindow& window,  std::vector<std::vector<MyNode>> paths)
{
	//std::vector<MyNode> path = paths[0];
	for(int j = 0; j<paths.size(); j++)
	{
		std::vector<MyNode> path = paths[j];
		for(int i=0; i<path.size(); i++)
		{
			sf::CircleShape bulb(20);
			bulb.setFillColor(sf::Color::Black);
			bulb.setPosition(20 + path[i].colIdx * 40, 20 + path[i].rowIdx * 40);
			window.draw(bulb);
		}
	}
}

bool GameScreen::checkPassLevel( std::vector<std::vector<MyNode>> paths)
{
	if(total_target > curr_hit)
        return false;
	std::unordered_set<int> mySet;
	int targetNum = paths.size();
	for(int i = 0; i!=paths.size(); i++)
	{
		std::vector<MyNode> path = paths[i];
		for(int j = 0; j != path.size()-1; j++)
		{
			mySet.insert(path[j].rowIdx * 15 + path[j].colIdx);
		}
	}
	int nodeNum = mySet.size();
	int money = 20 * (targetNum-1) + 10 * (nodeNum - (targetNum - 1));
	return money <= currentScore;
}