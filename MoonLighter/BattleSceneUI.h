#pragma once
#include "GameObject.h"

class UI;
class Inventory;
class BattleSceneUI : public GameObject
{
private:
	UI* lpUIbase;
	UI* lpUIFront;
	UI* lpUIGold;
	Inventory* lpUIInventory;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	bool GetInvenActive();
	void ToggleInven();

	void ImageLoad();
	~BattleSceneUI() override {};
};

