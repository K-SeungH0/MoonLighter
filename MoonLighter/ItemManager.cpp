#include "ItemManager.h"
#include "Item.h"
#include "Inventory.h"
#include "Weapon.h"

HRESULT ItemManager::Init()
{
	return S_OK;
}

HRESULT ItemManager::Init(Inventory* lpInventory)
{
	this->lpInventory = lpInventory;
	//this->lpInventory->DataLoad();

	return S_OK;
}

void ItemManager::Release()
{

}

void ItemManager::Update()
{
}

void ItemManager::Render(HDC hdc)
{
	for (auto iter = vItems.begin(); iter != vItems.end(); iter++)
	{
		(*iter)->Render(hdc);
	}
}

void ItemManager::AddItem(Item* item, GameData::ItemData itemData, POINTFLOAT pos)
{
	vItems.push_back(item);
	vItems.back()->Init(itemData, this);
	vItems.back()->SetPos(pos);

	COLLIDERMANAGER->AddCollider(vItems.back());
}

void ItemManager::RemoveItem(Item* item)
{
	auto iter = find(vItems.begin(), vItems.end(), item);
	if (*iter == item)
	{
		COLLIDERMANAGER->RemoveCollider(*iter);
		(*iter)->Release();
		vItems.erase(iter);
	}
}
