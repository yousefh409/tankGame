#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "State.h"
#include "Button.h"
#include "GameState.h"

class MainMenuState :
	public State
{
private:
	sf::Texture backGroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;
    sf::Clock clock;
    sf::Music sound;
    sf::Time lastSoundTrigger;
	//Functions
	void initBackGround();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();


	//Functions
	void endState();
	void updateInput();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void update();
	void render(sf::RenderWindow* target = nullptr);
	void drawTitle();
};
#endif // MAINMENUSTATE_H

