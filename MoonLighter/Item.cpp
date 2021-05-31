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
		// 1000���� ����
	case 1000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->speed = -25;
		this->description = "�Ʒÿ� ���";
		break;
	case 1001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->speed = -25; 
		this->description = "ŷ�����׷� ���";
		break;
	case 1010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�Ʒÿ� ��";
		break;
	case 1011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�����ְ� ��";
		break;
	case 1020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�Ʒÿ� â";
		break;
	case 1021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�� â";
		break;
	case 1030:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�Ʒÿ� �۷���";
		break;
	case 1031:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�����ְ� �۷���";
		break;
	case 1040:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_0");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "�Ʒÿ� Ȱ";
		break;
	case 1041:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_1");
		this->slotType = SLOTTYPE::MAINWEAPON;
		this->description = "ŷ Ȱ";
		break;

		// 2000���� ����
	case 2000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_0");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "�μ��� ��";
		break;
	case 2001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_1");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "����";
		break;
	case 2002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_2");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "������ ����";
		break;
	case 2003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_3");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "���� �ɰ���";
		break;
	case 2004:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_4");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "�� �ھ�";
		break;
	case 2005:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_5");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "�� ����";
		break;
	case 2006:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_6");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "���� �ν�����";
		break;
	case 2007:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_7");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "��ö ��";
		break;
	case 2008:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_8");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "���� ����";
		break;
	case 2009:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_9");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "�Ķ� ����";
		break;
	case 2010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_10");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "��� ����";
		break;
	case 2011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_11");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "���� ����";
		break;
	case 2012:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_12");
		this->slotType = SLOTTYPE::INVEN;
		this->description = "���� ����";
		break;
		
		// 3000���� ����
	case 3000:		
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_0");
		this->slotType = SLOTTYPE::POTION;
		this->description = "���� Lv1";
		this->hp = 10;
		break;
	case 3001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_1");
		this->slotType = SLOTTYPE::POTION;
		this->description = "���� Lv2";
		this->hp = 20;
		break;
	case 3002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_2");
		this->slotType = SLOTTYPE::POTION;
		this->description = "���� Lv3";
		this->hp = 30;
		break;
	case 3003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_3");
		this->slotType = SLOTTYPE::POTION;
		this->description = "���� Lv4";
		this->hp = 40;
		break;

		// 4õ���� ��
	case 4000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Boot_0");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 50;
		this->description = "õ �Ź�";
		break;
	case 4001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Boot_1");
		this->slotType = SLOTTYPE::SHOES;
		this->speed = 100;
		this->description = "��ö �Ź�";
		break;
	case 4010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Helmet_0");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 50;
		this->description = "õ �Ӹ���";
		break;
	case 4011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Helmet_1");
		this->slotType = SLOTTYPE::HELMET;
		this->hp = 100;
		this->description = "��ö �Ӹ���";
		break;
	case 4020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Chest_0");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 20;
		this->description = "õ ����";
		break;
	case 4021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Chest_1");
		this->slotType = SLOTTYPE::CHEST;
		this->armor = 50;
		this->description = "��ö ����";
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
	// �ʵ� ����
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if (itemData.isEquipment && slotType != SLOTTYPE::POTION)
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->Render(hdc, pos.x, pos.y, 1, true);
}

void Item::Render(HDC hdc, POINT pos)
{
	// �κ� ����
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
	// TODO : �κ��丮 AddItem �߰�
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
