#ifndef SCORESSCREENSTATE_H
#define SCORESSCREENSTATE_H
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "Score.h"

class ScoresScreenState : public State
{
private:
	sf::Texture backGroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	map<std::string, Button*> buttons;

	map<int, Score> highScores;

	//Functions
	void initBackGround();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initHighScores();
public:
	ScoresScreenState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~ScoresScreenState();


	//Functions
	void endState();
	void updateInput();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void renderScores();
	void update();
	void render(sf::RenderWindow* target = nullptr);

};
#endif
