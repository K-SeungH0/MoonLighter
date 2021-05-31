#pragma once
//#include "Object.h"
#include "Unit.h"
class Projectile : public Object
{
private:
	int moveSpeed;
	DIR dir;

	bool isMove;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Move();
	void Shoot(DIR dir, POINTFLOAT pos);
	void SetCollider();

	inline void SetImage(Image* lpImage) { this->lpImage = lpImage; }

	inline bool GetIsMove() { return this->isMove; }
};