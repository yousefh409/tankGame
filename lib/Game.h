#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Sprite.h"
#include "MainTank.h"
#include "SecondaryTank.h"
#include "Bullet.h"
#include "Maps.h"
#include "Wall.h"
#include "EnemyTank.h"


using namespace std;


class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	MainTank *mainTank;
	SecondaryTank *secondaryTank;
	vector<shared_ptr<Sprite>> allSprites;
	vector<shared_ptr<EnemyTank>> enemyTanks;
	set<shared_ptr<Sprite>> destroyed;
	

	//Intitializer Functions
	void initWindow();
	void initializeLevel();
	void updateWindow();
	void checkCollisions();
	void removeDestroyed();
	bool gameOver();
	void drawGameOver();
	//void initMap();

public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Functions 
	void gameOverCheck();
	void updateEvents();
	void update();
	void render();
	void run();

};

