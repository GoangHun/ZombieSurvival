#pragma once
#include "Scene.h"
#include "ObjectPool.h"	

class VertexArrayGo;
class Player;
class Zombie;

class SceneDev1 :
    public Scene
{
protected:
	Player* player;
	VertexArrayGo* background;
	//std::list<Zombie*> zombiePool;
	//std::list<Zombie*> zombies;
	sf::FloatRect wallBounds;
	bool isGameOver;

	ObjectPool<Zombie> poolZombies;


public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;	//씬 전환을 할 때 Init 대신 사용
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	VertexArrayGo* CreateBackground(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize,
		std::string textureId);


	void CreateZombies(int count);
	void SpawnZombies(int count, sf::Vector2f center, float radius);
	void ClearZombies();

	void OnDieZombie(Zombie* zombie);
	void OnDiePlayer();
	

	const std::list<Zombie*>* GetZombieList() const;
};

