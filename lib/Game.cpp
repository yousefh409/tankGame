#include "Game.h"

//Intitializer Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Tank Game", sf::Style::Close);
	//this->background.setSize(sf::Vector2f(1024.0f, 768.0f));
	//backgroundTexture.loadFromFile(std::string("images/background.png"));
	//this->background.setTexture(&backgroundTexture);
}



void Game::initKeys()
{

	ifstream fin("../images/keys.txt");
	if (!fin)
	{
		cout << "Cant find file" << endl;
	}
	if (fin.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (fin >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;

		}

	}
	fin.close();
}

void Game::initState()
{
	//Here is where First State Pushed on stack is MainMenu
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}



//Constructor/Destructors
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initState();
	//All this is now defined in GameState
	//this->mainTank = new MainTank("images/tank.png", sf::Vector2f(1024.0f / 2, 768.0f / 2), 0, 0.4);
	//this->secondaryTank = new SecondaryTank("images/tank.png", sf::Vector2f(1024.0f / 5, 768.0f / 5), 0, 0.4);
	//this->initializeLevel();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
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
		//this->gameOverCheck();
	}
}



void Game::update()
{
	this->updateEvents();
	if (!this->states.empty())
	{
		this->states.top()->update();

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}

}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	//this->window->draw(background);
	//this->gameOverCheck();
	//this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();

	}
}

void Game::endApplication()
{
	std::cout << "Ending Application\n";
}
