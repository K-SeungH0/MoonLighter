#pragma once
#include "UI.h"

#define INVEN_SIZE_X 5
#define INVEN_SIZE_Y 4

class Image;
class Item;
class ItemManager;
class Weapon;
class Camera;
enum class SLOTTYPE
{
	INVEN,
	MAINWEAPON,
	SUBWEAPON,
	HELMET,
	CHEST,
	SHOES,
	POTION,
	NONE
};

struct Slot
{
	Image* lpSlotImage;
	POINT slotPos;
	Item* lpItem = nullptr;
	//GameData::ItemData itemData;
	int count = 0;
	SLOTTYPE slotType;
};

class Inventory : public UI
{
private:
	bool isActive;

	Image* lpJBtnImage;
	Image* lpIBtnImage;
	Image* lpDescriptionImage;
	Image* lpCurrentWeaponImage;

	Slot invenSlots[INVEN_SIZE_Y][INVEN_SIZE_X];
	Slot equipSlots[INVEN_SIZE_Y][2];
	Slot selectSlots;
	Slot selectItem;

	int selectSlotX;
	int selectSlotY;

	bool isEquipSelect;
	bool isItemPickUp;
	char text[128];

	float selectSlotSize;
	float selectTimer;

	Camera* lpCamera;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void AddItem(Item* item);
	void RemoveItem(Item* item);
	void ToggleActive();
	void ItemPickUp();
	void ItemAllPickUp();
	void ItemPickDown();
	void SwapWeapon();

	inline void SetCamera(Camera* lpCamera) { this->lpCamera = lpCamera; }
	inline bool GetActive() { return this->isActive; }

	void DataLoad(ItemManager* lpItemManager);
	void ImageLoad();
	~Inventory() override {};
};

