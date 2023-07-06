#include "stdafx.h"
#include "SceneDev1.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "VertexArrayGo.h"
#include "Framework.h"
#include "Zombie.h"
#include "SceneMgr.h"
#include "Crosshair.h"

SceneDev1::SceneDev1() : Scene(SceneId::Title), player(nullptr)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/player.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/background_sheet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/bloater.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/chaser.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/crawler.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/bullet.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/crosshair.png"));
}

SceneDev1::~SceneDev1()
{
	Release();
}

void SceneDev1::Init()
{
	Release();
	//FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;

	worldView.setSize(windowSize);
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	sf::Vector2f tileWorldSize = { 50.f, 50.f };
	sf::Vector2f tileTexSize = { 50.f, 50.f };

	player = (Player*)AddGo(new Player("graphics/player.png", "Player"));

	background = CreateBackground({ 10, 10 }, tileWorldSize, tileTexSize,
		"graphics/background_sheet.png");
	background->sortLayer = -1;
	background->SetOrigin(Origins::MC);
	background->SetPosition(0.f, 0.f);
	AddGo(background);

	wallBounds = background->vertexArray.getBounds();
	wallBounds.width -= tileWorldSize.x * 2.f;
	wallBounds.height -= tileWorldSize.y * 2.f;
	wallBounds.left += tileWorldSize.x;
	wallBounds.top += tileWorldSize.y;
	player->SetWallBounds(wallBounds);

	//player->SetBackground(background);

	poolZombies.OnCreate = [this](Zombie* zombie) {
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		zombie->SetType(zombieType);
		zombie->SetPlayer(player);
	};

	poolZombies.Init();
	
	for (auto go : gameObjects)
	{
		go->Init();
	}


}

void SceneDev1::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}

	poolZombies.Release();
}

void SceneDev1::Enter()
{
	Scene::Enter();
	isGameOver = false;
	worldView.setCenter(0.f, 0.f);
	player->SetPosition(0.f, 0.f);

}

void SceneDev1::Exit()
{
	ClearZombies();
	player->Reset();

	Scene::Exit();

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (isGameOver)
	{
		SCENE_MGR.ChangeScene(sceneId);
	}

	worldView.setCenter(player->GetPosition());

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(sceneId);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		SpawnZombies(100, player->GetPosition(), 200.f);
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		ClearZombies();
	}
	if (poolZombies.GetUseList().size() == 0)
	{
		SpawnZombies(10, player->GetPosition(), 200.f);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

VertexArrayGo* SceneDev1::CreateBackground(sf::Vector2i size, sf::Vector2f tileSize, sf::Vector2f texSize,
	std::string textureId)
{
	VertexArrayGo* background = new VertexArrayGo(textureId, "Background");

	background->vertexArray.setPrimitiveType(sf::Quads);
	background->vertexArray.resize(size.x * size.y * 4);

	sf::Vector2f startPos = { 0, 0 };
	sf::Vector2f offsets[4] =
	{
		{0.f, 0.f},
		{tileSize.x, 0.f},
		{tileSize.x, tileSize.y},
		{0.f, tileSize.y}
	};

	sf::Vector2f texOffsets[4] =
	{
		{0.f, 0.f},
		{texSize.x, 0.f},
		{texSize.x, texSize.y},
		{0.f, texSize.y}
	};

	sf::Vector2f currPos = startPos;
	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			int texIndex = 3;
			if (i != 0 && i != size.y - 1 && j != 0 && j != size.x - 1)
			{
				texIndex = Utils::RandomRange(0, 2);
			}

			int tileIndex = size.x * i + j;
			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = tileIndex * 4 + k;
				background->vertexArray[vertexIndex].position = currPos + offsets[k];
				background->vertexArray[vertexIndex].texCoords = texOffsets[k];
				background->vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
			}
			currPos.x += tileSize.x;
		}
		currPos.x = startPos.x;
		currPos.y += tileSize.y;
	}

	return background;
}

void SceneDev1::CreateZombies(int count)
{
	for (int i = 0; i < count; i++)
	{
		Zombie* zombie = poolZombies.Get();
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		zombie->SetType(zombieType);
		zombie->SetPlayer(player);
		zombie->SetBackground(background);

		zombie->Init();
		zombie->Reset();
		zombie->SetActive(false);

		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			sceneDev1->AddGo(zombie);
		}
	}
}

void SceneDev1::SpawnZombies(int count, sf::Vector2f center, float radius)
{
	for (int i = 0; i < count; i++)
	{
		Zombie* zombie = poolZombies.Get();
		sf::Vector2f pos;
		do
		{
			pos = center + Utils::RandomInCircle(radius);
		} while (Utils::Distance(center, pos) < 100.f && radius > 100.f);

		zombie->SetPosition(pos);
		AddGo(zombie);
	}
}

void SceneDev1::ClearZombies()
{
	for (auto zombie : poolZombies.GetUseList())
	{
		RemoveGo(zombie);
	}

	poolZombies.Clear();
}

void SceneDev1::OnDieZombie(Zombie* zombie)
{
	RemoveGo(zombie);
	poolZombies.Return(zombie);
}

void SceneDev1::OnDiePlayer()
{
	isGameOver = true;
}

const std::list<Zombie*>* SceneDev1::GetZombieList() const
{
	return &poolZombies.GetUseList();
}

