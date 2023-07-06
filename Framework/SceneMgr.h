#pragma once
#include "Singleton.h"


class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;


protected:
	SceneMgr() = default;
	virtual ~SceneMgr() override = default;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene = nullptr;

	SceneId startSceneId = SceneId::Title;
	int gameMode;
	int playChar1;
	int playChar2;
public:
	void ChangeScene(SceneId id);

	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	Scene* GetCurrScene() const;
};

#define SCENE_MGR (SceneMgr::Instance())
