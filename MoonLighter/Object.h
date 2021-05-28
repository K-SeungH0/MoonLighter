#pragma once
#include "GameObject.h"

class Camera;

enum class OBJECTTYPE
{
	WALL,
	ITEM,
	BREAKABLE,
	UNIT,
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
	//POINTFLOAT* lpCameraPos;
	Camera* lpCamera;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void SetCamera(Camera* lpCamera) { this->lpCamera = lpCamera; }

	inline RECTFLOAT GetCollider() { return this->collider; }
	inline OBJECTTYPE GetObjectType() { return this->objectType; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline Image* GetImage() { return this->lpImage; }
};