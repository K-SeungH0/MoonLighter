#pragma once
#include "Object.h"
class NPC : public Object
{
private:
	RECTFLOAT interactCollider;
	string dialog;

public:
	HRESULT Init() override;
	HRESULT Init(POINTFLOAT pos);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	inline void SetDialog(string dialog) { this->dialog = dialog; }
};