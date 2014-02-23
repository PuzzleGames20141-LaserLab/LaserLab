#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <iostream>

#include "Game.h"
#include "GameScreen.h"
#include "MenuScreen.h"

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
	:window(sf::VideoMode(Game::Width, Game::Height),"Laser Game")
{

}

void Game::handleInput()
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			window.close();
	}

	Game::Screen->handleInput(window);
}

void Game::render()
{
	window.clear();
	Game::Screen->render(window);
	window.display();

}

void Game::run()
{

	while(window.isOpen())
	{
		handleInput();
		//updata();

	    render();
	}
}

