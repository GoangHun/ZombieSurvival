#pragma once
#include "SpriteGo.h"
class Blood :
    public SpriteGo
{
protected:
	float delayTime = 0.f;

public:
	Blood(const std::string& n = "");
	virtual ~Blood() override;

	virtual void Init()  override;
	virtual void Release()  override;
	virtual void Reset()  override;

	virtual void Update(float dt)  override;
	virtual void Draw(sf::RenderWindow& window)  override;

};

