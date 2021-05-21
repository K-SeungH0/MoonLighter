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
	OBJECTTYPE type;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	inline RECTFLOAT GetCollider() { return this->collider; }
	inline OBJECTTYPE GetType() { return this->type; }
};

