#include "tankObject.h"
#include "enemyTankObject.h"
#include <sstream>
#include <Windows.h>

void moveBullets()
{
	int size = bullets.size();
	for (int i = 0; i < size; i++)
	{
		if (bullets[i].dectectCollision())
			bullets[i].setVisibility(false);
		else
			bullets[i].move();
	}
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].dectectCollision())
			enemyBullets[i].setVisibility(false);
		else
			enemyBullets[i].move();
	}
}


void drawBullets(sf::RenderWindow& windows)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if(bullets[i].getVisibililty())
			bullets[i].drawBullet(windows);
	}
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].getVisibililty())
			enemyBullets[i].drawBullet(windows);
	}
}
	

int main()
{
	srand(unsigned(time(0)));

	sf::RenderWindow windows(sf::VideoMode(1000, 600), "start");
	windows.setFramerateLimit(60);
	//images

	int enemy_counter = 3;

	//sounds
	sf::SoundBuffer hit_sound;
	if (!hit_sound.loadFromFile("Data/second.wav"))
		return -1;
	sf::Sound hit;
	hit.setBuffer(hit_sound);
	hit.play();
	hit.setLoop(true);

	//Font
	sf::Font font;
	font.loadFromFile("Data/Unique.ttf");
	//text
	sf::Text text_1;
	text_1.setFillColor(sf::Color::Green);
	text_1.setFont(font);
	text_1.setString("Your Health: ||||||||||");
	text_1.setPosition(740, 500);


	sf::Text text_2(text_1);
	text_2.setString("E1:  ||||||||||");
	text_2.setPosition(80, 50);

	sf::Text text_3(text_1);
	text_3.setString("E2: ||||||||||");
	text_3.setPosition(80, 80);

	sf::Text text_4(text_1);
	text_4.setString("E3: ||||||||||");
	text_4.setPosition(80, 110);


	sf::Text end(text_1);
	end.setPosition(500, 300);
	end.setOrigin(250, 150);
	//Map
	Map gameMap;
	Tank tank;

	int health = 0;
	int health_1 = 0;
	int health_2 = 0;
	int health_3 = 0;

	EnemyTank enemy_1(600, 500);
	EnemyTank enemy_2(300, 400);
	EnemyTank enemy_3(300, 100);
	int run = true;

	int counter = 1;
	while (run)
	{
		//Event handling
		sf::Event event;
		while (windows.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				run = false;
			tank.move(event);
 			tank.fire(event);
			
		}
		if (counter % 80 == 0)
		{
			if (enemy_1.getVisibility())
			{
				enemy_1.move();
				enemy_1.fire();
			}
			if (enemy_2.getVisibility())
			{
				enemy_2.move();
				enemy_2.fire();
			}
			if (enemy_3.getVisibility())
			{
				enemy_3.move();
				enemy_3.fire();
			}
			counter = 1;
		}
		else
			counter++;
		
		tank.dectectCollision();
		gameMap.drawMap(windows);


		health+=tank.isFired(enemyBullets);
		
		stringstream str;
		str.clear();
		str << "YOUR HEALTH: ";
		for (int i = 0; i < 10-health; i++)
		{
			str << "|";
		}
		text_1.setString(str.str());
		
		if (enemy_1.getVisibility())
		{
			stringstream str1;
			health_1 += enemy_1.isFired(bullets);
			str1 << "E01:  ";
			for (int i = 0; i < 10 - health_1; i++)
			{
				str1 << "|";
			}
			text_2.setString(str1.str());
			
		}
		if (enemy_2.getVisibility())
		{
			stringstream str2;
			health_2 += enemy_2.isFired(bullets);
			str2 << "E02: ";
			for (int i = 0; i < 10 - health_2; i++)
			{
				str2 << "|";
			}
			text_3.setString(str2.str());
			
		}
		if (enemy_3.getVisibility())
		{
			stringstream str3;
			health_3 += enemy_3.isFired(bullets);
			str3 << "E03: ";
			for (int i = 0; i < 10 - health_3; i++)
			{
				str3 << "|";
			}
			text_4.setString(str3.str());
			
		}
		tank.draw(windows);

		moveBullets();
		drawBullets(windows);
		//display windows
		if (health_1 < 10)
		{
			enemy_1.draw(windows);
			windows.draw(text_2);
		}
		else
			enemy_1.setVisibility(false);
		if (health_2 < 10)
		{
			enemy_2.draw(windows);
			windows.draw(text_3);
		}
		else
			enemy_2.setVisibility(false);
		if (health_3 < 10)
		{
			enemy_3.draw(windows);
			windows.draw(text_4);
		}
		else
			enemy_3.setVisibility(false);

		if (health_1 >= 10 && health_2 >= 10 && health_3 >= 10 && health < 10)
		{
			end.setString("YOU WON");
			end.setCharacterSize(100);
			end.setFillColor(sf::Color::Red);
			windows.draw(end);
			//system("pause");
		}
		if (health > 10)
		{
			end.setString("YOU LOOSE");
			end.setFillColor(sf::Color::Red);
			end.setCharacterSize(100);
			windows.draw(end);
			//system("pause");

		}
		windows.draw(text_1);
		windows.display();
	}
	
	windows.close();
	return 0;
}
