#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"


using namespace std;


class Game
{
private:
	//Variables
	int levelIndex;
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


	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;


	//Intitializer Functions
	void initWindow();
	void initializeLevel();
	void updateWindow();
	void checkCollisions();
	void removeDestroyed();
	bool gameOver();
	void drawGameOver();
	void initKeys();
	void initState(); //pushes a state


public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Functions
	//void gameOverCheck();
	void updateEvents();
	void update();
	void render();
	void run();
	void endApplication();

};
#endif
