#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Sprite.h"
#include "MainTank.h"
#include "SecondaryTank.h"
#include "Bullet.h"
#include "Map.h"
#include "Wall.h"
#include "EnemyTank.h"


using namespace std;

void initializeLevel(vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, int gameMap[][Maps::MAP_Y], vector<shared_ptr<EnemyTank>>& mapEnemyTanks);
void updateWindow(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock, set<shared_ptr<Sprite>>& destroyed);
void checkCollisions(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock, set<shared_ptr<Sprite>>& destroyed);
void removeDestroyed(set<shared_ptr<Sprite>>& destroyed, sf::Clock clock);
bool gameOver(MainTank& mainTank, vector<shared_ptr<EnemyTank>>& enemyTanks);
void drawGameOver(sf::RenderWindow& window, bool isWin);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tank Game", sf::Style::Close);
    sf::Event event;
    sf::Clock clock;

    sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("../images/background.png"));
	background.setTexture(&backgroundTexture);

	MainTank mainTank = MainTank("../images/tank.png", sf::Vector2f(1024.0f/2, 768.0f/2), 0, 0.4);
    SecondaryTank secondaryTank = SecondaryTank("../images/tank.png", sf::Vector2f(1024.0f/5, 768.0f/5), 0, 0.4);

	vector<shared_ptr<Sprite>> allSprites;
	vector<shared_ptr<EnemyTank>> enemyTanks;
	set<shared_ptr<Sprite>> destroyed;

	initializeLevel(allSprites, enemyTanks, Maps::mapOne, Maps::mapOneEnemyTanks);

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
			default: ;
			}
			if (!gameOver(mainTank, enemyTanks)) {
                checkCollisions(mainTank, secondaryTank, allSprites, enemyTanks, window, event, clock, destroyed);
                updateWindow(mainTank, secondaryTank, allSprites, enemyTanks, window, event, clock, destroyed);
                removeDestroyed(destroyed, clock);
			} else {
                drawGameOver(window, mainTank.getHealth() > 0);
			}
		}

		window.clear();
		window.draw(background);
		if (!gameOver(mainTank, enemyTanks)) {
            checkCollisions(mainTank, secondaryTank, allSprites,enemyTanks, window, event, clock, destroyed);
            updateWindow(mainTank, secondaryTank, allSprites, enemyTanks, window, event, clock, destroyed);
            removeDestroyed(destroyed, clock);
		} else {
            drawGameOver(window, mainTank.getHealth() > 0);
        }
		window.display();
	}
}

void initializeLevel(vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, int gameMap[][Maps::MAP_Y], vector<shared_ptr<EnemyTank>>& mapEnemyTanks) {
   for (int i = 0; i < Maps::MAP_X; i++)
    {
        for (int j = 0; j < Maps::MAP_Y; j++)
        {
            if (gameMap[i][j] == 1)
            {
                Wall wall("../images/border.png", sf::Vector2f(i * 50, j * 70), 0, 0.13);
                allSprites.push_back(make_shared<Wall>(wall));
            }
        }
    }

    enemyTanks = mapEnemyTanks;
}


void updateWindow(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock, set<shared_ptr<Sprite>>& destroyed) {
    mainTank.update(window, event, allSprites, clock);
    secondaryTank.update(window, event, allSprites, clock);
    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        (*iter)->update(window, event, allSprites, clock);
    }
    for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
        iter->get()->update(window, event, allSprites, clock);
    }
    for (auto iter = destroyed.begin(); iter != destroyed.end(); iter++) {
        (*iter)->update(window, event, allSprites, clock);
    }
}

void checkCollisions(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow& window, sf::Event& event, sf::Clock& clock, set<shared_ptr<Sprite>>& destroyed) {
    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        if ((*iter)->isIntersect(&mainTank)) {
            if(mainTank.collision(iter->get())) {
                //MAIN LOST
            }
            if((*iter)->collision(&mainTank)) {
                destroyed.insert(*iter);
                iter = allSprites.erase(iter);
                iter--;
            }
        }
    }

     for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        if ((*iter)->isIntersect(&secondaryTank)) {
            if(secondaryTank.collision(iter->get())) {
                //SECONDARY LOST
            }
            if((*iter)->collision(&secondaryTank)) {
                destroyed.insert(*iter);
                iter = allSprites.erase(iter);
                iter--;
            }
        }
    }

    for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
        for (auto jter = allSprites.begin(); jter != allSprites.end(); jter++) {
            if ((*jter)->isIntersect(iter->get())) {
                if((*jter)->collision(iter->get()) && (*iter)->collision(jter->get())) {
                    destroyed.insert(*jter);
                    jter = allSprites.erase(jter);
                    jter--;

                    destroyed.insert(*iter);
                    iter = enemyTanks.erase(iter);
                    iter--;
                } else if ((*jter)->collision(iter->get())) {
                    destroyed.insert(*jter);
                    jter = allSprites.erase(jter);
                    jter--;
                } else if ((*iter)->collision(jter->get())) {
                    destroyed.insert(*iter);
                    iter = enemyTanks.erase(iter);
                    iter--;
                }
            }
        }
    }

    for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
        for (auto jter = allSprites.begin(); jter != allSprites.end(); jter++) {
            if((*jter != *iter) && (*iter)->isIntersect(jter->get()) && (*iter)->collision(jter->get())) {
                if ((*jter)->collision(iter->get())) {
                    destroyed.insert(*jter);
                    jter = allSprites.erase(jter);
                    jter--;
                }
                destroyed.insert(*iter);
                iter = allSprites.erase(iter);
                iter--;

                break;
            }
        }
    }
}

void removeDestroyed(set<shared_ptr<Sprite>>& destroyed, sf::Clock clock) {
    for (auto iter = destroyed.begin(); iter != destroyed.end();) {
        if ((*iter)->isExploded(clock)) {
            iter = destroyed.erase(iter);

        } else {
            iter++;
        }
    }
}

bool gameOver(MainTank& mainTank, vector<shared_ptr<EnemyTank>>& enemyTanks) {
    bool result = false;
    if (mainTank.getHealth() <= 0) {
        result = true;
    }
    if (enemyTanks.size() == 0) {
        result = true;
    }
    return result;
}

void drawGameOver(sf::RenderWindow& window, bool isWin) {
    sf::Font font;
    font.loadFromFile("../fonts/Unique.ttf");

    sf::Text gameEnd;
    sf::FloatRect textRect = gameEnd.getLocalBounds();

    gameEnd.setFont(font);
    gameEnd.setOrigin(textRect.width / 2.0f + 200, textRect.height / 2.0f + 50);
    gameEnd.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    gameEnd.setCharacterSize(100);

    if (isWin) {
        gameEnd.setString("YOU WON");
        gameEnd.setFillColor(sf::Color::Green);
    } else {
        gameEnd.setString("YOU LOST");
        gameEnd.setFillColor(sf::Color::Red);
    }

    window.draw(gameEnd);
}

