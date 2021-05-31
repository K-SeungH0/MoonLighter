#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>

class Object;
class Image;
using namespace std;

class CollisionManager : public Singleton<CollisionManager>
{
private:
	vector<Object*> vColliders;
	vector<pair<Image*, POINTFLOAT>> vPixelColliders;

public:
	HRESULT Init();
	void Release();

	void AddCollider(Object* object);
	void AddPixelCollider(Image* lpImage, POINTFLOAT pos);
	void RemoveCollider(Object* obejct);
	void RemovePixelCollider();

	vector<Object*> CheckCollider(Object* own);
	bool CheckPixelCollider(Object* own, COLORREF checkColor);
};