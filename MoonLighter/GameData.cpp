#include "GameData.h"
#include "Inventory.h"
//#include "Player.h"

HRESULT GameData::Init()
{
	lpGameDataInventory = new Inventory();
	lpGameDataInventory->Init();
	//lpGameDataInventory.Init();

	//lpGameDataPlayer = new Player();
	//lpGameDataPlayer->Init();

	return S_OK;
}

void GameData::Release()
{

}
