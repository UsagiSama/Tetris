#include "pch.h"

#include "Block.hpp"


///////////////////////////////////////////////////////
//////////////////////class Block//////////////////////

Block::Block(sf::Texture *texture, sf::IntRect rect, const sf::Vector2f &pixelPosition, const PitCoordinates &coords) 
	: BlockSp(*texture), coords(coords)
{
	BlockSp.setPosition(sf::Vector2f(pixelPosition));
	BlockSp.setTextureRect(rect);
}

Block::Block(sf::Sprite &sprite, const sf::Vector2f &pixelPosition, const PitCoordinates &coords)
	: BlockSp(sprite), coords(coords)
{
	BlockSp.setPosition(sf::Vector2f(pixelPosition));
}

void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(BlockSp, states);
}

sf::Sprite &Block::Sp()
{
	return BlockSp;
}

//const PitCoordinates &Block::Coordinates() const
//{
//	return coords;
//}

PitCoordinates &Block::Coordinates()
{
	return coords;
}

const sf::Vector2f &Block::GetPosition() const
{
	return BlockSp.getPosition();
}

void Block::MoveDown()
{
	if (coords.row == Pit::HEIGHT - 1) { return; }

	++coords.row;
	sf::Vector2f currPos = BlockSp.getPosition();

	BlockSp.setPosition(currPos.x, currPos.y + step);
}

///////////////////////////////////////////////////////
//////////////////////class Piece//////////////////////


