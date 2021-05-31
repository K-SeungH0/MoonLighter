#pragma once
#include "GameObject.h"

class UI;
class Inventory;
class Player;
class Camera;
class BattleSceneUI : public GameObject
{
private:
	UI* lpUIbase;
	UI* lpUIFront;
	UI* lpUIGold;
	UI* lpUICurrentHpbar;
	UI* lpUIReduceHpbar;
	UI* lpUICurrentWeapon;
	UI* lpUIPendantInteract;

	Inventory* lpUIInventory;

	Player* lpPlayer;
	Camera* lpCamera;

	float imageSize;
	float hpBarReduceTimer;

	bool isBattle;
	float escapeTimer;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	bool GetInvenActive();
	void ToggleInven();

	void ImageLoad();

	inline void SetIsBattle(bool isBattle) { this->isBattle = isBattle; }
	inline void SetCamera(Camera* lpCamera) { this->lpCamera = lpCamera; }
	inline Inventory* GetInventory() { return this->lpUIInventory; }
	~BattleSceneUI() override {};
};

