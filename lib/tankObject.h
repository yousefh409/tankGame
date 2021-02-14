#ifndef TANK_OBJECT_H
#define TANK_OBJECT_H

#include "utilObject.h"
using namespace std;

class Tank
{
public:
	Tank()
	{
		tank_image.loadFromFile("Data/HuntingTank2.png");
		tank.setSize(sf::Vector2f(50, 50));
		tank.setTexture(&tank_image);
		tank.setPosition(900, 200);
		tank.setOrigin(25, 25);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(tank);
	}
	void move(sf::Event& event)
	{
		xVelocity = 0;
		yVelocity = 0;
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left) leftButton = true;
			if (event.key.code == sf::Keyboard::Right) rightButton = true;
			if (event.key.code == sf::Keyboard::Up) upButton = true;
			if (event.key.code == sf::Keyboard::Down) downButton = true;
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Left) leftButton = false;
			if (event.key.code == sf::Keyboard::Right) rightButton = false;
			if (event.key.code == sf::Keyboard::Up) upButton = false;
			if (event.key.code == sf::Keyboard::Down) downButton = false;
		}
		if (rightButton == true)
		{
			xVelocity = 5;
			tank.setRotation(90);
		}

		if (leftButton == true) 
		{
			xVelocity = -5;
			tank.setRotation(270);

		}
		//Stopping horizontal movement if both buttons are pressed or released
		if (leftButton == true && rightButton == true)
		{
			xVelocity = 0;
		}

		if (leftButton == false && rightButton == false)
		{
			xVelocity = 0;
		}

		//Movement on y axis
		if (downButton == true)
		{
			yVelocity = 5;
			tank.setRotation(180);

		}

		if (upButton == true)
		{
			yVelocity = -5;
			tank.setRotation(0);
		}

		//Stopping vertical movement if both buttons are pressed or released
		if (upButton == true && downButton == true)
		{
			yVelocity = 0;
		}

		if (upButton == false && downButton == false)
		{
			yVelocity = 0;
		}
		tank.move(xVelocity, yVelocity);

	}
	void fire(sf::Event& event)
	{
		bool space = false;
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			space = true;
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		{
			space = false;
		}
		if (space)
		{
			if (tank.getRotation() == 0)
			{
				Bullet bullet(tank.getPosition().x, tank.getPosition().y - tank.getSize().y / 2, tank.getRotation());
				bullets.push_back(bullet);
			}
			if (tank.getRotation() == 90)
			{
				Bullet bullet(tank.getPosition().x + tank.getSize().x / 2, tank.getPosition().y , tank.getRotation());
				bullets.push_back(bullet);
			}
			if (tank.getRotation()==180)
			{
				Bullet bullet(tank.getPosition().x , tank.getPosition().y + tank.getSize().y / 2, tank.getRotation());
				bullets.push_back(bullet);
			}
			if (tank.getRotation() == 270)
			{
				Bullet bullet(tank.getPosition().x - tank.getSize().x / 2, tank.getPosition().y, tank.getRotation());
				bullets.push_back(bullet);
			}
		}
	}
	int isFired(vector<Bullet>& b)
	{
		int num = 0;
		for (int i = 0; i < b.size(); i++)
		{
			if (b[i].getVisibililty())
			{
				if (tank.getGlobalBounds().intersects(b[i].getGlobalBounds()))
				{
					num++;
					b[i].setVisibility(false);
				}
			}
		}
		return num;
	}
	void setVisibility(bool v)
	{
		visibilty = v;
	}
	bool getVisibility()
	{
		return visibilty;
	}
	sf::Vector2f getPosition()
	{
		return tank.getPosition();
	}
	int getRotation()
	{
		return tank.getRotation();
	}
	sf::Vector2f getSize()
	{
		return tank.getSize();
	}
	void dectectCollision()
	{
		vector<sf::RectangleShape> border = check.getBorder();
		for (size_t i = 0; i < border.size(); i++)
		{
			if (tank.getGlobalBounds().intersects(border[i].getGlobalBounds()))
			{
				int x = xVelocity == 0 ? 0 : xVelocity + 3;
				int y = yVelocity == 0 ? 0 : yVelocity + 3;
				tank.move(-x, -y);
			}
		}
	}
	~Tank()
	{}

private:
	sf::Texture tank_image;
	sf::RectangleShape tank;


	bool visibilty;
	Map check;
	int xVelocity = 0;
	int yVelocity = 0;
	bool leftButton;
	bool rightButton;
	bool upButton;
	bool downButton;
};


#endif // !TANK_OBJECT_H