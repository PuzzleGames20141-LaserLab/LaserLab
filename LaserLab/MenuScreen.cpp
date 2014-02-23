#include <SFML/Graphics.hpp>

#include<memory>
#include<iostream> 

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "UserButton.h"


void my_callBack_play()
{
	Game::Screen = std::make_shared<GameScreen>();
}

//void my_callBack_quit()
//{
//	Game::Screen = std::make_shared<EndScreen>();
//}

MenuScreen::MenuScreen()
	:playButton("Images/play.png"), quitButton("Images/quit.png")
{
	playButton.callBack = &my_callBack_play;
	//quitButton.callBack = &void my_callBack_quit;

	playButton.setPosition(Game::Width/2 - playButton.getSize().x * 2,Game::Height/2 - playButton.getSize().y/2);

	quitButton.setPosition(Game::Width/2 - quitButton.getSize().x/4,  Game::Height/2 - playButton.getSize().y/2);
	buttonManager.addButton("play",std::make_shared<UserButton>(playButton));
	buttonManager.addButton("quit",std::make_shared<UserButton>(quitButton));

	if(!backTexture.loadFromFile("Background/Capture.PNG")) 
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