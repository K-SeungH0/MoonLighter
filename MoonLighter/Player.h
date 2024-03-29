#pragma once
#include "Unit.h"

class Image;
class Weapon;
class Item;
enum class SLOTTYPE;

class Player : public Unit
{
private:
	int imageFrame;
	int stateFrame;
	int maxFrame;
	int preFrame;
	int comboStack;

	float frameTimer;
	float deadTimer;
	bool isAction;
	bool isCombo;
	bool isEquipMainWeapon;

	int additionalHp;
	int additionalMoveSpeed;
	int additionalArmor;

	//int gold;
	bool inBattle;
	Weapon* lpCurrentWeapon;

	Item* lpMainWeapon;
	Item* lpSubWeapon;

	Item* lpPotion;

	vector<int> attackFrame;

	HDC* pixelDC;
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
	void SetCollider();
	void NextCombo(int first, int second, int third);
	void AddAttackFrame(vector<int> frame);
	void ChangeWeapon(Item* weapon);
	void EquipFromInventory(SLOTTYPE slotType, Item* equipment);
	void SwapWeapon();
	void CheckItem();
	bool PixelCollision(int x, int y, bool isHorizontal, COLORREF checkColor);
	
	// 동작을 시작할때 실행
	void FrameReset();

	inline void SetPixelHDC(HDC* pixelDC) { this->pixelDC = pixelDC; }
 	void SetProjectileCamera();
	
	inline POINTFLOAT GetPos() { return this->pos; }
	inline POINTFLOAT* GetpPos() { return &this->pos; }
	inline int GetImageFrame() { return this->imageFrame; }
	inline int GetStateFrame() { return this->stateFrame; }
	inline STATE GetState() { return this->state; }
	inline bool GetIsAction() { return this->isAction; }
	inline bool GetIsMainWeapon() { return this->isEquipMainWeapon; }
	inline int GetAdditionalHp() { return this->additionalHp; }
	inline int GetAdditionalMoveSpeed() { return this->additionalMoveSpeed; }
	inline int GetAdditionalArmor() { return this->additionalArmor; }
	//inline int GetGold() { return this->gold; }
	inline bool GetIsEquipMainWeapon() { return this->isEquipMainWeapon; }
	inline Camera* GetCamera() { return this->lpCamera; }
	inline Weapon* GetWeapon() { return this->lpCurrentWeapon; }
	Image* GetCurrentWeaponImage();
	Image* GetPotionImage();
	int GetPotionCount();
	
	void ImageLoad();
	void LoadData();
	~Player() override {};
};

