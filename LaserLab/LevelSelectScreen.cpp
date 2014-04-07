#include <SFML/Graphics.hpp>

#include<memory>
#include<iostream>
#include<map>

#include "Game.h"
#include "LevelSelectScreen.h"
#include "GameScreen.h"
#include "UserButton.h"
#include "LevelInfo.h"
#include "MenuScreen.h"
#include "LevelManager.h"

void my_callBack_playlevel()
{
	Game::Screen = std::make_shared<GameScreen>();
}

void my_callBack_goBackMenu()
{
	Game::Screen = std::make_shared<MenuScreen>();
}

LevelSelectScreen::LevelSelectScreen()
	:goBackButton("Images/go_back.png")
{
	
	goBackButton.callBack = &my_callBack_goBackMenu;

	goBackButton.setPosition(700, 500);
	buttonManager_level.addButton("go_back", std::make_shared<UserButton>(goBackButton));
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
	if(!font.loadFromFile("Font/comic.ttf"))
	{
		std::cout << "Error: could not load font file!" << std::endl;
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
			std::string level_name;
			if(load_mode == 0)
			{
				level_name = "LevelScreen/" + (*it).first;
			
				level_name += "_button.png";
			}

			if(load_mode == 1)
			{
				level_name = "LevelScreen/user_level_button.png";
			}

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
			if(load_mode == 1)
			{
				sf::Text sfLevelName;
				sfLevelName.setFont(font);
				sfLevelName.setString((*it).first.substr(9));
				sfLevelName.setStyle(sf::Text::Bold);
				//sfLevelName.setCharacterSize(22);
				int strLen = (*it).first.substr(9).size();
				int size = (22-(strLen-5)*2);
				sfLevelName.setCharacterSize(size);
				/*
				while(bound.width > 70)
				{
					size--;
					sfLevelName.setCharacterSize(size);
					bound = sfLevelName.getLocalBounds();
				}
				*/
				sf::FloatRect bound = sfLevelName.getLocalBounds();
				sfLevelName.setColor(sf::Color::Magenta);
				double leftMargin = 40 - bound.width/2;
				double upMargin = 40 - bound.height/2;
				sfLevelName.setPosition((float)(x+leftMargin), (float)(y + upMargin + 5));
				textMap.insert(std::pair<std::string, sf::Text>((*it).first, sfLevelName));
			}

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
	drawLevelName(window);
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

void LevelSelectScreen::drawLevelName(sf::RenderWindow& window)
{
	std::map<std::string, sf::Text> :: iterator it = textMap.begin();
	for(; it != textMap.end(); it++)
	{
		window.draw(it->second);
	}
}