Piece::Piece(sf::Sprite &sprite, std::array<PitCoordinates, 4> coords) : state(true)
{
	for (int i = 0; i < 4; ++i)
	{
		Blocks[i] = new Block(sprite, sf::Vector2f((coords[i].column * Block::step) + 1, (coords[i].row * Block::step) + 1), coords[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) { RotatePositions[i][j]; }
	}
}

Piece::Piece(sf::Texture &texture, sf::IntRect rect, std::array<PitCoordinates, 4> coords, std::array<std::array<bool, 4>, 4> rotatePositions) 
	: state(true)
{
	for (int i = 0; i < 4; ++i)
	{
		Blocks[i] = new Block(&texture, rect, sf::Vector2f((coords[i].column * Block::step) + 1, (coords[i].row * Block::step) + 1), coords[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j) { RotatePositions[i][j] = rotatePositions[i][j]; }
	}
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int i = 0; i < 4; ++i) { target.draw(*(Blocks[i]), states); }
}

void Piece::MoveDown(Pit *pit)
{
	if (
		(Blocks[0]->Coordinates().row == Pit::HEIGHT - 1) ||
		(Blocks[1]->Coordinates().row == Pit::HEIGHT - 1) ||
		(Blocks[2]->Coordinates().row == Pit::HEIGHT - 1) ||
		(Blocks[3]->Coordinates().row == Pit::HEIGHT - 1) 
		) { state = 0; return; }
	
	if (
		(Blocks[0]->Coordinates().row >= 0) ||
		(Blocks[1]->Coordinates().row >= 0) ||
		(Blocks[2]->Coordinates().row >= 0) ||
		(Blocks[3]->Coordinates().row >= 0)
		)
	{
		if (
			(pit->GetGameMap()[Blocks[0]->Coordinates().row + 1][Blocks[0]->Coordinates().column] != NULL) ||
			(pit->GetGameMap()[Blocks[1]->Coordinates().row + 1][Blocks[1]->Coordinates().column] != NULL) ||
			(pit->GetGameMap()[Blocks[2]->Coordinates().row + 1][Blocks[2]->Coordinates().column] != NULL) ||
			(pit->GetGameMap()[Blocks[3]->Coordinates().row + 1][Blocks[3]->Coordinates().column] != NULL)
			) { state = 0; return; }
	}

	for (int i = 0; i < 4; ++i)
	{		
		Blocks[i]->MoveDown();
	}
}

void Piece::MoveRight(Pit *pit)
{
	if (
		(Blocks[0]->Coordinates().column == Pit::WIDTH - 1) ||
		(Blocks[1]->Coordinates().column == Pit::WIDTH - 1) ||
		(Blocks[2]->Coordinates().column == Pit::WIDTH - 1) ||
		(Blocks[3]->Coordinates().column == Pit::WIDTH - 1)
		) { return; }
	
	if (
		(Blocks[0]->Coordinates().row >= 0) &&
		(Blocks[1]->Coordinates().row >= 0) &&
		(Blocks[2]->Coordinates().row >= 0) &&
		(Blocks[3]->Coordinates().row >= 0)
		)
	{
		if (
			(pit->GetGameMap()[Blocks[0]->Coordinates().row][Blocks[0]->Coordinates().column + 1] != NULL) ||
			(pit->GetGameMap()[Blocks[1]->Coordinates().row][Blocks[1]->Coordinates().column + 1] != NULL) ||
			(pit->GetGameMap()[Blocks[2]->Coordinates().row][Blocks[2]->Coordinates().column + 1] != NULL) ||
			(pit->GetGameMap()[Blocks[3]->Coordinates().row][Blocks[3]->Coordinates().column + 1] != NULL)
			) { return; }
	}
	
	for (int i = 0; i < 4; ++i)
	{
		++Blocks[i]->Coordinates().column;

		sf::Vector2f currPos = Blocks[i]->GetPosition();

		Blocks[i]->Sp().setPosition(currPos.x + Block::step, currPos.y);
	}
}

void Piece::MoveLeft(Pit *pit)
{
	if (
		(Blocks[0]->Coordinates().column == 0) ||
		(Blocks[1]->Coordinates().column == 0) ||
		(Blocks[2]->Coordinates().column == 0) ||
		(Blocks[3]->Coordinates().column == 0)
		) { return; }

	if (
		(Blocks[0]->Coordinates().row >= 0) &&
		(Blocks[1]->Coordinates().row >= 0) &&
		(Blocks[2]->Coordinates().row >= 0) &&
		(Blocks[3]->Coordinates().row >= 0)
		)
	{
		if (
			(pit->GetGameMap()[Blocks[0]->Coordinates().row][Blocks[0]->Coordinates().column - 1] != NULL) ||
			(pit->GetGameMap()[Blocks[1]->Coordinates().row][Blocks[1]->Coordinates().column - 1] != NULL) ||
			(pit->GetGameMap()[Blocks[2]->Coordinates().row][Blocks[2]->Coordinates().column - 1] != NULL) ||
			(pit->GetGameMap()[Blocks[3]->Coordinates().row][Blocks[3]->Coordinates().column - 1] != NULL)
			) { return; }
	}

	for (int i = 0; i < 4; ++i)
	{
		--Blocks[i]->Coordinates().column;

		sf::Vector2f currPos = Blocks[i]->GetPosition();

		Blocks[i]->Sp().setPosition(currPos.x - Block::step, currPos.y);
	}
}

void Piece::Rotate(Pit *pit, bool direction)
{
	auto GetCoords = [&]
		(
			std::array<std::array<bool, 4>, 4> map,
			std::array<PitCoordinates, 4> coords
		) -> std::array<PitCoordinates, 4>
	{
		for (int i = 0, k = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j) { if (map[i][j]) { coords[k] = PitCoordinates(i, j); ++k; } }
		}

		return coords;
	};

	std::array<std::array<bool, 4>, 4> Tarnsp = RotatePositions;
	std::array<PitCoordinates, 4> prevCoords, currCoords, difference;

	/////////////////////////////////////////////////////////////////
	if (direction)
	{
		for (int i = 3, k = 0; i >= 0; --i, ++k)
		{
			for (int j = 0; j < 4; ++j)
			{
				Tarnsp[j][k] = RotatePositions[i][j];
			}
		}
	}
	else
	{
		for (int i = 3, k = 0; i >= 0; --i, ++k)
		{
			for (int j = 0; j < 4; ++j)
			{
				Tarnsp[k][j] = RotatePositions[j][i];
			}
		}
	}
	/////////////////////////////////////////////////////////////////
	prevCoords = GetCoords(RotatePositions, prevCoords);
	currCoords = GetCoords(Tarnsp, currCoords);

	for (int i = 0; i < 4; ++i)
	{
		difference[i].row = prevCoords[i].row - currCoords[i].row;
		difference[i].column = prevCoords[i].column - currCoords[i].column;
	}

	///////////////////////////////////////////////////////////////////////
	int r, c;

	for (int i = 0; i < 4; ++i)
	{
		r = Blocks[i]->Coordinates().row - difference[i].row;
		c = Blocks[i]->Coordinates().column - difference[i].column;

		if ((r > Pit::HEIGHT - 1) || (r < 0) || (c > Pit::WIDTH - 1) || (c < 0)) { return; }
		if (pit->GetGameMap()[r][c] != NULL) { return; }
	}

	for (int i = 0; i < 4; ++i)
	{
		Blocks[i]->Coordinates().row -= difference[i].row;
		Blocks[i]->Coordinates().column -= difference[i].column;

		Blocks[i]->Sp().setPosition(sf::Vector2f((Blocks[i]->Coordinates().column * Block::step) + 1, 
			(Blocks[i]->Coordinates().row * Block::step) + 1));
	}	

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			RotatePositions[i][j] = Tarnsp[i][j];
		}
	}
}

Block *&Piece::operator[](int index)
{
	return Blocks[index];
}

Piece::~Piece()
{
	for (int i = 0; i < 4; ++i)
	{
		if (Blocks[i] != NULL) { delete Blocks[i]; }
	}
}
