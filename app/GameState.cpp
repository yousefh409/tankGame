#include <string>
#include <fstream>
#include "GameState.h"
#include "ScoresScreenState.h"
#include "MainMenuState.h"
#include "PauseState.h"


using namespace std;

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(1024.0f, 768.0f));
	backgroundTexture.loadFromFile(std::string(Maps::filePrefix + "background.png"));
	this->background.setTexture(&backgroundTexture);
}

void GameState::initializeLevel()
{
	for (int i = 0; i < Maps::MAP_X; i++)
	{
		for (int j = 0; j < Maps::MAP_Y; j++)
		{
			if (Maps::levels[gameIndex].mapArray[i][j] == 1)
			{
				Wall wall(Maps::filePrefix + "border.png", sf::Vector2f(i * 50, j * 70), 0, 0.13, Maps::filePrefix);
				allSprites.push_back(make_shared<Wall>(wall));
			}
		}
	}
	if (!this->isTest) {
        for (auto iter = Maps::levels[gameIndex].enemyTanks.begin(); iter != Maps::levels[gameIndex].enemyTanks.end(); iter++) {
            enemyTanks.push_back((*iter)->clone());
        }
	}
}

void GameState::updateWindow()
{
    //WE USE INDECIES RATHER THAN ITERATORS BECAUSE ITERATORS WILL BE INVALIDATED
    // IF WE INSERT ELEMENTS INTO THE VECTOR(WHICH WILL HAPPEN)
    unsigned allSpritesSize = allSprites.size();
	for (unsigned i = 0; i < allSpritesSize; i++) {
		allSprites[i]->update(this->window, event, allSprites, clock);
	}

	unsigned enemyTankSize = enemyTanks.size();
	for (unsigned i = 0; i < enemyTankSize; i++) {
		enemyTanks[i]->update(this->window, event, allSprites, clock);
	}
	for (auto iter = destroyed.begin(); iter != destroyed.end(); iter++) {
		(*iter)->update(this->window, event, allSprites, clock);
	}
    this->drawScore();
}

void GameState::checkCollisions()
{
    bool iterCollision = false;
    bool jterCollision = false;
	for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); ) { //Checking for collisions between all sprites and enemyTanks
		for (auto jter = allSprites.begin(); jter != allSprites.end();) {
			if ((*jter)->isIntersect(iter->get())) {
                iterCollision = (*iter)->collision(jter->get());
                jterCollision = (*jter)->collision(iter->get());
                if (jterCollision) {
					destroyed.insert(*jter);
					jter = allSprites.erase(jter);
					playHitSound();
				} else {
				    jter++;
				}
				if (iterCollision) {
					destroyed.insert(*iter);
					iter = enemyTanks.erase(iter);
					playHitSound();
					score.incrScore(100 * (enemyTanks.size() + 1));
					break;
				}
			} else {
                jter++;
			}
		}
		if (!iterCollision) {
            iter++;
		}
	}

    unsigned vectorLength = allSprites.size();
	//WE USE INDECIES HERE TO MAKE THE DELETE SYNTAX EASIER
	for (unsigned i = 0; i < vectorLength; i++) { //Checking for collisions between all other sprites
		for (unsigned j = i + 1; j < vectorLength; j++) {
			if ((allSprites[i] != allSprites[j]) && allSprites[i]->isIntersect(allSprites[j].get())) {
                bool iterCollision = allSprites[i]->collision(allSprites[j].get());
                bool jterCollision = allSprites[j]->collision(allSprites[i].get());
                bool isSound = false;
				if (jterCollision) {
					destroyed.insert(allSprites[j]);
					allSprites.erase(allSprites.begin() + j);
					vectorLength--;
					playHitSound();
					isSound = true;
				}
				if (iterCollision) {
                    destroyed.insert(allSprites[i]);
					allSprites.erase(allSprites.begin() + i);
                    vectorLength--;
                    if (!isSound) {
                        playHitSound();
                    }
					break;
				}
			}
		}
	}
}

void GameState::removeDestroyed()
{
	for (auto iter = destroyed.begin(); iter != destroyed.end();) {
		if ((*iter)->isExploded(clock)) {
			iter = destroyed.erase(iter);
		}
		else {
			iter++;
		}
	}
}

bool GameState::gameOver()
{
    if (this->isTest) {
        return false;
    }
	bool result = false;
	if (this->allSprites.front()->getHealth() <= 0) {
		result = true;
	}
	if (enemyTanks.size() == 0) {
		result = true;
	}
	return result;
}

