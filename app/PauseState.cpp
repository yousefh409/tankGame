#include "PauseState.h"

void PauseState::initBackGround()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backGroundTexture.loadFromFile(Maps::filePrefix + "tankBackground.jpg"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backGroundTexture);
}

void PauseState::initFonts()
{
	if (!this->font.loadFromFile(Maps::filePrefix + "Unique.ttf"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD FONT");
	}
}

void PauseState::initKeybinds()
{
	ifstream fin(Maps::filePrefix + "mainMenuStateKeybinds.txt");
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

void PauseState::initButtons()
{

	this->buttons["BACK_STATE"] = new Button(400, 300, 150, 50,
		&this->font, "Back to game",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE"] = new Button(400, 400, 150, 50,
		&this->font, "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}
PauseState::PauseState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}
PauseState::~PauseState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseState::endState()
{
	std::cout << "Ending PauseState!\n"; // Debugging
}

void PauseState::updateInput()
{
}

void PauseState::updateButtons()
{

	//Updates all the buttons in the state and handles functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Quit the Game
	if (this->buttons["BACK_STATE"]->isPressed())
	{
		this->quit = true;
	}
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
        this->states->pop();
        this->states->pop();
	}
}

void PauseState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void PauseState::update()
{
	this->updateMousePositions();
	this->updateInput();

	this->updateButtons();

}

void PauseState::render(sf::RenderWindow* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	target->display();
}
