#pragma once
#include "SpriteGo.h"
class Crosshair :
    public SpriteGo
{
protected:
public:
	Crosshair(const std::string tId = "", const std::string n = "");

	virtual void Init()  override;
	virtual void Release()  override;
	virtual void Reset()  override;

	virtual void Update(float dt)  override;
	virtual void Draw(sf::RenderWindow& window)  override;
};

