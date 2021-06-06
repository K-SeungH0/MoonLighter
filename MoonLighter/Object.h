#pragma once
#include "GameObject.h"

class Camera;

enum class OBJECTTYPE
{
	WALL,
	ITEM,
	BREAKABLE,
	UNIT,
	PROJECTILE,
	NONE
};
class Object : public GameObject
{
protected:
	POINTFLOAT pos;
	RECTFLOAT cameraCollider;
	RECTFLOAT collider;
	Image* lpImage;
	OBJECTTYPE objectType;
	Camera* lpCamera;
	RECT moveArea;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void SetMoveArea(RECT moveArea) { this->moveArea = moveArea; }
	inline void SetCamera(Camera* lpCamera) { this->lpCamera = lpCamera; }

	inline RECTFLOAT GetCameraCollider() { return this->cameraCollider; }
	inline RECTFLOAT GetCollider() { return this->collider; }
	inline OBJECTTYPE GetObjectType() { return this->objectType; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline Image* GetImage() { return this->lpImage; }
};