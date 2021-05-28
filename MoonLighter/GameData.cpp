#include "GameData.h"
#include "Player.h"
#include "Inventory.h"

HRESULT GameData::Init()
{
	//lpPlayerData = new Player();
	//lpPlayerData->Init();

	return S_OK;
}

void GameData::Release()
{

}

void GameData::AddItem(ItemData item)
{
	// TODO : 수정해야함
	bool isNewItem = true;
	for (auto iter = vItemDatas.begin(); iter != vItemDatas.end(); iter++)
	{
		if ((*iter).itemCode == item.itemCode)
		{
			isNewItem = false;	
		}
	}

	if(isNewItem)
		vItemDatas.push_back(item);
}

void GameData::RunTimeDataInit()
{
	if (!lpRunTimePlayer)
	{
		lpRunTimePlayer = new Player();
		lpRunTimePlayer->Init();
	}
	else
	{
		delete lpRunTimePlayer;
		lpRunTimePlayer = nullptr;
		lpRunTimePlayer = new Player();
		lpRunTimePlayer->Init();
	}

	if (!lpRunTimeInventory)
	{
		lpRunTimeInventory = new Inventory();
		lpRunTimeInventory->Init();
	}
	else
	{
		delete lpRunTimeInventory;
		lpRunTimeInventory = nullptr;
		lpRunTimeInventory = new Inventory();
		lpRunTimeInventory->Init();
	}
}
