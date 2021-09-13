#pragma once

class Score
{
public:

	Score() : score(0) {}

	void operator+=(int i) { score += i; }

	void Reset() { score = 0; }

	int GetScore() { return score; }

private:

	int score;

};
