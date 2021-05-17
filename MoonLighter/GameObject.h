#pragma once
#include "MoonLighter.h"

class GameObject
{
public:
	virtual HRESULT Init() = 0;			
	virtual void Release() = 0;			
	virtual void Update() = 0;			
	virtual void Render(HDC hdc) = 0;	

	GameObject() {};
	virtual ~GameObject() {};
};

