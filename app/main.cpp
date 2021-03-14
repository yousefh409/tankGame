#include <iostream>
#include <string>
#include <ctime>
#include "Game.h"


int main()
{
	srand(time(0));
	Game game;
	game.run();
}
