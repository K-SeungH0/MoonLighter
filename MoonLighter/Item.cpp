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
		// 1000���� ����
	case 1000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_0");
		this->description = "�Ʒÿ� ���";
		break;
	case 1001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("BigSword_1");
		this->description = "ŷ�����׷� ���";
		break;
	case 1010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_0");
		this->description = "�Ʒÿ� ��";
		break;	
	case 1011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("ShortSword_1");
		this->description = "�����ְ� ��";
		break;
	case 1020:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_0");
		this->description = "�Ʒÿ� â";
		break;
	case 1021:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Spear_1");
		this->description = "�� â";
		break;
	case 1030:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_0");
		this->description = "�Ʒÿ� �۷���";
		break;
	case 1031:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Gloves_1");
		this->description = "�����ְ� �۷���";
		break;
	case 1040:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_0");
		this->description = "�Ʒÿ� Ȱ";
		break;
	case 1041:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Bow_1");
		this->description = "ŷ Ȱ";
		break;

		// 2000���� ����
	case 2000:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_0");
		this->description = "�μ��� ��";
		break;
	case 2001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_1");
		this->description = "����";
		break;
	case 2002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_2");
		this->description = "������ ����";
		break;
	case 2003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_3");
		this->description = "���� �ɰ���";
		break;
	case 2004:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_4");
		this->description = "�� �ھ�";
		break;
	case 2005:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_5");
		this->description = "�� ����";
		break;
	case 2006:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_6");
		this->description = "���� �ν�����";
		break;
	case 2007:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_7");
		this->description = "��ö ��";
		break;
	case 2008:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_8");
		this->description = "���� ����";
		break;
	case 2009:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_9");
		this->description = "�Ķ� ����";
		break;
	case 2010:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_10");
		this->description = "��� ����";
		break;
	case 2011:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_11");
		this->description = "���� ����";
		break;
	case 2012:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Item_12");
		this->description = "���� ����";
		break;
		
		// 3000���� ����
	case 3000:		
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_0");
		this->description = "���� Lv1";
		break;
	case 3001:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_1");
		this->description = "���� Lv2";
		break;
	case 3002:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_2");
		this->description = "���� Lv3";
		break;
	case 3003:
		this->itemData.lpItemImage = IMAGEMANAGER->FindImage("Potion_3");
		this->description = "���� Lv4";
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
	// �ʵ� ����
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if (itemData.isEquipment)
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, IMAGE_SIZE, true);
	else
		itemData.lpItemImage->FrameRender(hdc, pos.x, pos.y, 0, 0, 1, true);
}

void Item::Render(HDC hdc, POINT pos)
{
	// �κ� ����
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
