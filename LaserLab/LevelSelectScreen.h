#ifndef LEVELSELECTSCREEN_H
#define LEVELSELECTSCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "UserButton.h"
#include "ButtonManager.h"

class LevelSelectScreen : public Screen
{
public:
	LevelSelectScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	ButtonManager buttonManager_level;
	//std::vector<UserButton> level_buttons;
	sf::Texture backTexture;
	std::vector<sf::Sprite> level_stars;
	std::vector<sf::Sprite> level_lock;
	sf::Texture zero_star;
	sf::Texture one_star;
	sf::Texture two_star;
	sf::Texture three_star;
	sf::Texture lock;
	sf::Font font;
	UserButton goBackButton;
	std::map<std::string, sf::Text> textMap;

	void drawLevelStar(sf::RenderWindow& window);
	void drawLevelLock(sf::RenderWindow& window);
	void drawLevelName(sf::RenderWindow& window);

};

#endif