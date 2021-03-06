#include "GameState.h"
//Intitializer Functions

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f(1024.0f, 768.0f));
	backgroundTexture.loadFromFile(std::string("images/background.png"));
	this->background.setTexture(&backgroundTexture);
}

void GameState::initializeLevel()
{
	for (int i = 0; i < Maps::MAP_X; i++)
	{
		for (int j = 0; j < Maps::MAP_Y; j++)
		{
			if (Maps::mapOne[i][j] == 1)
			{
				Wall wall("images/border.png", sf::Vector2f(i * 50, j * 70), 0, 0.13);
				allSprites.push_back(make_shared<Wall>(wall));
			}
		}
	}

	enemyTanks = Maps::mapOneEnemyTanks;
}

void GameState::updateWindow()
{
	this->mainTank->update(this->window, event, allSprites, clock);
	this->secondaryTank->update(this->window, event, allSprites, clock);
	for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
		(*iter)->update(this->window, event, allSprites, clock);
	}
	for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
		iter->get()->update(this->window, event, allSprites, clock);
	}
	for (auto iter = destroyed.begin(); iter != destroyed.end(); iter++) {
		(*iter)->update(this->window, event, allSprites, clock);
	}
}

void GameState::checkCollisions()
{
	for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
		if ((*iter)->isIntersect(this->mainTank)) {
			if (this->mainTank->collision(iter->get())) {
				//MAIN LOST
			}
			if ((*iter)->collision(this->mainTank)) {
				destroyed.insert(*iter);
				iter = allSprites.erase(iter);
				iter--;
			}
		}
	}

	for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
		if ((*iter)->isIntersect(this->secondaryTank)) {
			if (this->secondaryTank->collision(iter->get())) {
				//SECONDARY LOST
			}
			if ((*iter)->collision(this->secondaryTank)) {
				destroyed.insert(*iter);
				iter = allSprites.erase(iter);
				iter--;
			}
		}
	}

	for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
		for (auto jter = allSprites.begin(); jter != allSprites.end(); jter++) {
			if ((*jter)->isIntersect(iter->get())) {
				if ((*jter)->collision(iter->get()) && (*iter)->collision(jter->get())) {
					destroyed.insert(*jter);
					jter = allSprites.erase(jter);
					jter--;

					destroyed.insert(*iter);
					iter = enemyTanks.erase(iter);
					iter--;
				}
				else if ((*jter)->collision(iter->get())) {
					destroyed.insert(*jter);
					jter = allSprites.erase(jter);
					jter--;
				}
				else if ((*iter)->collision(jter->get())) {
					destroyed.insert(*iter);
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
	bool result = false;
	if (this->mainTank->getHealth() <= 0) {
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
		drawGameOver();
	}
}

void GameState::drawGameOver()
{
	sf::Font font;
	font.loadFromFile("fonts/Unique.ttf");

	sf::Text gameEnd;
	sf::FloatRect textRect = gameEnd.getLocalBounds();

	gameEnd.setFont(font);
	gameEnd.setOrigin(textRect.width / 2.0f + 200, textRect.height / 2.0f + 50);
	gameEnd.setPosition(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f);
	gameEnd.setCharacterSize(100);

	if (this->mainTank->getHealth() > 0) {
		gameEnd.setString("YOU WON");
		gameEnd.setFillColor(sf::Color::Green);
	}
	else {
		gameEnd.setString("YOU LOST");
		gameEnd.setFillColor(sf::Color::Red);
	}

	this->window->draw(gameEnd);
}

void GameState::initKeybinds()
{
	ifstream fin("images/gameStateKeybinds.txt");
	if (!fin)
	{
		cout << "Cant find file2" << endl;
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

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackground();
	this->initKeybinds();
	this->mainTank = new MainTank("images/tank.png", sf::Vector2f(1024.0f / 2, 768.0f / 2), 0, 0.4);
	this->secondaryTank = new SecondaryTank("images/tank.png", sf::Vector2f(1024.0f / 5, 768.0f / 5), 0, 0.4);
	this->initializeLevel();
}

GameState::~GameState()
{
}


void GameState::endState()
{
	std::cout << "Ending GameState!\n"; //Debugging
}

void GameState::updateInput()
{
	this->checkForQuit();
	this->gameOverCheck();
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

