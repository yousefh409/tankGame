#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "Score.h"

class InstructionScreenState : public State
{
private:
	sf::Texture backGroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	map<std::string, Button*> buttons;

	map<string, string> instructionKeys;
    map<string, string> bulletDescrips;
	string instructionDescription;


	//Functions
	void initBackGround();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initInstructions();
public:
	InstructionScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~InstructionScreenState();


	//Functions
	void endState();
	void updateInput();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void renderInstructions();
	void update();
	void render(sf::RenderWindow* target = nullptr);

};
