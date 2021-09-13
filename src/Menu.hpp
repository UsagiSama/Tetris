#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
//#include "Game.hpp"

#include <iostream>

class Game;

class Menu : sf::NonCopyable
{
public:

	Menu();

	sf::Sprite strGame(bool contain = false);

	sf::Sprite strExit(bool contain = false);

	void Frame(sf::RenderWindow *window);

	void Event(sf::RenderWindow *window, Game *game);

	bool &isOpen() { return state; }

	~Menu();

private:

	sf::Texture *gameTx;
	sf::Texture *gameTxPress;
	sf::Sprite *gameSp;

	sf::Texture *exitTx;
	sf::Texture *exitTxPress;
	sf::Sprite *exitSp;

	bool state;             // This variable show state of menu. It is 1 if menu is open, if is closed 0
};
