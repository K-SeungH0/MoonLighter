#include "Item.h"
#include "Image.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Weapon.h"

HRESULT Item::Init()
{
	return S_OK;
}

HRESULT Item::Init(GameData::ItemData itemData, ItemManager* lpItemManager)
{
	this->objectType = OBJECTTYPE::ITEM;
	this->itemData = itemData;
	this->lpItemManager = lpItemManager;

	switch (itemData.itemCode)
	{
		// 1000¹ø´ë ¹«±â
	case 1000:
		this->lpItemImage = IMAGEMANAGER->FindImage("BigSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë ´ë°Ë";
		this->itemData.isEquipment = true;
		break;
	case 1001:
		this->lpItemImage = IMAGEMANAGER->FindImage("BigSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "Å·°«Á¦³×·² ´ë°Ë";
		this->itemData.isEquipment = true;
		break;
	case 1010:
		this->lpItemImage = IMAGEMANAGER->FindImage("ShortSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë °Ë";
		this->itemData.isEquipment = true;
		break;
	case 1011:
		this->lpItemImage = IMAGEMANAGER->FindImage("ShortSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "¿ìÁÖÃÖ°­ °Ë";
		this->itemData.isEquipment = true;
		break;
	case 1020:
		this->lpItemImage = IMAGEMANAGER->FindImage("Spear_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë Ã¢";
		this->itemData.isEquipment = true;
		break;
	case 1021:
		this->lpItemImage = IMAGEMANAGER->FindImage("Spear_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "°« Ã¢";
		this->itemData.isEquipment = true;
		break;
	case 1030:
		this->lpItemImage = IMAGEMANAGER->FindImage("Gloves_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë ±Û·¯ºê";
		this->itemData.isEquipment = true;
		break;
	case 1031:
		this->lpItemImage = IMAGEMANAGER->FindImage("Gloves_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "¼¼°èÃÖ°í ±Û·¯ºê";
		this->itemData.isEquipment = true;
		break;
	case 1040:
		this->lpItemImage = IMAGEMANAGER->FindImage("Bow_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë È°";
		this->itemData.isEquipment = true;
		break;
	case 1041:
		this->lpItemImage = IMAGEMANAGER->FindImage("Bow_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "Å· È°";
		this->itemData.isEquipment = true;
		break;

		// 2000¹ø´ë ÀâÅÛ
	case 2000:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_0");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "ºÎ¼­Áø °Ë";
		this->itemData.isEquipment = false;
		break;
	case 2001:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_1");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "±¤¼®";
		this->itemData.isEquipment = false;
		break;
	case 2002:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_2");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "¿¡³ÊÁö ±¤¼®";
		this->itemData.isEquipment = false;
		break;
	case 2003:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_3");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "Á¾ÀÌ ÂÉ°¡¸®";
		this->itemData.isEquipment = false;
		break;
	case 2004:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_4");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°ñ·½ ÄÚ¾î";
		this->itemData.isEquipment = false;
		break;
	case 2005:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_5");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°ñ·½ µµ¸é";
		this->itemData.isEquipment = false;
		break;
	case 2006:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_6");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "¿ø¼® ºÎ½º·¯±â";
		this->itemData.isEquipment = false;
		break;
	case 2007:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_7");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°­Ã¶ ¹Ù";
		this->itemData.isEquipment = false;
		break;
	case 2008:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_8");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "»¡°£ Á©¸®";
		this->itemData.isEquipment = false;
		break;
	case 2009:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_9");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "ÆÄ¶õ Á©¸®";
		this->itemData.isEquipment = false;
		break;
	case 2010:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_10");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "³ë¶õ Á©¸®";
		this->itemData.isEquipment = false;
		break;
	case 2011:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_11");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "³ª¹µ °¡Áö";
		this->itemData.isEquipment = false;
		break;
	case 2012:
		this->lpItemImage = IMAGEMANAGER->FindImage("Item_12");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "µ¢±¼ Á¶°¢";
		this->itemData.isEquipment = false;
		break;
		
		// 3000¹ø´ë ¹°¾à
	case 3000:		
		this->lpItemImage = IMAGEMANAGER->FindImage("Potion_0");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv1";
		this->hp = 10;
		this->itemData.isEquipment = true;
		break;
	case 3001:
		this->lpItemImage = IMAGEMANAGER->FindImage("Potion_1");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv2";
		this->hp = 20;
		this->itemData.isEquipment = true;
		break;
	case 3002:
		this->lpItemImage = IMAGEMANAGER->FindImage("Potion_2");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv3";
		this->hp = 30;
		this->itemData.isEquipment = true;
		break;
	case 3003:
		this->lpItemImage = IMAGEMANAGER->FindImage("Potion_3");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv4";
		this->hp = 40;
		this->itemData.isEquipment = true;
		break;

		// 4Ãµ¹ø´ë ¹æ¾î±¸
	case 4000:
		this->lpItemImage = IMAGEMANAGER->FindImage("Boot_0");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 50;
		this->description = "Ãµ ½Å¹ß";
		this->itemData.isEquipment = true;
		break;
	case 4001:
		this->lpItemImage = IMAGEMANAGER->FindImage("Boot_1");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 100;
		this->description = "°­Ã¶ ½Å¹ß";
		this->itemData.isEquipment = true;
		break;
	case 4010:
		this->lpItemImage = IMAGEMANAGER->FindImage("Helmet_0");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 50;
		this->description = "Ãµ ¸Ó¸®¶ì";
		this->itemData.isEquipment = true;
		break;
	case 4011:
		this->lpItemImage = IMAGEMANAGER->FindImage("Helmet_1");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 100;
		this->description = "°­Ã¶ ¸Ó¸®¶ì";
		this->itemData.isEquipment = true;
		break;
	case 4020:
		this->lpItemImage = IMAGEMANAGER->FindImage("Chest_0");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 20;
		this->description = "Ãµ °©¿Ê";
		this->itemData.isEquipment = true;
		break;
	case 4021:
		this->lpItemImage = IMAGEMANAGER->FindImage("Chest_1");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 50;
		this->description = "°­Ã¶ °©¿Ê";
		this->itemData.isEquipment = true;
		break;

	}

	return S_OK;
}

void Item::Release()
{

}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
	// ÇÊµå ·»´õ
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if (itemData.isEquipment && slotType != SLOTTYPE::POTION)
		lpItemImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);
	else
		lpItemImage->Render(hdc, pos.x, pos.y, 1, true);
}

void Item::Render(HDC hdc, POINT pos)
{
	// ÀÎº¥ ·»´õ
	if(itemData.isEquipment && slotType != SLOTTYPE::POTION)
		lpItemImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);
	else
		lpItemImage->Render(hdc, pos.x, pos.y, 1, true);

}

void Item::Use()
{
	if (slotType == SLOTTYPE::POTION)
	{
		if(--lpOwnerSlot->count == 0)
			GAMEDATA->GetRunTimeInventory()->RemoveItem(this);

		this->itemData.count--;
	}
}

void Item::PickUp()
{
	// TODO : ÀÎº¥Åä¸® AddItem Ãß°¡
	lpItemManager->GetInventory()->AddItem(this);
	lpItemManager->RemoveItem(this);
}

void Item::ReSetCollider()
{
	collider.left = this->pos.x - lpItemImage->GetFrameWidth();
	collider.right = this->pos.x + lpItemImage->GetFrameWidth();
	collider.top = this->pos.y - lpItemImage->GetFrameHeight();
	collider.bottom = this->pos.y + lpItemImage->GetFrameHeight();
}
