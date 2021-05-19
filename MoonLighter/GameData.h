#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>
//#include "Inventory.h"
//#include "Player.h"
class Inventory;
//class Player;

class GameData : public Singleton<GameData>
{
private:
	Inventory* lpGameDataInventory;
	//Player lpGameDataPlayer;

public:
	HRESULT Init();
	void Release();

	Inventory* GetInventory() { return this->lpGameDataInventory; }
};

