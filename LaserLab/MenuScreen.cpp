#include <SFML/Graphics.hpp>

#include<memory>
#include<iostream> 

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "UserButton.h"
#include "LevelSelectScreen.h"
#include "EditScreen.h"

int load_mode = 0;

void my_callBack_play()
{
	load_mode = 0;
	Game::Screen = std::make_shared<GameScreen>();
}

void my_callBack_quit()
{
	load_mode = 1;
	Game::Screen = std::make_shared<LevelSelectScreen>();
}

void my_callBack_edit()
{
	Game::Screen = std::make_shared<EditScreen>();
}

void my_callBack_levelSelect()
{
	load_mode = 0;
	Game::Screen = std::make_shared<LevelSelectScreen>();
}

MenuScreen::MenuScreen()
	:playButton("Images/play.png"), quitButton("Images/quit.png"), levelSelectButton("Images/level_select.png"),levelEditButton("Images/level_edit.png")
{
	playButton.callBack = &my_callBack_play;
	quitButton.callBack = &my_callBack_quit;
	levelSelectButton.callBack = &my_callBack_levelSelect;
	levelEditButton.callBack = &my_callBack_edit;
	playButton.setPosition(200,300);
	quitButton.setPosition(350, 300);
	levelSelectButton.setPosition(500,300);
	levelEditButton.setPosition(650, 300);
	buttonManager.addButton("play",std::make_shared<UserButton>(playButton));
	buttonManager.addButton("quit",std::make_shared<UserButton>(quitButton));
	buttonManager.addButton("level_select",std::make_shared<UserButton>(levelSelectButton));
	buttonManager.addButton("level_edit", std::make_shared<UserButton>(levelEditButton));
	
	if(!backTexture.loadFromFile("Background/background.png")) 
	{
		std::cout << "Error: could not load grid image!" << std::endl;
	}

}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	buttonManager.update(window);
}

void MenuScreen::render(sf::RenderWindow& window)
{
	
	sf::Sprite backSprite;
	backSprite.setTexture(backTexture);

	window.draw(backSprite);
	buttonManager.render(window);
}

void MenuScreen::update(sf::Time delta)
{
	
}