#include <fstream>
#include <sstream>
#include <iomanip>
#include "ScoresScreenState.h"
#include "Score.h"
#include "Maps.h"


void ScoresScreenState::initHighScores() {
    for (int i = 1; i <= Maps::numLevels; i++) {
        highScores[i] = Score(i, 0);
    }
    try {
        ifstream fin("scores.bin", ios::binary);
        if (!fin) {
           throw string("Could not open file: scores.bin");
        }
        string input;
        Score score;
        while (getline(fin, input)) {
            istringstream sout(input);
            sout >> score;
            unsigned level = score.getLevel();
            if (score > highScores[level]) {
                highScores[level] = score;
            }
        }

    } catch (string err) {
        ofstream fout("scores.bin", ios::binary);
        if (!fout) {
            cerr << "Could not open file: scores.bin" << endl;
            exit(-2);
        }
        this->initHighScores();
    }
}

void ScoresScreenState::initBackGround()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backGroundTexture.loadFromFile(Maps::filePrefix + "scoreBackground.jpg"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backGroundTexture);
}

void ScoresScreenState::initFonts()
{
	if (!this->font.loadFromFile(Maps::filePrefix + "Unique.ttf"))
	{
		throw("ERROR::MAINMENUSTATE;;COULD NOT LOAD FONT");
	}
}

void ScoresScreenState::initKeybinds()
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

void ScoresScreenState::initButtons()
{
	this->buttons["EXIT_STATE"] = new Button(100, 500, 150, 50,
		&this->font, "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

ScoresScreenState::ScoresScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
    this->initHighScores();
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

ScoresScreenState::~ScoresScreenState()
{
	auto it = this-> buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void ScoresScreenState::endState()
{
	std::cout << "Ending ScoresScreenState!\n"; // Debugging
}

void ScoresScreenState::updateInput()
{
	this->checkForQuit();
}

void ScoresScreenState::updateButtons()
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

void ScoresScreenState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void ScoresScreenState::update()
{
	this->updateMousePositions();
	this->updateInput();
	this->updateButtons();
}

void ScoresScreenState::render(sf::RenderWindow* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);
	this->renderButtons(target);
	this->renderScores();
	target->display();
}

void ScoresScreenState::renderScores() {
    sf::Font font;
	font.loadFromFile(Maps::filePrefix + "Unique.ttf");

	sf::Text score;
	int scoreY = 40;
	score.setFont(font);
	score.setCharacterSize(35);
    score.setFillColor(sf::Color::Green);

    ostringstream sout;
    sout << setw(15) << "LEVEL" << setw(15) << "SCORE";
    score.setString(sout.str());
    score.setPosition(sf::Vector2f(300, 100));
    this->window->draw(score);
    for (auto iter = highScores.begin(); iter != highScores.end(); iter++) {
        sout.str("");
        sout.clear();
        sout << setw(20) << iter->second.getLevel() << setw(20) << iter->second.getScore();
        score.setString(sout.str());
        score.setPosition(sf::Vector2f(300, 100 + scoreY));
        this->window->draw(score);
        scoreY += 40;
    }
}


