#pragma once

#include "Menu.hpp"

class App : sf::NonCopyable
{
private:

	sf::RenderWindow *window;

public:

	App();

	int StartApp();

	~App();

};
