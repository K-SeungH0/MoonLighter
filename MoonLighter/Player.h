#pragma once
#include "Unit.h"

class Image;
class Equipment;

class Player : public Unit
{
private:
	int imageFrame;
	int stateFrame;
	int maxFrame;
	int preFrame;
	int comboStack;

	float frameTimer;

	bool isAction;
	bool isCombo;

	//Image* lpWeaponImage;
	Equipment* weapon;

	char testText[128];
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Avoid();
	void Move(DIR dir);
	void Die();
	void Attack();
	void SpecialAttack();
	void SetHitBox();
	void NextCombo(int first, int second, int third);
	void EquipmentChagne(Equipment* weapon);

	// 동작을 시작할때 실행
	void FrameReset();

	~Player() override {};
};

