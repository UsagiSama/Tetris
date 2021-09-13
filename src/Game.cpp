#include "pch.h"

#include "Game.hpp"

#include <random>
#include <cstdlib>

#pragma warning (disable : 4996)

const float PIECE_MOVE_TIME = 0.5;

Game::Game() : isRunningGame(false), gameOver(false)
{
	loadResources();

	menu = new Menu(); 
	pit = new Pit(Resources.GetTexture(7));
	CurrentPiece = GenerateNext();
	NextPiece = GenerateNext();
	ShowNextPiece.setPosition(208, 48);
}

bool Game::isRunning() const
{
	return isRunningGame;
}

void Game::loadResources()
{
	Resources.Load(sf::IntRect(0, 0, 17, 17), "images/tiles.png");     // Dark - blue    index: 0
	Resources.Load(sf::IntRect(18, 0, 17, 17), "images/tiles.png");    // Purple         index: 1
	Resources.Load(sf::IntRect(36, 0, 17, 17), "images/tiles.png");    // Red            index: 2
	Resources.Load(sf::IntRect(54, 0, 17, 17), "images/tiles.png");    // Green          index: 3
	Resources.Load(sf::IntRect(72, 0, 17, 17), "images/tiles.png");    // Yellow         index: 4
	Resources.Load(sf::IntRect(90, 0, 17, 17), "images/tiles.png");    // Blue           index: 5
	Resources.Load(sf::IntRect(108, 0, 17, 17), "images/tiles.png");   // Orange         index: 6
	Resources.Load("images/Pit.png");                                  // Pit            index: 7
	Resources.Load("images/i.png");                                    // I              index: 8
	Resources.Load("images/j.png");                                    // J              index: 9
	Resources.Load("images/l.png");                                    // L              index: 10
	Resources.Load("images/o.png");                                    // O              index: 11
	Resources.Load("images/s.png");                                    // S              index: 12
	Resources.Load("images/t.png");                                    // T              index: 13
	Resources.Load("images/z.png");                                    // Z              index: 14
	font.loadFromFile("images/11776.otf");
}

void Game::Render(sf::RenderWindow *window)
{
	sf::Text text("", font, 32);
	char str[32];

	itoa(score.GetScore(), str, 10);
	text.setString(str);
	text.setPosition(192, 125);

	if (menu->isOpen()) { menu->Frame(window); }
	else
	{
		window->draw(*pit);
		window->draw(*CurrentPiece);
		window->draw(text);
		window->draw(ShowNextPiece);
	}
}

void Game::Event(sf::RenderWindow *window, sf::Event *event)
{
	if (menu->isOpen()) { menu->Event(window, this); }

	if (!gameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { CurrentPiece->MoveDown(pit); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { CurrentPiece->MoveRight(pit); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { CurrentPiece->MoveLeft(pit); }
		if (event->type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { CurrentPiece->Rotate(pit, false); } // Left rotate
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { CurrentPiece->Rotate(pit, true); }  // Right rotate
		}
	}
}

Piece *Game::GenerateNext()
{
	Piece *piece;

	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution<> dist(1, 7);

	int choice = dist(gen);

	//int choice = 1;

	switch (choice)
	{
	case 1:

		piece = new I(Resources.GetTexture(5), Resources.GetRect(5));
		ShowNextPiece.setTexture(Resources.GetTexture(8));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 73, 19));
		return piece;

		break;

	case 2:

		piece = new J(Resources.GetTexture(0), Resources.GetRect(0));
		ShowNextPiece.setTexture(Resources.GetTexture(9));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 55, 37));
		return piece;

		break;

	case 3:

		piece = new L(Resources.GetTexture(6), Resources.GetRect(6));
		ShowNextPiece.setTexture(Resources.GetTexture(10));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 55, 37));
		return piece;

		break;

	case 4:

		piece = new O(Resources.GetTexture(4), Resources.GetRect(4));
		ShowNextPiece.setTexture(Resources.GetTexture(11));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 37, 37));
		return piece;

		break;

	case 5:

		piece = new S(Resources.GetTexture(3), Resources.GetRect(3));
		ShowNextPiece.setTexture(Resources.GetTexture(12));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 55, 37));
		return piece;

		break;

	case 6:

		piece = new T(Resources.GetTexture(1), Resources.GetRect(1));
		ShowNextPiece.setTexture(Resources.GetTexture(13));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 55, 37));
		return piece;

		break;

	case 7:

		piece = new Z(Resources.GetTexture(2), Resources.GetRect(2));
		ShowNextPiece.setTexture(Resources.GetTexture(14));
		ShowNextPiece.setTextureRect(sf::IntRect(0, 0, 55, 37));
		return piece;

		break;

	default:

		std::cout << "This unreachable" << std::endl;
		return NULL;

		break;
	}
}

void Game::UpDate(const sf::Time &time)
{
	static float timeSinceLastPieceMove = 0;
	timeSinceLastPieceMove += time.asSeconds();

	if (!gameOver)
	{
		if (timeSinceLastPieceMove >= PIECE_MOVE_TIME)
		{
			if (CurrentPiece->PieceState())
			{
				CurrentPiece->MoveDown(pit);
				timeSinceLastPieceMove = 0;
			}
		}

		if (!CurrentPiece->PieceState())
		{
			if (!pit->Init(CurrentPiece))
			{
				gameOver = true;
			}

			delete CurrentPiece;

			CurrentPiece = NextPiece;
			NextPiece = GenerateNext();
		}

		int numRows = pit->DeleteFullRows();
		
		switch (numRows)
		{
		case 1:
			score += 100;
			break;

		case 2:
			score += 300;
			break;

		case 3:
			score += 700;
			break;

		case 4:
			score += 1500;
			break;

		default:
			break;
		}

	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameOver = true;
			isRunningGame = false;
			pit->Clear();
			score.Reset();

			menu->isOpen() = true;
		}
	}
}

void Game::Play()
{
	isRunningGame = true;
	gameOver = false;
}

Game::~Game()
{
	if (NextPiece != NULL) { delete NextPiece; }
	if (CurrentPiece != NULL) { delete CurrentPiece; }
    delete pit; 
	delete menu;
}
