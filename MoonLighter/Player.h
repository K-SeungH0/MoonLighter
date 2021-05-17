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

	Equipment* weapon;

	vector<int> attackFrame;
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
	void AddAttackFrame(vector<int> frame);
	void EquipmentChagne(Equipment* weapon);

	void ImageLoad();

	// 동작을 시작할때 실행
	void FrameReset();

	inline POINTFLOAT GetPos() { return this->pos; }
	inline int GetImageFrame() { return this->imageFrame; }
	inline int GetStateFrame() { return this->stateFrame; }
	~Player() override {};
};

