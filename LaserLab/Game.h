#include <memory>
#include "Screen.h"

class Game
{
public:
	Game();

	void run();
	void handleInput();
	void render();
	
	static const int Width = 800;
	static const int Height = 600;
	
	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window;

};