void GameState::gameOverCheck()
{
	if (!gameOver())
	{
		checkCollisions();
		updateWindow();
		removeDestroyed();
	}
	else {
        if (!isEndedSet) {
            int incrScore = 1000 - (30 * this->clock.getElapsedTime().asSeconds());
            if (incrScore < 0) { //Make sure that it is not negative
                incrScore = 0;
            }
            score.incrScore(incrScore);
            this->writeScoreFile();
            whenEnded = clock.getElapsedTime();
            isEndedSet = true;
        }
	    sf::Time currentTime = clock.getElapsedTime();
        if ((currentTime - whenEnded).asSeconds() >= 3) {
            this->quit = true;
        } else {
            drawGameOver();
        }
	}
}

void GameState::drawGameOver()
{
    this->drawScore();
	sf::Font font;
	font.loadFromFile(Maps::filePrefix + "Unique.ttf");

	sf::Text gameEnd;
	sf::FloatRect textRect = gameEnd.getLocalBounds();

	gameEnd.setFont(font);
	gameEnd.setOrigin(textRect.width / 2.0f + 200, textRect.height / 2.0f);
	gameEnd.setPosition(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f - 130);
	gameEnd.setCharacterSize(100);

	if (this->allSprites.front()->getHealth() > 0) {
		gameEnd.setString("YOU WON");
		gameEnd.setFillColor(sf::Color::Green);
	}
	else {
		gameEnd.setString("YOU LOST");
		gameEnd.setFillColor(sf::Color::Red);
	}
	this->window->draw(gameEnd);

    sf::Time currentTime = clock.getElapsedTime();
    gameEnd.setString(to_string(static_cast<int>(4 - (currentTime - whenEnded).asSeconds())));
    gameEnd.setCharacterSize(150);
    gameEnd.setFillColor(sf::Color::Blue);
    gameEnd.setOrigin(textRect.width / 2.0f + 30, textRect.height / 2.0f);
    gameEnd.setPosition(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f);

	this->window->draw(gameEnd);
}

void GameState::initKeybinds()
{
	ifstream fin(Maps::filePrefix + "gameStateKeybinds.txt");
	if (!fin)
	{
		cout << "Cant find gameStateKeybinds.txt" << endl;
	}
	if (fin.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (fin >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);

		}
	}
	fin.close();


}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int newGame, bool isTestNew)
	: State(window, supportedKeys, states), gameIndex(newGame), isTest(isTestNew), score(newGame, 0), isEndedSet(false)
{
	this->initBackground();
	this->initKeybinds();
	if (isTest) {
        this->allSprites.push_back(make_shared<SecondaryTank>(SecondaryTank(Maps::filePrefix + "tank.png", sf::Vector2f(1024.0f / 5, 768.0f / 5), 0, 0.4, Maps::filePrefix)));
	}
	this->allSprites.push_back(make_shared<MainTank>(MainTank(Maps::filePrefix + "tank.png", Maps::mainTankPositions[gameIndex], 0, 0.4, Maps::filePrefix)));
	this->initializeLevel();
    font.loadFromFile(Maps::filePrefix + "Unique.ttf");

    buffer.loadFromFile(Maps::filePrefix + "gunShot.wav");
    sound.setBuffer(buffer);
    sound.setVolume(1.5);
}


void GameState::endState()
{
    if ((gameIndex == Maps::levels.size()) && (this->allSprites.front()->getHealth() > 0)) {
        auto current = this->states->top();
        this->states->pop();
        this->states->push(new ScoresScreenState(this->window, this->supportedKeys, this->states));
        this->states->push(current);
    } else {
        auto current = this->states->top();
        this->states->pop();
        if (this->allSprites.front()->getHealth() > 0) {
            this->states->push(new GameState(this->window, this->supportedKeys, this->states, gameIndex + 1, false));
        } else {
             this->states->push(new GameState(this->window, this->supportedKeys, this->states, gameIndex, false));
        }
        this->states->push(current);
    }
	this->quit = true;
}

void GameState::updateInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		this->states->push(new PauseState(this->window, this->supportedKeys, this->states));
	} else {
        this->checkForQuit();
        this->gameOverCheck();
	}
}

void GameState::update()
{
	this->updateMousePositions();
	this->updateInput();
}

void GameState::render(sf::RenderWindow* target)
{
    target->draw(background);
    this->gameOverCheck();
    target->display();
}

void GameState::writeScoreFile() {
    ofstream fout("scores.bin", ios::binary | ios::app);
    if (!fout) {
        cerr << "Cant open file: scores.bin" << endl;
        exit(-2);
    }
    fout << score;
}

void GameState::drawScore() {
	sf::Text writeScore;
	writeScore.setFont(font);
	writeScore.setCharacterSize(50);
    writeScore.setFillColor(sf::Color::Green);

    writeScore.setPosition(sf::Vector2f(10, 10));
    writeScore.setString("SCORE: " + to_string(score.getScore()));
    this->window->draw(writeScore);
}

void GameState::playHitSound() {
    sound.play();
}


