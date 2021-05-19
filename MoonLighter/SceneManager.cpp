#include "SceneManager.h"
#include "GameObject.h"

GameObject* SceneManager::currentScene = nullptr;
GameObject* SceneManager::loadingScene = nullptr;
GameObject* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
    if (SUCCEEDED(SceneManager::readyScene->Init()))
    {
        SceneManager::currentScene = SceneManager::readyScene;

        SceneManager::loadingScene->Release();
        SceneManager::loadingScene = nullptr;
        SceneManager::readyScene = nullptr;
    }
    return 0;
}

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Release()
{
    for (auto iter = mSceneDatas.begin(); iter != mSceneDatas.end(); iter++)
    {
        if (iter->second)
        {
            iter->second->Release();
            //delete iter->second;
            iter->second = nullptr;
        }
    }
    mSceneDatas.clear();
    ReleaseSingleton();
}

void SceneManager::Update()
{
    if (currentScene)
        currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if (currentScene)
        currentScene->Render(hdc);
}

bool SceneManager::AddScene(string key, GameObject* scene)
{
    if (scene == nullptr)
        return false;

    auto iter = mSceneDatas.find(key);
    if (iter != mSceneDatas.end())
        return false;

    mSceneDatas.insert(pair<string, GameObject*>(key, scene));
    return false;
}

bool SceneManager::AddLodingScene(string key, GameObject* scene)
{
    if (scene == nullptr)
        return false;

    auto iter = mLoadingSceneDatas.find(key);
    if (iter != mLoadingSceneDatas.end())
        return false;

    mSceneDatas.insert(pair<string, GameObject*>(key, scene));
    return false;
    return false;
}

HRESULT SceneManager::ChageScene(string sceneName)
{
    auto iter = mSceneDatas.find(sceneName);
    if (iter == mSceneDatas.end())
        return E_FAIL;

    if (iter->second == currentScene)
        return S_OK;

    if (currentScene)
        currentScene->Release();

    if (SUCCEEDED(iter->second->Init()))
    {
        currentScene = iter->second;

        return S_OK;
    }
    return E_FAIL;
}

HRESULT SceneManager::ChageScene(string sceneName, string lodingSceneName)
{
    auto iter = mSceneDatas.find(sceneName);
    if (iter == mSceneDatas.end())
        return E_FAIL;

    if (iter->second == currentScene)
        return S_OK;

    // 로딩씬 찾기
    map<string, GameObject*>::iterator iterLoading = mLoadingSceneDatas.find(lodingSceneName);

    if (iterLoading == mLoadingSceneDatas.end())
        return ChageScene(sceneName);



    if (SUCCEEDED(iterLoading->second->Init()))
    {
        if (currentScene)
            currentScene->Release();

        currentScene = iterLoading->second;

        readyScene = iter->second;
        loadingScene = iterLoading->second;

        // 다음 씬을 초기화할 쓰레드 생성
        DWORD loadingThreadId;
        HANDLE hThread;
        hThread = CreateThread(NULL, 0,
            LoadingThread,      // 실행 시킬 함수포인터
            NULL,               // 실행 시킬 함수의 매개변수
            0,
            &loadingThreadId    // 쓰레드의 ID
            );
        
        CloseHandle(hThread);
        return S_OK;
    }
    return E_FAIL;
}
