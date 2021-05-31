#pragma once
#include "GameObject.h"

class Object;
class Image;
class Camera;

class LayerManager : public GameObject
{
private:
	//vector<Object*> vObjects;
	Camera* lpCamera;
	vector<pair<Image*, POINTFLOAT>> vObjects;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	//void AddObject(Object* object);
	void AddObject(pair<Image*, POINTFLOAT> object);
	void RemoveObject(pair<Image*, POINTFLOAT> object);
	void LayerSort(int start, int end);

	inline void SetCamera(Camera* camera) { this->lpCamera = camera; }
};

