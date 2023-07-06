#include "stdafx.h"
#include "TextGo.h"
#include "Utils.h"
#include <sstream>

TextGo::TextGo(const std::string n) : GameObject(n)
{
}

TextGo::~TextGo()
{
}

void TextGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	text.setPosition(p);
}

void TextGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	text.setPosition(position);
}

void TextGo::SetOrigin(Origins origin)
{
	Utils::SetOrigin(text, origin);
}

void TextGo::SetOrigin(float x, float y)
{
	text.setOrigin(x, y);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
}

void TextGo::Update(float dt)
{

}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGo::SetText( const std::string str, int size, sf::Color color, float x, float y)
{
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	Utils::SetOrigin(text, Origins::TL);
	text.setPosition(x, y);
}

void TextGo::SetText(std::stringstream ss, int size, sf::Color color, float x, float y)
{
	text.setString(ss.str());
	text.setCharacterSize(size);
	text.setFillColor(color);
	Utils::SetOrigin(text, Origins::MC);
	text.setPosition(x, y);
}
