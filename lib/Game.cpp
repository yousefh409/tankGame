#include "Game.h"
// Static fucntions 

//Initializer Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Tank Game", sf::Style::Close);
}

void Game::initBackGround()
{
	sf::RectangleShape background(sf::Vector2f(1024.0f, 768.0f));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("images/background.png"));
	background.setTexture(&backgroundTexture);
}


void Game::initializeLevel(vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, int gameMap[][Maps::MAP_Y], vector<shared_ptr<EnemyTank>>& mapEnemyTanks)
{
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

void Game::updateWindow(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock)
{
	mainTank.update(*window, event, allSprites, clock);
	secondaryTank.update(*window, event, allSprites, clock);
	for (auto iter = allSprites.begin(); iter != allSprites.end(); iter++) {
		(*iter)->update(*window, event, allSprites, clock);
	}
	for (auto iter = enemyTanks.begin(); iter != enemyTanks.end(); iter++) {
		iter->get()->update(*window, event, allSprites, clock);
	}
}

void Game::checkCollisions(MainTank& mainTank, SecondaryTank& secondaryTank, vector<shared_ptr<Sprite>>& allSprites, vector<shared_ptr<EnemyTank>>& enemyTanks, sf::RenderWindow* window, sf::Event& event, sf::Clock& clock)
{
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
Game::Game()
{
	mainTank = MainTank("images/tank.png", sf::Vector2f(1024.0f / 2, 768.0f / 2), 0, 0.4);
	secondaryTank = SecondaryTank("images/tank.png", sf::Vector2f(1024.0f / 5, 768.0f / 5), 0, 0.4);
	//initializeLevel(allSprites, enemyTanks, Maps::mapOne, Maps::mapOneEnemyTanks);
}
//Destructor
Game::~Game()
{
	delete this->window;

}

// Functions
void Game::update()
{
	this->updateEvents();
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) this->window->close();
		default:;
		}
		checkCollisions(mainTank, secondaryTank, allSprites, enemyTanks, this->window, event, clock);
		updateWindow(mainTank, secondaryTank, allSprites, enemyTanks, this->window, event, clock);

	}
}

void Game::render()
{
	this->window->clear();

	//renderItems
	checkCollisions(mainTank, secondaryTank, allSprites, enemyTanks, this->window, event, clock);
	updateWindow(mainTank, secondaryTank, allSprites, enemyTanks, this->window, event, clock);
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		// New Code
		this->update();
		this->render();

	}
}

