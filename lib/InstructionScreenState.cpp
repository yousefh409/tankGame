#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include "InstructionScreenState.h"
#include "Score.h"
#include "Maps.h"



void InstructionScreenState::initBackGround()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backGroundTexture.loadFromFile(Maps::filePrefix + "scoreBackground.jpg"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backGroundTexture);
}

void InstructionScreenState::initFonts()
{
	if (!this->font.loadFromFile(Maps::filePrefix + "Unique.ttf"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD FONT");
	}
}

void InstructionScreenState::initKeybinds()
{
	ifstream fin(Maps::filePrefix + "mainMenuStateKeybinds.txt");
	if (!fin)
	{
		cout << "Cant find mainMenuStateKeybinds.txt" << endl;
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

void InstructionScreenState::initButtons()
{
	this->buttons["EXIT_STATE"] = new Button(100, 500, 150, 50,
		&this->font, "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

InstructionScreenState::InstructionScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initInstructions();
}

InstructionScreenState::~InstructionScreenState()
{
	auto it = this-> buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void InstructionScreenState::endState()
{
	std::cout << "Ending InstructionScreenState!\n"; // Debugging
}

void InstructionScreenState::updateInput()
{
	this->checkForQuit();
}

void InstructionScreenState::updateButtons()
{
	//Updates all the buttons in the state and hadles functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Quit the Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void InstructionScreenState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void InstructionScreenState::update()
{
	this->updateMousePositions();
	this->updateInput();
	this->updateButtons();
}

void InstructionScreenState::render(sf::RenderWindow* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->renderInstructions();
	target->display();
}

void InstructionScreenState::renderInstructions() {

}



void InstructionScreenState::initInstructions() {
    instructionDescription = "Your goal in this game is to defeat all the enemies in the shortest time possible";

    instructionKeys["W"] = "Move up";
    instructionKeys["A"] = "Move left";
    instructionKeys["S"] = "Move down";
    instructionKeys["D"] = "Move right";
    instructionKeys["SPACE"] = "Shoot normal bullet";
    instructionKeys["LEFT CLICK"] = "Shoot a fire ball";
    instructionKeys["RIGHT CLICK"] = "Shoot a bouncing bullet";
    instructionKeys["LEFT SHIFT"] = "Shoot a laser";

    bulletDescrips[Maps::filePrefix + "bullet.png"] = "Deals 10 damage to the enemy if hit";
    bulletDescrips[Maps::filePrefix + "bulletBig.png"] = "Moves slow, but will deal 25 damage to enemy if hit";
    bulletDescrips[Maps::filePrefix + "bouncingBullet.png"] = "Will bounce of walls a maximum of 2 times, and will deal 20 damage if hit";
    bulletDescrips[Maps::filePrefix + "laserBullet.png"] = "Will deal 40 damage to enemies, but will also deal 10 to self";
}



