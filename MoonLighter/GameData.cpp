#include "GameData.h"
#include "Player.h"
#include "Inventory.h"
GameData::ItemData GameData::gameSaveData[30];
int GameData::gold;

HRESULT GameData::Init()
{
	//lpPlayerData = new Player();
	//lpPlayerData->Init();
	FileLoad();
	return S_OK;
}

void GameData::Release()
{

}

void GameData::AddItem(ItemData item)
{
	bool isNewItem = true;
	for (auto iter = vItemDatas.begin(); iter != vItemDatas.end(); iter++)
	{
		if ((*iter).itemCode == item.itemCode)
		{
			isNewItem = false;
			(*iter).count = item.count;
			(*iter).slotPos = item.slotPos;
			(*iter).isEquipment = item.isEquipment;
		}
	}

	if(isNewItem)
		vItemDatas.push_back(item);
}

void GameData::SaveData(vector<ItemData> items)
{
	vItemDatas = items;
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
		lpRunTimePlayer->LoadData();
	}
	else
	{
		lpRunTimeInventory->DataSave();
		FileSave();
		delete lpRunTimeInventory;
		lpRunTimeInventory = nullptr;
		lpRunTimeInventory = new Inventory();
		lpRunTimeInventory->Init();
		lpRunTimePlayer->LoadData();
	}
}

void GameData::FileSave()
{
	string saveName = "Save/SaveGameData.data";
	DWORD writtenBytes;
	HANDLE hFile;

	for (int i = 0; i < vItemDatas.size(); i++)
	{
		gameSaveData[i] = vItemDatas[i];
	}
	
	hFile = CreateFile(saveName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (WriteFile(hFile, &gameSaveData, sizeof(ItemData) * 30, &writtenBytes, NULL))
	{
		if (WriteFile(hFile, &gold, sizeof(int), &writtenBytes, NULL))
		{

		}
		else
		{
			MessageBox(g_hWnd, "골드 세이브 실패", "실패", MB_OK);
		}
	}
	else
	{
		MessageBox(g_hWnd, "인벤토리 세이브 실패", "실패", MB_OK);
	}
	
	CloseHandle(hFile);
}

void GameData::FileLoad()
{
	string saveName = "Save/SaveGameData.data";
	DWORD readBytes;
	HANDLE hFile;
	
	hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFile, &gameSaveData, sizeof(ItemData) * 30, &readBytes, NULL))
	{
		if (ReadFile(hFile, &gold, sizeof(int), &readBytes, NULL))
		{

		}
		else
		{

		}
	}
	else
	{
	}


	for (int i = 0; i < 30; i++)
	{
		if (gameSaveData[i].itemCode == 0) break;

		vItemDatas.push_back(gameSaveData[i]);
	}
	
	CloseHandle(hFile);
}
