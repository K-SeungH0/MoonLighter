#pragma once
#include "GameObject.h"

class UI;
class Inventory;
class Player;
class BattleSceneUI : public GameObject
{
private:
	UI* lpUIbase;
	UI* lpUIFront;
	UI* lpUIGold;
	UI* lpUICurrentHpbar;
	UI* lpUIReduceHpbar;
	UI* lpUICurrentWeapon;

	Inventory* lpUIInventory;

	Player* player;

	float imageSize;
	float hpBarReduceTimer;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	bool GetInvenActive();
	void ToggleInven();

	void ImageLoad();

	inline Inventory* GetInventory() { return this->lpUIInventory; }
	~BattleSceneUI() override {};
};

