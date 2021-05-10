#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <map>
#include <string>

using namespace std;

class GameObject;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameObject*> mSceneDatas;
	map<string, GameObject*> mLoadingSceneDatas;

public:
	static GameObject* currentScene;
	static GameObject* loadingScene;
	static GameObject* readyScene;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool AddScene(string key, GameObject* scene);
	bool AddLodingScene(string key, GameObject* scene);

	HRESULT ChageScene(string sceneName);
	HRESULT ChageScene(string sceneName, string lodingSceneName);
	//GameNode* GetCurrentScene();
};

