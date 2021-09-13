#include "pch.h"

#include "TextureHolder.hpp"

void TextureHolder::Load(sf::IntRect rect, std::string path)
{
	sf::Image img;

	img.loadFromFile(path);

	sf::Texture tx;

	tx.loadFromImage(img);

	sf::Sprite sp;

	sp.setTexture(tx);
	sp.setTextureRect(rect);

	TextureArray.push_back(tx);
	RectArray.push_back(rect);
	SpriteArray.push_back(sp);
}

void TextureHolder::Load(std::string path)
{
	sf::Texture tx;

	tx.loadFromFile(path);

	sf::Sprite sp;

	sp.setTexture(tx);

	TextureArray.push_back(tx);
	SpriteArray.push_back(sp);
}

sf::Texture &TextureHolder::GetTexture(int index)
{
	return TextureArray[index];
}

sf::IntRect &TextureHolder::GetRect(int index)
{
	return RectArray[index];
}

sf::Sprite &TextureHolder::GetSprite(int index)
{
	return SpriteArray[index];
}
