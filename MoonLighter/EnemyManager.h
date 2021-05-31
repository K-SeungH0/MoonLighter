#pragma once
#include "GameObject.h"

class Enemy;

class EnemyManager : public GameObject
{
private:
	vector<Enemy*> vEnemys;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	inline vector<Enemy*> GetEnemys() { return this->vEnemys; }
};

