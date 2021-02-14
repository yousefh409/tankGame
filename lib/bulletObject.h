#ifndef BULLET_H
#define BULLET_H
#include "mapObject.h"
class Bullet
{
public:
	Bullet(float x,float y,int rotation)
	{
		enemyBullet.loadFromFile("Data/bullet1.png");

		bullet.setTexture(&enemyBullet);
		bullet.setSize(sf::Vector2f(5, 5));
		bullet.setOrigin(2.5f, 2.5f);
		bullet.setFillColor(sf::Color::Red);
		this->x = x;
		this->y = y;
		this->rotation = rotation;
		bullet.setPosition(x, y);
		bullet.setRotation(rotation);
	}
	void drawBullet(sf::RenderWindow& window)
	{
		window.draw(bullet);
	}
	bool dectectCollision()
	{
		vector<sf::RectangleShape> border = check.getBorder();
		for (size_t i = 0; i < border.size(); i++)
		{
			if (bullet.getGlobalBounds().intersects(border[i].getGlobalBounds()))
			{
				return true;
			}
		}
		return false;
	}
	sf::FloatRect getGlobalBounds()
	{
		return bullet.getGlobalBounds();
	}
	bool getVisibililty()
	{
		return isVisible;
	}
	void setVisibility(bool v)
	{
		isVisible = v;
	}
	void move()
	{
		if(rotation==0)
			bullet.move(0, -5);
		if (rotation == 90)
			bullet.move(5, 0);
		if (rotation == 180)
			bullet.move(0, 5);
		if (rotation == 270)
			bullet.move(-5, 0);
	}
	~Bullet()
	{}

private:
	sf::Texture enemyBullet;
	sf::RectangleShape bullet;
	float x, y, rotation;
	bool isVisible=true;
	Map check;
};



#endif // !BULLET_H
