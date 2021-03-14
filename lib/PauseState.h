#pragma once
#include "State.h"
#include "Button.h"
class PauseState :public State
{
private:
	sf::Texture backGroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;
	//Functions
	void initBackGround();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	PauseState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~PauseState();

	//Functions
	void endState();
	void updateInput();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void update();
	void render(sf::RenderWindow* target = nullptr);
};

