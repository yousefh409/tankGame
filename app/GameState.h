#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Score.h"
#include "State.h"
#include "SFML/Audio.hpp"


class GameState : public State
{
private:
    unsigned int gameIndex;
    bool isTest;
    Score score;
	sf::Time whenEnded;
	bool isEndedSet;
	sf::Event event;
	sf::Clock clock;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	vector<shared_ptr<Sprite>> allSprites; //main and secondary tanks stored in 1st and 2nd elements
	vector<shared_ptr<EnemyTank>> enemyTanks;
	set<shared_ptr<Sprite>> destroyed;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound sound;



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
	void writeScoreFile();
	void drawScore();
	void drawLevel();
	void playHitSound();
	//Functions


public:

	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int newGame, bool isTestNew);
	virtual ~GameState() = default;


	//Functions
	void endState();
	void updateInput();
	void update();
	void render(sf::RenderWindow* target = nullptr);

};
#endif

