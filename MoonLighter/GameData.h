#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>
using namespace std;

class Image;
class Player;
class Inventory;

class GameData : public Singleton<GameData>
{
public:
	struct ItemData
	{
		int itemCode = 0;
		bool isEquipment;

		// 세이브 전용 데이터
		POINT slotPos;
		int count;
		bool isInEquip;
	};

private:
	vector<ItemData> vItemDatas;
	Player* lpPlayerData;

	Player* lpRunTimePlayer;
	Inventory* lpRunTimeInventory;

	static ItemData gameSaveData[30];
	static int gold;

public:
	HRESULT Init();
	void Release();

	void AddItem(ItemData item);
	void SaveData(vector<ItemData> items);
	void RunTimeDataInit();

	void FileSave();
	void FileLoad();

	inline void SetGold(int gold) { this->gold += gold; }

	inline int GetGold() { return this->gold; }
	inline Player* GetRunTimePlayer() { return this->lpRunTimePlayer; }
	inline Inventory* GetRunTimeInventory() { return this->lpRunTimeInventory; }
	inline vector<ItemData> GetItems() { return this->vItemDatas; }
};

