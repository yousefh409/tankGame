#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "MainTank.h"
#include "SecondaryTank.h"
#include "Bullet.h"
#include "Map.h"
#include "Wall.h"
#include "EnemyTank.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

void initializeLevel(vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, int gameMap[][Maps::MAP_Y], vector<shared_ptr<EnemyTank>>& mapEnemyTanks);
void updateWindow(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock);
void checkCollisions(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock);

class Game
{
private:
	//Variables
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock clock;
	sf::RectangleShape background;
    MainTank  mainTank = MainTank("images/tank.png", sf::Vector2f(1024.0f / 2, 768.0f / 2), 0, 0.4);
    SecondaryTank secondaryTank = SecondaryTank("images/tank.png", sf::Vector2f(1024.0f / 5, 768.0f / 5), 0, 0.4);
    vector<shared_ptr<Sprite>> allSprites;
    vector<shared_ptr<EnemyTank>> enemyTanks;

	//Initializations
	void initWindow();
	void initBackGround();


public:
	Game();
	virtual ~Game();

	//Functions
	void update();
	void updateEvents();
	void render();
	void run(); // game loop

};

void initializeLevel(vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, int gameMap[][Maps::MAP_Y], vector<shared_ptr<EnemyTank>>& mapEnemyTanks) {
    for (int i = 0; i < Maps::MAP_X; i++)
    {
        for (int j = 0; j < Maps::MAP_Y; j++)
        {
            if (gameMap[i][j] == 1)
            {
                Wall wall("images/border.png", sf::Vector2f(i * 50, j * 70), 0, 0.13);
                allSprites.push_back(make_shared<Wall>(wall));
            }
        }
    }

    enemyTanks = mapEnemyTanks;
}


void updateWindow(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock) {
    mainTank.update(*window, event, allSprites, clock);
    secondaryTank.update(*window, event, allSprites, clock);
    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        (*iter)->update(*window, event, allSprites, clock);
    }
    for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
        iter->get()->update(*window, event, allSprites, clock);
    }
}

void checkCollisions(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock) {
    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        if ((*iter)->isIntersect(&mainTank)) {
            if (mainTank.collision(iter->get())) {
                exit(0); //MAIN LOST
            }
            if ((*iter)->collision(&mainTank)) {
                iter = allSprites.erase(iter);
                iter--;
            }
        }
    }

    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        if ((*iter)->isIntersect(&secondaryTank)) {
            if (secondaryTank.collision(iter->get())) {
                exit(0); //SECONDARY LOST
            }
            if ((*iter)->collision(&secondaryTank)) {
                iter = allSprites.erase(iter);
                iter--;
            }
        }
    }

    for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
        for (auto jter = allSprites.begin(); jter != allSprites.end(); jter++) {
            if ((*jter)->isIntersect(iter->get())) {
                if ((*jter)->collision(iter->get()) && (*iter)->collision(jter->get())) {
                    jter = allSprites.erase(jter);
                    jter--;

                    iter = enemyTanks.erase(iter);
                    iter--;
                }
                else if ((*jter)->collision(iter->get())) {
                    jter = allSprites.erase(jter);
                    jter--;
                }
                else if ((*iter)->collision(jter->get())) {
                    iter = enemyTanks.erase(iter);
                    iter--;
                }
            }
        }
    }

    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        for (auto jter = allSprites.begin(); jter != allSprites.end(); jter++) {
            if ((*jter != *iter) && (*iter)->isIntersect(jter->get()) && (*iter)->collision(jter->get())) {
                if ((*jter)->collision(iter->get())) {
                    jter = allSprites.erase(jter);
                    jter--;
                }
                iter = allSprites.erase(iter);
                iter--;

                break;
            }
        }
    }
}


