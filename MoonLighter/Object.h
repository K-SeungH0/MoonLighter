#pragma once
#include "GameObject.h"

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
	RECTFLOAT collider;
	Image* lpImage;
	OBJECTTYPE objectType;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline RECTFLOAT GetCollider() { return this->collider; }
	inline OBJECTTYPE GetObjectType() { return this->objectType; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline Image* GetImage() { return this->lpImage; }
};