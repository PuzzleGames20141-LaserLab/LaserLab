#include <SFML/Graphics.hpp>

#include<memory>
#include<iostream>
#include<map>
#include "Game.h"
#include "LevelSelectScreen.h"
#include "GameScreen.h"
#include "UserButton.h"
#include "LevelManager.h"
#include "LevelInfo.h"

void my_callBack_playlevel()
{
	Game::Screen = std::make_shared<GameScreen>();
}

LevelSelectScreen::LevelSelectScreen()
{
	
	if(!backTexture.loadFromFile("Background/background.png")) 
	{
		std::cout << "Error: could not load grid image!" << std::endl;
	}

	if(!zero_star.loadFromFile("LevelScreen/zero_star.png")) 
	{
		std::cout << "Error: could not load zero_star image!" << std::endl;
	}

	if(!one_star.loadFromFile("LevelScreen/one_star.png")) 
	{
		std::cout << "Error: could not load one_star image!" << std::endl;
	}

	if(!two_star.loadFromFile("LevelScreen/two_star.png")) 
	{
		std::cout << "Error: could not load two star image!" << std::endl;
	}

	if(!three_star.loadFromFile("LevelScreen/three_star.png")) 
	{
		std::cout << "Error: could not load three star image!" << std::endl;
	}
	
	if(!lock.loadFromFile("LevelScreen/lock.png")) 
	{
		std::cout << "Error: could not load lock image!" << std::endl;
	}

	LevelManager *level = LevelManager::getInstance();
	std::map<std::string, LevelInfo> curr_info = level->levelMap;
	std::map<std::string, LevelInfo>::iterator it = curr_info.begin();
	int num = 0;
	for(; it!=curr_info.end(); it++)
	{
		int y = num / 7;
		int x = num - 7*y;
		x = 60 + 100 * x;
		y = 60 + 100 * y;

		if((*it).second.getStarNum() != -1)
		{
			std::string level_name = "LevelScreen/" + (*it).first;
			
			level_name += "_button.png";
			UserButton new_button(level_name);
			sf::Sprite new_star;
			if((*it).second.getStarNum() == 0)
			{
				new_star.setTexture(zero_star);
			}

			else if((*it).second.getStarNum() == 1)
			{
				new_star.setTexture(one_star);
			}

			else if((*it).second.getStarNum() == 2)
			{
				new_star.setTexture(two_star);
			}

			else if((*it).second.getStarNum() == 3)
			{
				new_star.setTexture(three_star);
			}
			new_star.setPosition((float)x, (float)y);
			level_stars.push_back(new_star);

			new_button.setPosition((float)x, (float)y);
			new_button.callBack = &my_callBack_playlevel;
			buttonManager_level.addButton((*it).first, std::make_shared<UserButton>(new_button));
			int u = 0;

			

		}

		else
		{
			sf::Sprite lock_level;
			lock_level.setTexture(lock);
			lock_level.setPosition((float)x, (float)y);
			level_lock.push_back(lock_level);

		}
		num ++;
	}


}


void LevelSelectScreen::handleInput(sf::RenderWindow& window)
{
	buttonManager_level.update(window);
}

void LevelSelectScreen::render(sf::RenderWindow& window)
{
	
	sf::Sprite backSprite;
	backSprite.setTexture(backTexture);
	window.draw(backSprite);
	buttonManager_level.render(window);
	drawLevelStar(window);
	drawLevelLock(window);
}

void LevelSelectScreen::update(sf::Time delta)
{
	
}

void LevelSelectScreen::drawLevelStar(sf::RenderWindow& window)
{
	for(int i=0; i!=level_stars.size(); i++)
	{
		window.draw(level_stars[i]);
	}

}

void LevelSelectScreen::drawLevelLock(sf::RenderWindow& window)
{
	for(int i=0; i!=level_lock.size(); i++)
	{
		window.draw(level_lock[i]);
	}
}