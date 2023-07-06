#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneDev1.h"
#include "Bullet.h"
#include "VertexArrayGo.h"
#include "Utils.h"

Player::Player(const std::string tId, const std::string n) : SpriteGo(tId, n)
{
	
}

void Player::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);

	ObjectPool<Bullet>* ptr = &poolBullets;
	poolBullets.OnCreate = [ptr](Bullet* bullet) {
		bullet->textureId = "graphics/bullet.png";
		bullet->pool = ptr;
	};
	poolBullets.Init();
}

void Player::Release()
{
	SpriteGo::Release();

	poolBullets.Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	isAlive = true;
	hp = maxHp;

	for (auto bullet : poolBullets.GetUseList())
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(bullet);
	}

	poolBullets.Clear();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	//회전
	look = Utils::Normalize(mousePos - playerScreenPos);
	sprite.setRotation(Utils::Angle(look));

	//이동
	direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

	SetPosition(position + direction * speed * dt);
	
	//벽충돌
	if (!wallBounds.contains(position))
	{
		position = Utils::Clamp(position, wallBoundsLT, wallBoundsRB);	
	}
	sprite.setPosition(position);

	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		Bullet* bullet = poolBullets.Get();
		bullet->Init();
		bullet->Reset();
		bullet->Fire(GetPosition(), look, 1000.f);
		
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			bullet->SetZombieList(sceneDev1->GetZombieList());
			sceneDev1->AddGo(bullet);
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

//void Player::OnHitZombie(int damage)
//{
//	hp -= damage;
//	if (hp <= 0)
//	{
//		Scene* scene = SCENE_MGR.GetCurrScene();
//		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
//		if (sceneDev1 != nullptr)
//		{
//			sceneDev1->OnDiePlayer();
//		}
//	}
//}

void Player::SetBackground(VertexArrayGo* background)
{
	this->background = background;
}

//void Player::OnCollisionWall()
//{
//	sf::FloatRect wall = background->vertexArray.getBounds();
//	
//	if (wall.top > position.y)
//	{
//		SetPosition(position.x, wall.top);
//	}
//	if (wall.top + wall.height < position.y)
//	{
//		SetPosition(position.x, wall.top + wall.height);
//	}
//	if (wall.left > position.x)
//	{
//		SetPosition(wall.left, position.y);
//	}
//	if (wall.left + wall.width < position.x)
//	{
//		SetPosition(wall.left + wall.width, position.y);
//	}
//}

void Player::SetWallBounds(const sf::FloatRect& bounds)
{
	wallBounds = bounds;
	wallBoundsLT = { wallBounds.left, wallBounds.top };
	wallBoundsRB = { wallBounds.left + wallBounds.width, wallBounds.top + wallBounds.height };
}

void Player::OnHitted(int damage)
{
	if (!isAlive)
		return;

	hp = std::max(hp - damage, 0);
	if (hp == 0)
	{
		OnDie();
	}
}

void Player::OnDie()
{
	isAlive = false;
	std::cout << "Player Die" << std::endl;

	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	if (sceneDev1 != nullptr)
	{
		sceneDev1->OnDiePlayer();
	}
}
