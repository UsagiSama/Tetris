#pragma once

#include "Pit.hpp"
#include "Block.hpp"
#include "TextureHolder.hpp"
#include "Menu.hpp"
#include "Score.hpp"

class Game : sf::NonCopyable
{
public:

	Game();

	bool isRunning() const;

	void Render(sf::RenderWindow *window);

	void Event(sf::RenderWindow *window, sf::Event *event);

	void UpDate(const sf::Time &time);

	void Play();

	bool GameOver() { return gameOver; }

	~Game();

private:

	Menu *menu;

	Pit *pit;
	Piece *CurrentPiece;
	Piece *NextPiece;
	sf::Sprite ShowNextPiece;
	TextureHolder Resources;
	Score score;
	sf::Font font;

	bool isRunningGame;
	bool gameOver;

	void loadResources();
	Piece *GenerateNext();
};
