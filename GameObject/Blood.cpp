#include "stdafx.h"
#include "Blood.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SceneDev1.h"

Blood::Blood(const std::string& n)
{
}

Blood::~Blood()
{
}

void Blood::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Blood::Release()
{
	SpriteGo::Release();
}

void Blood::Reset()
{
	SpriteGo::Reset();
}

void Blood::Update(float dt)
{
	SpriteGo::Update(dt);
	delayTime += dt;
	if (delayTime > 3.f)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			sceneDev1->ClearBlood(this);
		}
	}
}

void Blood::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
