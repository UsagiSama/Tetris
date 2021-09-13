#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
#include <array>

class Block;
class Piece;

struct PitCoordinates
{
	int row;
	int column;

	PitCoordinates(int row = 0, int column = 0) : row(row), column(column) {}
};

class Pit : public sf::Drawable, sf::NonCopyable
{
public:

	static const int HEIGHT = 20;
	static const int WIDTH = 10;

	Pit(sf::Texture &texture);

	bool Init(Piece *piece);

	void Clear();

	std::array<std::array<Block*, WIDTH>, HEIGHT> GetGameMap() { return GameMap; }

	int DeleteFullRows();

	~Pit();

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Sprite PitSp;	
	std::array<std::array<Block*, WIDTH>, HEIGHT> GameMap;
	std::array<bool, HEIGHT> fullRows;

	void DeleteRow(int i);
};

