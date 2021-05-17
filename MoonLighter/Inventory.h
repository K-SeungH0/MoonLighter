#pragma once
#include "UI.h"

#define SLOT_X 5
#define SLOT_Y 4

class Image;

struct Slot
{
	Image* lpSlotImage;
	POINTFLOAT slotPos;
};
class Inventory : public UI
{
private:
	bool isActive;
	Slot invenSlots[SLOT_Y][SLOT_X];
	Slot equipSlots[SLOT_Y][2];
	Slot selectSlots;

	int selectSlotX;
	int selectSlotY;

	char text[128];
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void ImageLoad();
	
	inline void ToggleActive() { this->isActive = !(this->isActive); }
	inline void SetActive(bool isActive) { this->isActive = isActive; }
	inline bool GetActive() { return this->isActive; }
	~Inventory() override {};
};

