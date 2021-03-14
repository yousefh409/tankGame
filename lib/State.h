#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Sprite.h"
#include "MainTank.h"
#include "SecondaryTank.h"
#include "Bullet.h"
#include "Maps.h"
#include "Wall.h"
#include "EnemyTank.h"
#include<vector>
#include <stack>
#include <cmath>
#include <fstream>

class State
{
private:

protected:
	std::stack<State*>* states; // Pointer to a stack of (stateStacks) used so eachState can access a universal state stack
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//resources
	std::vector<sf::Texture> textures;

	//Functins
	virtual void initKeybinds() = 0;


public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//functions
	const bool& getQuit() const;
	virtual void update() = 0;
	virtual void updateInput() = 0;
	virtual void updateMousePositions();
	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void render(sf::RenderWindow* target = nullptr) = 0;
};

#endif
