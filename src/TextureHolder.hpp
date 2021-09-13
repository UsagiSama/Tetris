#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class TextureHolder
{
public:

	void Load(sf::IntRect rect, std::string path);

	void Load(std::string path);

	sf::Sprite &GetSprite(int index);

	sf::IntRect &GetRect(int index);

	sf::Texture &GetTexture(int index);

private:

	std::vector<sf::Texture> TextureArray;
	std::vector<sf::IntRect> RectArray;
	std::vector<sf::Sprite> SpriteArray;
};
