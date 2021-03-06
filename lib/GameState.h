#pragma once

#include "State.h"

class GameState :public State
{
private:
	
	sf::Event event;
	sf::Clock clock;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	MainTank* mainTank;
	SecondaryTank* secondaryTank;
	vector<shared_ptr<Sprite>> allSprites;
	vector<shared_ptr<EnemyTank>> enemyTanks;
	set<shared_ptr<Sprite>> destroyed;


	//Intitializer Functions
	void initKeybinds();
	void initBackground();
	void initializeLevel();
	void updateWindow();
	void checkCollisions();
	void removeDestroyed();
	bool gameOver();
	void gameOverCheck();
	void drawGameOver();
	//Functions
	

public:
	
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();


	//Functions
	void endState();
	void updateInput();
	void update();
	void render(sf::RenderWindow* target = nullptr);

};

