#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
using namespace sf;
using std::cout;
using std::endl;
using std::string;

void moveMario(const string& direction, const RenderWindow& window, Sprite& mario);

int main()
{
	RenderWindow window(VideoMode(1024, 768), "SFML Sprite Move Demo", sf::Style::Close);
	Event event;

	// Render window background
	sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("C:/temp/zion_meadow.png"));
	background.setTexture(&backgroundTexture);

	// Create sprite (Mario)
	sf::Texture marioTexture;
	marioTexture.loadFromFile("C:/temp/mario.jpg");

	sf::Sprite marioSprite(marioTexture);
	marioSprite.setScale(0.333f, 0.333f);
	marioSprite.setPosition(1024.0f / 2, 768.0f / 2);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveMario("up", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveMario("down", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveMario("left", window, marioSprite);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveMario("right", window, marioSprite);
				else;
			default:
				;
			}
		}

		window.clear();
		window.draw(background);
		window.draw(marioSprite);
		window.display();
	}
}

void moveMario(const string& direction, const RenderWindow& window, Sprite& mario)
{
	// delta is 1% of render window size
	sf::Vector2f delta = sf::Vector2f(window.getSize().x / 100.f, window.getSize().y / 100.f);
	sf::Vector2f position = mario.getPosition();
	if (direction == "up") mario.setPosition(position.x, position.y - delta.y);
	if (direction == "down") mario.setPosition(position.x, position.y + delta.y);
	if (direction == "left") mario.setPosition(position.x - delta.x, position.y);
	if (direction == "right") mario.setPosition(position.x + delta.x, position.y);
}