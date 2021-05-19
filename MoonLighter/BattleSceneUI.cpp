#include "BattleSceneUI.h"
#include "UI.h"
#include "Inventory.h"

HRESULT BattleSceneUI::Init()
{
	ImageLoad();

	lpUIbase = new UI();
	lpUIbase->Init(IMAGEMANAGER->FindImage("UI_Base"), { 0,0 });

	lpUIFront = new UI();
	lpUIFront->Init(IMAGEMANAGER->FindImage("UI_front"), { 0,0 });

	lpUIGold = new UI();
	lpUIGold->Init(IMAGEMANAGER->FindImage("UI_gold"), { 0,0 });

	lpUIInventory = GAMEDATA->GetInventory();
	//lpUIInventory = new Inventory();
	//lpUIInventory->Init();

	return S_OK;
}

void BattleSceneUI::Release()
{
	lpUIbase->Release();
	lpUIFront->Release();
	lpUIGold->Release();
	//lpUIInventory->Release();
}

void BattleSceneUI::Update()
{
	lpUIInventory->Update();
}

void BattleSceneUI::Render(HDC hdc)
{
	lpUIbase->Render(hdc);
	lpUIFront->Render(hdc);
	lpUIGold->Render(hdc);
	lpUIInventory->Render(hdc);
}

bool BattleSceneUI::GetInvenActive()
{
	return lpUIInventory->GetActive();
}

void BattleSceneUI::ToggleInven()
{
	lpUIInventory->ToggleActive();
}

void BattleSceneUI::ImageLoad()
{
	COLORREF color = RGB(128, 128, 128);
	IMAGEMANAGER->AddImage("UI_Base", L"Image/UI/UI_base.png",
		1280, 720, 1, 1, true, color);
	IMAGEMANAGER->AddImage("UI_front", L"Image/UI/UI_front.png",
		1280, 720, 1, 1, true, color);
	IMAGEMANAGER->AddImage("UI_gold", L"Image/UI/UI_gold.png",
		1280, 720, 1, 1, true, color);
}
