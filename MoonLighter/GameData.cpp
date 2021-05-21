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
	for (auto iter = itemDatas.begin(); iter != itemDatas.end(); iter++)
	{
		if ((*iter).itemCode == item.itemCode)
		{
			isNewItem = false;	
		}
	}

	if(isNewItem)
		itemDatas.push_back(item);
}

void GameData::RunTimeDataInit()
{
	lpRunTimePlayer = new Player();
	lpRunTimePlayer->Init();

	lpRunTimeInventory = new Inventory();
	lpRunTimeInventory->Init();
}
