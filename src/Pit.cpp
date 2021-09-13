#include "pch.h"

#include "Pit.hpp"
#include "Block.hpp"


Pit::Pit(sf::Texture &texture) : PitSp(texture)
{
	PitSp.setPosition(0, 0);

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j) { GameMap[i][j] = NULL; }

		fullRows[i] = false;
	}
}

void Pit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(PitSp, states);
	
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if ((GameMap[i][j]) != NULL) { target.draw(*((GameMap)[i][j]), states); }
		}
	}
}

bool Pit::Init(Piece *piece)
{
	bool b = true;

	for (int i = 0; i < 4; ++i)
	{	
		if ((*(*piece)[i]).Coordinates().row < 1) { b = false; }

		if ((*(*piece)[i]).Coordinates().row >= 0)
		{
			GameMap[(*(*piece)[i]).Coordinates().row][(*(*piece)[i]).Coordinates().column] = (*piece)[i];
			(*piece)[i] = NULL;
		}
	}

	return b;
}

void Pit::DeleteRow(int i)
{
	for (int j = 0; j < WIDTH; ++j)
	{
		delete GameMap[i][j];
		GameMap[i][j] = NULL;
	}
	
	for (int j = i - 1; j >= 0; --j)
	{
		for (int k = 0; k < WIDTH; ++k)
		{
			if (GameMap[j][k] != NULL) 
			{
				GameMap[j + 1][k] = GameMap[j][k];
				GameMap[j][k]->MoveDown();
				GameMap[j][k] = NULL;
			}
		}
	}
}

int Pit::DeleteFullRows()
{
	// Lambda function that return fill array fullRows and to return number full rows
	auto CheckFullRows = [&]() -> int
	{
		int blocksInRow;
		int NumberOfFullRows = 0;

		for (int i = 0; i < HEIGHT; ++i)
		{
			blocksInRow = 0;

			for (int j = 0; j < WIDTH; ++j) { if ((GameMap[i][j]) != NULL) { ++blocksInRow; } }

			if (blocksInRow == WIDTH)
			{
				fullRows[i] = true;
				++NumberOfFullRows;
			}
		}

		return NumberOfFullRows;
	};
	/////////////////////////////////////////////////////////////////////////////////

	int NumberOfFullRows = CheckFullRows();

	if (!NumberOfFullRows) { return 0; }

	for (int i = 0; i < HEIGHT; ++i)
	{
		if (fullRows[i]) 
		{
			DeleteRow(i);
			fullRows[i] = false;
		}
	}

	return NumberOfFullRows;
}

void Pit::Clear()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if ((GameMap[i][j]) != NULL) 
			{
				delete GameMap[i][j]; 
				GameMap[i][j] = NULL;
			}

		}
	}
}

Pit::~Pit()
{
	Clear();
}
