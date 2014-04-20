#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <string>
#include <iostream>
#include <windows.h>

#include "Game.h"
#include "GameScreen.h"
#include "MenuScreen.h"

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
	:window(sf::VideoMode(Game::Width, Game::Height),"Laser Game")
{
	sf::Vector2i pos(450,50);
	window.setPosition(pos);
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
	    render();        
		if(hint_time > 0)
        {
            Sleep(500);
        }
	}
}

