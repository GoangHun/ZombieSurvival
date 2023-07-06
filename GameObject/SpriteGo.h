#pragma once
#include "GameObject.h"

class SpriteGo :
    public GameObject
{
protected:

public:
	sf::Sprite sprite;
	std::string textureId;


	SpriteGo(const std::string tId = "", const std::string n = "");
	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f& p) override;
	virtual void SetPosition(float x, float y) override;

	virtual void SetOrigin(Origins origin) override;
	virtual void SetOrigin(float x, float y) override;

	virtual void Init()  override;	//생성자 역할
	virtual void Release()  override;	//소멸자 역할
	virtual void Reset()  override;	//초기화 역할

	virtual void Update(float dt)  override;
	virtual void Draw(sf::RenderWindow& window)  override;
};

