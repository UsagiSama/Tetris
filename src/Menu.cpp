#include "pch.h"

#include "Menu.hpp"
#include "Game.hpp"
#include <iostream>

Menu::Menu() : state(true)
{
	sf::Image image;
	image.loadFromFile("images/GameR.png");

	//////////////////////////////////////////////////////////////////
	////////// set Sprite Game Red///////////////
	try { gameTx = new sf::Texture; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	gameTx->loadFromImage(image);

	try { gameSp = new sf::Sprite; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	gameSp->setTexture(*gameTx);
	gameSp->setPosition(53, 50);
	//////////////////////////////////////////////////////////////////
	////////// set Sprite Exit Red///////////////
	
	image.loadFromFile("images/ExitR.png");

	try { exitTx = new sf::Texture; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	exitTx->loadFromImage(image);

	try { exitSp = new sf::Sprite; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	exitSp->setTexture(*exitTx);
	exitSp->setPosition(82, 150);

	//////////////////////////////////////////////////////////////////
	/////////// Load White texture "Game"///////////////

	image.loadFromFile("images/GameW.png");

	try { gameTxPress = new sf::Texture; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	gameTxPress->loadFromImage(image);

	//////////////////////////////////////////////////////////////////
	/////////// Load White texture "Exit"///////////////

	image.loadFromFile("images/ExitW.png");

	try { exitTxPress = new sf::Texture; }
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	exitTxPress->loadFromImage(image);
}

sf::Sprite Menu::strGame(bool contain)
{
	if (contain == true) { gameSp->setTexture(*gameTxPress); }
	else { gameSp->setTexture(*gameTx); }

	return *gameSp;
}

sf::Sprite Menu::strExit(bool contain)
{
	if (contain == true) { exitSp->setTexture(*exitTxPress); }
	else { exitSp->setTexture(*exitTx); }

	return *exitSp;
}

void Menu::Frame(sf::RenderWindow *window)
{
	bool str1, str2;

	str1 = str2 = false;
	//53, 50, 194, 52
	if (sf::IntRect(53, 50, 194, 52).contains(sf::Mouse::getPosition(*window))) { str1 = true; } // if to bring mouse on "Game" will change to white     
	else { str1 = false; } // Color "Game" change to Red
	window->draw(this->strGame(str1));

	if (sf::IntRect(82, 150, 135, 53).contains(sf::Mouse::getPosition(*window))) { str2 = true; } // if to bring mouse on "Exit" will change to white  
	else { str2 = false; } // Color "Exit" change to Red
	window->draw(this->strExit(str2));
}

void Menu::Event(sf::RenderWindow *window, Game *game)
{
	int numKey = 0;

	if (sf::IntRect(53, 50, 194, 52).contains(sf::Mouse::getPosition(*window))) { numKey = 1; }
	else if (sf::IntRect(82, 150, 135, 53).contains(sf::Mouse::getPosition(*window))) { numKey = 2; }
	else { numKey = 0; }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (numKey == 0) {/* Nothing happening */ }
		if (numKey == 1) 
		{ 			
			this->state = false;
			game->Play(); 
		}
	
		if (numKey == 2) { window->close();  this->state = false; }
	}
}

Menu::~Menu()
{
	delete gameTx;
	delete gameTxPress;
	delete gameSp;
	delete exitTx;
	delete exitTxPress;
	delete exitSp;
}
