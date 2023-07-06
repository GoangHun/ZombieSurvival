#include "stdafx.h"
#include "Crosshair.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

Crosshair::Crosshair(const std::string tId, const std::string n) : SpriteGo(tId, n)
{
}

void Crosshair::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Crosshair::Release()
{
	SpriteGo::Release();
}

void Crosshair::Reset()
{
	SpriteGo::Reset();
}

void Crosshair::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);

	SetPosition(mouseWorldPos);
}

void Crosshair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
