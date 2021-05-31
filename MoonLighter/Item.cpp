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
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->speed = -25;
		this->description = "ÈÆ·Ã¿ë ´ë°Ë";
		break;
	case 1001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->speed = -25; 
		this->description = "Å·°«Á¦³×·² ´ë°Ë";
		break;
	case 1010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë °Ë";
		break;
	case 1011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "¿ìÁÖÃÖ°­ °Ë";
		break;
	case 1020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë Ã¢";
		break;
	case 1021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "°« Ã¢";
		break;
	case 1030:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë ±Û·¯ºê";
		break;
	case 1031:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "¼¼°èÃÖ°í ±Û·¯ºê";
		break;
	case 1040:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ÈÆ·Ã¿ë È°";
		break;
	case 1041:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "Å· È°";
		break;

		// 2000¹ø´ë ÀâÅÛ
	case 2000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_0");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "ºÎ¼­Áø °Ë";
		break;
	case 2001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_1");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "±¤¼®";
		break;
	case 2002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_2");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "¿¡³ÊÁö ±¤¼®";
		break;
	case 2003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_3");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "Á¾ÀÌ ÂÉ°¡¸®";
		break;
	case 2004:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_4");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°ñ·½ ÄÚ¾î";
		break;
	case 2005:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_5");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°ñ·½ µµ¸é";
		break;
	case 2006:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_6");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "¿ø¼® ºÎ½º·¯±â";
		break;
	case 2007:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_7");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "°­Ã¶ ¹Ù";
		break;
	case 2008:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_8");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "»¡°£ Á©¸®";
		break;
	case 2009:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_9");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "ÆÄ¶õ Á©¸®";
		break;
	case 2010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_10");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "³ë¶õ Á©¸®";
		break;
	case 2011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_11");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "³ª¹µ °¡Áö";
		break;
	case 2012:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_12");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "µ¢±¼ Á¶°¢";
		break;
		
		// 3000¹ø´ë ¹°¾à
	case 3000:		
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_0");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv1";
		this->hp = 10;
		break;
	case 3001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_1");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv2";
		this->hp = 20;
		break;
	case 3002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_2");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv3";
		this->hp = 30;
		break;
	case 3003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_3");
		this->slotType = SLOTTYPE::POTION;
		this->description = "Æ÷¼Ç Lv4";
		this->hp = 40;
		break;

		// 4Ãµ¹ø´ë ¹æ¾î±¸
	case 4000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Boot_0");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 50;
		this->description = "Ãµ ½Å¹ß";
		break;
	case 4001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Boot_1");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 100;
		this->description = "°­Ã¶ ½Å¹ß";
		break;
	case 4010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Helmet_0");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 50;
		this->description = "Ãµ ¸Ó¸®¶ì";
		break;
	case 4011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Helmet_1");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 100;
		this->description = "°­Ã¶ ¸Ó¸®¶ì";
		break;
	case 4020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Chest_0");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 20;
		this->description = "Ãµ °©¿Ê";
		break;
	case 4021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Chest_1");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 50;
		this->description = "°­Ã¶ °©¿Ê";
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
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, 1, true);
}

void Item::Render(HDC hdc, POINT pos)
{
	// ÀÎº¥ ·»´õ
	if(itemData.isEquipment && slotType != SLOTTYPE::POTION)
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, 1, true);

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
	collider.left = this->pos.x - itemData.lpItemImage->GetFrameWidth();
	collider.right = this->pos.x + itemData.lpItemImage->GetFrameWidth();
	collider.top = this->pos.y - itemData.lpItemImage->GetFrameHeight();
	collider.bottom = this->pos.y + itemData.lpItemImage->GetFrameHeight();
}
