
#include "MainMenuState.h"


void MainMenuState::initBackGround()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backGroundTexture.loadFromFile("../images/tankBackground.jpg"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backGroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("../fonts/Unique.ttf"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD FONT");
	}



}

void MainMenuState::initKeybinds()
{
	ifstream fin("../images/mainMenuStateKeybinds.txt");
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 720, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 720, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}

MainMenuState::~MainMenuState()
{
	auto it = this-> buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!\n"; // Debugging
}

void MainMenuState::updateInput()
{
	this->checkForQuit();
}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the state and hadles functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed() )
	{
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            cout << "Backdoor" << endl;
	    } else {
            this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	    }
	}

	//Quit the Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::update()
{
	this->updateMousePositions();
	this->updateInput();

	this->updateButtons();



}

void MainMenuState::render(sf::RenderWindow* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	target->display();
}

