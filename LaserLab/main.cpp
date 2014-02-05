#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Laser Lab");
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	bool running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		window.display();
	}
}