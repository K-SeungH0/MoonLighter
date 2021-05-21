#include "Item.h"
#include "Image.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Equipment.h"

HRESULT Item::Init()
{
	return S_OK;
}

HRESULT Item::Init(GameData::ItemData itemData, ItemManager* lpItemManager)
{
	this->type = OBJECTTYPE::ITEM;
	this->itemData = itemData;
	this->lpItemManager = lpItemManager;
	string itemName = "";
	int number = 0;
	switch (itemData.itemCode)
	{
		// 1000¹ø´ë ¹«±â
	case 1000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_0");
		this->description = "ÈÆ·Ã¿ë ´ë°Ë";
		break;
	case 1001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_1");
		this->description = "Å·°«Á¦³×·² ´ë°Ë";
		break;
	case 1010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_0");
		this->description = "ÈÆ·Ã¿ë °Ë";
		break;	
	case 1011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_1");
		this->description = "¿ìÁÖÃÖ°­ °Ë";
		break;
	case 1020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_0");
		this->description = "ÈÆ·Ã¿ë Ã¢";
		break;
	case 1021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_1");
		this->description = "°« Ã¢";
		break;
	case 1030:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_0");
		this->description = "ÈÆ·Ã¿ë ±Û·¯ºê";
		break;
	case 1031:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_1");
		this->description = "¼¼°èÃÖ°í ±Û·¯ºê";
		break;
	case 1040:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_0");
		this->description = "ÈÆ·Ã¿ë È°";
		break;
	case 1041:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_1");
		this->description = "Å· È°";
		break;

		// 2000¹ø´ë ÀâÅÛ
	case 2000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_0");
		this->description = "ºÎ¼­Áø °Ë";
		break;
	case 2001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_1");
		this->description = "±¤¼®";
		break;
	case 2002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_2");
		this->description = "¿¡³ÊÁö ±¤¼®";
		break;
	case 2003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_3");
		this->description = "Á¾ÀÌ ÂÉ°¡¸®";
		break;
	case 2004:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_4");
		this->description = "°ñ·½ ÄÚ¾î";
		break;
	case 2005:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_5");
		this->description = "°ñ·½ µµ¸é";
		break;
	case 2006:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_6");
		this->description = "¿ø¼® ºÎ½º·¯±â";
		break;
	case 2007:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_7");
		this->description = "°­Ã¶ ¹Ù";
		break;
	case 2008:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_8");
		this->description = "»¡°£ Á©¸®";
		break;
	case 2009:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_9");
		this->description = "ÆÄ¶õ Á©¸®";
		break;
	case 2010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_10");
		this->description = "³ë¶õ Á©¸®";
		break;
	case 2011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_11");
		this->description = "³ª¹µ °¡Áö";
		break;
	case 2012:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_12");
		this->description = "µ¢±¼ Á¶°¢";
		break;
		
		// 3000¹ø´ë ¹°¾à
	case 3000:		
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_0");
		this->description = "Æ÷¼Ç Lv1";
		break;
	case 3001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_1");
		this->description = "Æ÷¼Ç Lv2";
		break;
	case 3002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_2");
		this->description = "Æ÷¼Ç Lv3";
		break;
	case 3003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_3");
		this->description = "Æ÷¼Ç Lv4";
		break;
	}

	return S_OK;
}

void Item::Release()
{
	delete this;
}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
	// ÇÊµå ·»´õ
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if (itemData.isEquipment)
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, 1, true);
}

void Item::Render(HDC hdc, POINT pos)
{
	// ÀÎº¥ ·»´õ
	if(itemData.isEquipment)
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, 1 , true);

}

void Item::Use()
{

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
