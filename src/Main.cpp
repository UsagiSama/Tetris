#include "pch.h"

#include <iostream>

#include "App.hpp"

int main()
{
	App *app = new App;

	app->StartApp();

	delete app;

	return 0;
}
