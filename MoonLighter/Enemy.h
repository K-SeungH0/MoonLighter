#pragma once
#include "Unit.h"

class UI;
class Enemy : public Unit
{
private:
	RECTFLOAT astarInteractCollider;
	RECTFLOAT attackCollider;
	RECTFLOAT attackRangeCollider;
	UI* lpUICurrentHpbar;
	UI* lpUIReduceHpbar;
	vector<POINT> vAstarPos;
	POINT nextMovePos;

	int imageFrame;
	
	float frameTimer;
	float deadTimer;

	bool isAstar;
	bool isAttack;
	float hpBarReduceTimer;
	
public:
	HRESULT Init() override;
	HRESULT Init(POINT pos);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void SetAstarPos(vector<POINT> vAstarPos) { this->vAstarPos.clear(); this->vAstarPos = vAstarPos; }
	void SetAstarClear(){ this->vAstarPos.clear(); }
	void Move();
	void Attack();
	void Die();
	DIR CheckAttack();
	bool CheckAstar();
	void ResetCollider();
};

