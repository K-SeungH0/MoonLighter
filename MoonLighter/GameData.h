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
		Image* lpItemImage;
		int itemCode;
		bool isEquipment;

		// 세이브 전용 데이터
		POINT slotPos;
		int count;
	};

private:
	vector<ItemData> vItemDatas;
	Player* lpPlayerData;

	Player* lpRunTimePlayer;
	Inventory* lpRunTimeInventory;

public:
	HRESULT Init();
	void Release();

	void AddItem(ItemData item);
	void RunTimeDataInit();

	inline Player* GetRunTimePlayer() { return this->lpRunTimePlayer; }
	inline Inventory* GetRunTimeInventory() { return this->lpRunTimeInventory; }
	inline vector<ItemData> GetItems() { return this->vItemDatas; }
};

