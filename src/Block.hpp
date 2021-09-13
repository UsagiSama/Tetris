#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>
#include <array>

#include "Pit.hpp"

class Block : public sf::Drawable
{
public:

	static const int step = 18;

	Block(sf::Texture *texture, sf::IntRect rect, const sf::Vector2f &pixelPosition, const PitCoordinates &coords);

	Block(sf::Sprite &sprite, const sf::Vector2f &pixelPosition, const PitCoordinates &coords);

	const sf::Vector2f &GetPosition() const;

	sf::Sprite &Sp();

	PitCoordinates &Coordinates();

	void MoveDown();

private:

	sf::Sprite BlockSp;
	PitCoordinates coords;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class Piece : public sf::Drawable
{
public:

	void MoveDown(Pit *pit);

	void MoveLeft(Pit *pit);
	
	void MoveRight(Pit *pit);

	void Rotate(Pit *pit, bool direction); // direction - if true to right, else to left

	Block *&operator[](int index);

	bool PieceState() const { return state; }

	Piece(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords);

	Piece(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords, std::array<std::array<bool, 4>, 4> rotatePositions);

	~Piece();

private:

	bool state;

	std::array<std::array<bool, 4>, 4> RotatePositions;
	std::array<Block*, 4> Blocks;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class I : public Piece
{
public:

	I(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	I(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords = 
		{ 
			PitCoordinates(-1, 3), 
			PitCoordinates(-1, 4), 
			PitCoordinates(-1, 5), 
			PitCoordinates(-1, 6) 
		},
		std::array<std::array<bool, 4>, 4> rotatePositions = 
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class J : public Piece
{
public:

	J(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	J(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords =
		{
			PitCoordinates(-2, 3),
			PitCoordinates(-1, 3),
			PitCoordinates(-1, 4),
			PitCoordinates(-1, 5)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 1,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class L : public Piece
{
public:

	L(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	L(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords = 
		{
			PitCoordinates(-2, 5),
			PitCoordinates(-1, 3),
			PitCoordinates(-1, 4),
			PitCoordinates(-1, 5)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 0, 0, 1,
			0, 1, 1, 1,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class O : public Piece
{
public:

	O(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	O(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords = 
		{
			PitCoordinates(-2, 4),
			PitCoordinates(-2, 5),
			PitCoordinates(-1, 4),
			PitCoordinates(-1, 5)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class S : public Piece
{
public:

	S(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	S(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords = 
		{
			PitCoordinates(-2, 4),
			PitCoordinates(-2, 5),
			PitCoordinates(-1, 3),
			PitCoordinates(-1, 4)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 0, 1, 1,
			0, 1, 1, 0,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class T : public Piece
{
public:

	T(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	T(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords =
		{
			PitCoordinates(-2, 5),
			PitCoordinates(-1, 4),
			PitCoordinates(-1, 5),
			PitCoordinates(-1, 6)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 1,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};

class Z : public Piece
{
public:

	Z(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : Piece(sprite, coords) {}

	Z(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords = 
		{
			PitCoordinates(-2, 4),
			PitCoordinates(-2, 5),
			PitCoordinates(-1, 5),
			PitCoordinates(-1, 6)
		},
		std::array<std::array<bool, 4>, 4> rotatePositions =
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 1,
			0, 0, 0, 0
		})
		: Piece(texture, rect, coords, rotatePositions) {}
};
