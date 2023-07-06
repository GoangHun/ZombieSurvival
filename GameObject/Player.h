#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"	

class Bullet;
class VertexArrayGo;

class Player :
    public SpriteGo
{
protected:
	sf::Vector2f look;
	sf::Vector2f direction;
	float speed = 150.f;
	VertexArrayGo* background = nullptr;

	sf::FloatRect wallBounds;
	sf::Vector2f wallBoundsLT;
	sf::Vector2f wallBoundsRB;

	int maxHp = 100;
	int hp = 0;

	ObjectPool<Bullet> poolBullets;

public:
	Player(const std::string tId = "", const std::string n = "");

	virtual void Init()  override;	
	virtual void Release()  override;	
	virtual void Reset()  override;	

	virtual void Update(float dt)  override;
	virtual void Draw(sf::RenderWindow& window)  override;

	//void OnHitZombie(int damage);
	void SetBackground(VertexArrayGo* background);
	//void OnCollisionWall();

	void SetWallBounds(const sf::FloatRect& bounds);

	bool isAlive = false;

	void OnHitted(int damage);
	void OnDie();
};

