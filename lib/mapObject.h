#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
class Map
{
public:
	Map()
	{
		
		background_image.loadFromFile("Data/background1.jpg");
		background.setSize(sf::Vector2f(1000, 600));
		background.setPosition(0, 0);
		background.setTexture(&background_image);
		border_image.loadFromFile("Data/border3.png");
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (gameMap[i][j] == 1)
				{
					sf::RectangleShape temp;
					temp.setSize(sf::Vector2f(50, 50));
					int x = i * 50;
					int y = j * 50;
					temp.setPosition(x, y);
					temp.setTexture(&border_image);
					temp.setFillColor(sf::Color::Red);
					border.push_back(temp);
				}
			}
		}

	}
	vector<sf::RectangleShape> getBorder()
	{
		return border;
	}
	void drawMap(sf::RenderWindow& windows)
	{
		windows.draw(background);
		for (int i = 0; i < border.size(); i++)
		{
			windows.draw(border[i]);
		}
	}
	~Map()
	{}
	static int gameMap[20][12];
private:
	sf::Texture background_image;
	sf::RectangleShape background;
	vector<sf::RectangleShape> border;
	sf::Texture border_image;
	
};

int Map::gameMap[20][12] = { {1,1,1,1,1,1,1,1,1,1,1,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,1,0,0,0,0,0,1 },
					{1,0,0,0,0,1,0,0,0,0,0,1 },
					{1,0,0,0,0,1,0,0,0,0,0,1 },
					{1,0,0,0,0,1,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,1,0,0,0,1 },
					{1,0,0,0,0,0,0,1,1,1,1,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,1,1,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,0,0,0,0,0,0,0,0,0,0,1 },
					{1,1,1,1,1,1,1,1,1,1,1,1 } };

#endif // !MAP_OBJECT_H
