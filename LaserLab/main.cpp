#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <iostream>
#include <string>
#include "Macro.h"
#include "Grid.h"
#include <vector>
#include "Photon.h"
#include "Mirror.h"
#include "Target.h"
#include "LaserSource.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Laser Lab");
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	//window.setActive(true);	
	sf::FloatRect windowRect(MARGIN, MARGIN, GRID_WIDTH*(BLOCK_SIZE), GRID_HEIGHT*(BLOCK_SIZE));

	Grid myGrid;
	std::string* text;
	text = loadTXT("level_1.txt");
	myGrid.loadGrid(text);
	std::vector<std::vector<sf::Sprite>> gridImage = myGrid.getSprites();

	Mirror myMirror;
	myMirror.setPosition(240, 80);
	myMirror.setRotation(135);
	Mirror myNewMirror = myMirror;
	myNewMirror.setPosition(320, 80);
	myNewMirror.setRotation(135);
	LaserSource myLaser;
	myLaser.setPosition(80,80);
	myLaser.setRotation(0);
	Target myTarget;
	myTarget.setPosition(240, 400);
	myTarget.setRotation(90);
	std::vector<Equipment *> myVec;
	myVec.push_back(&myMirror);
	myVec.push_back(&myNewMirror);
	myVec.push_back(&myTarget);
	myVec.push_back(&myLaser);
	std::vector<Photon> myPhotonVec;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		for (int i = 0; i < GRID_HEIGHT; i++) 
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				window.draw(gridImage[i][j]);
			}
		}
		for(int i = 0; i < myVec.size(); i++)
		{
			window.draw(*(myVec[i]));
		}
		myPhotonVec.clear();
		myPhotonVec.push_back(myLaser.getPhoton(2));
		while(myPhotonVec.size() > 0)
		{
			Photon myPhoton = myPhotonVec.back();
			myPhoton.setVelocity(1);
			myPhotonVec.pop_back();
			window.draw(myPhoton);
			while(true) {
				myPhoton.move();
				for(int i = 0; i < myVec.size(); i++) {
					//std::cout<<myPhoton.getPosition().x<<"," <<myPhoton.getPosition().y<<std::endl;
					if(myPhoton.getPosition() == myVec[i]->getPosition()) {
						myVec[i]->reaction(myPhoton);
						break;
					}
				}
				if(myPhoton.getVelocity() == 0.0 || !windowRect.contains(myPhoton.getPosition()))
				{
					break;
				}
				window.draw(myPhoton);
			}
		}
		window.display();
	}
}