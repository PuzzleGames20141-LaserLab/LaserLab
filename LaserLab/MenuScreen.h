#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "UserButton.h"
#include "ButtonManager.h"

extern int load_mode;

class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	ButtonManager buttonManager;
	UserButton playButton;
	UserButton quitButton;
	UserButton levelSelectButton;
	UserButton levelEditButton;
	sf::Texture backTexture;

};

#endif