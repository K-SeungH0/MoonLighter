#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>

class Object;
using namespace std;

class CollisionManager : public Singleton<CollisionManager>
{
private:
	vector<Object*> vColliders;

public:
	HRESULT Init();
	void Release();

	void AddCollider(Object* object);
	void RemoveCollider(Object* obejct);

	vector<Object*> CheckCollider(Object* own);
};

