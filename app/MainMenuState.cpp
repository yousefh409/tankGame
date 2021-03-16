#include "ScoresScreenState.h"
#include "InstructionScreenState.h"
#include "MainMenuState.h"
#include "Button.h"
#include <SFML/Audio.hpp>


void MainMenuState::initBackGround()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backGroundTexture.loadFromFile(Maps::filePrefix + "tankBackground.jpg"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backGroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile(Maps::filePrefix + "Unique.ttf"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 250, 50,
		&this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->buttons["INSTRUCTION_STATE"] = new Button(100, 200, 250, 50,
		&this->font, "Instructions",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->buttons["SCORE_STATE"] = new Button(100, 300, 250, 50,
		&this->font, "High Scores",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 400, 250, 50,
		&this->font, "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->buttons["MUSIC_STATE"]= new Button(850, 600, 70, 70,
		&this->font, "Music",
		sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{

	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	if (!sound.openFromFile(Maps::filePrefix + "themeSong.wav")) {
        cerr << "Could not open file: themeSong.wav";
        exit(-2);
	}
	lastSoundTrigger = clock.getElapsedTime();
    sound.play();
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
                int toTeleport;
                cout << "Enter level number: ";
                cin >> toTeleport;
                this->states->push(new GameState(this->window, this->supportedKeys, this->states, toTeleport, false));
            } else {
                this->states->push(new GameState(this->window, this->supportedKeys, this->states, 1, true));
            }
	    } else {
            this->states->push(new GameState(this->window, this->supportedKeys, this->states, 1, false));
	    }
	}

	if (this->buttons["SCORE_STATE"]->isPressed() )
	{
        this->states->push(new ScoresScreenState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["INSTRUCTION_STATE"]->isPressed() )
	{
        this->states->push(new InstructionScreenState(this->window, this->supportedKeys, this->states));
	}

	//Quit the Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
	if (this->buttons["MUSIC_STATE"]->isPressed()) {
	    sf::Time currentTime = clock.getElapsedTime();
        if ((currentTime - lastSoundTrigger).asSeconds() > 0.25) {
            if (sound.getStatus() == sf::Music::Status::Playing) {
                sound.pause();
            } else {
                sound.play();
            }
            lastSoundTrigger = clock.getElapsedTime();
        }
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
	this->drawTitle();
	this->renderButtons(target);
	target->display();
}

void MainMenuState::drawTitle(){
	sf::Text writeTitle;
	writeTitle.setFont(font);
	writeTitle.setCharacterSize(50);
	writeTitle.setFillColor(sf::Color::White);

	writeTitle.setPosition(sf::Vector2f(400, 20));
	writeTitle.setString("Tank Game");
	this->window->draw(writeTitle);
}
