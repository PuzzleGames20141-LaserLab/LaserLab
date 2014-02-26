#include <SFML/Graphics.hpp>

#include<memory>
#include<iostream> 

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "UserButton.h"
#include "LevelSelectScreen.h"

void my_callBack_play()
{
	Game::Screen = std::make_shared<GameScreen>();
}

void my_callBack_quit()
{
	//Game::Screen = std::make_shared<EndScreen>();
}

void my_callBack_levelSelect()
{
	Game::Screen = std::make_shared<LevelSelectScreen>();
}

MenuScreen::MenuScreen()
	:playButton("Images/play.png"), quitButton("Images/quit.png"), levelSelectButton("Images/level_select.png")
{
	playButton.callBack = &my_callBack_play;
	//quitButton.callBack = &my_callBack_quit;
	levelSelectButton.callBack = &my_callBack_levelSelect;
	
	playButton.setPosition(float(Game::Width/2 - playButton.getSize().x * 2),float(Game::Height/2 - playButton.getSize().y/2));
	quitButton.setPosition(float(Game::Width/2 - quitButton.getSize().x/4),  float(Game::Height/2 - playButton.getSize().y/2));
	levelSelectButton.setPosition(float(Game::Width - quitButton.getSize().x*2),  float(Game::Height/2 - playButton.getSize().y/2));
	
	buttonManager.addButton("play",std::make_shared<UserButton>(playButton));
	buttonManager.addButton("quit",std::make_shared<UserButton>(quitButton));
	buttonManager.addButton("level_select",std::make_shared<UserButton>(levelSelectButton));
	
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