#include "BattleSceneUI.h"
#include "UI.h"
#include "Inventory.h"
#include "Player.h"
#include "Image.h"

HRESULT BattleSceneUI::Init()
{
	ImageLoad();

	lpUIbase = new UI();
	lpUIbase->Init(IMAGEMANAGER->FindImage("UI_Base"), { 131,25 });

	lpUIFront = new UI();
	lpUIFront->Init(IMAGEMANAGER->FindImage("UI_front"), { 1036,0 });

	lpUIGold = new UI();
	lpUIGold->Init(IMAGEMANAGER->FindImage("UI_gold"), { 0,0 });

	lpUIReduceHpbar = new UI();
	lpUIReduceHpbar->Init(IMAGEMANAGER->FindImage("UI_HPbar"), { 179, 32 }, 0, 1);

	lpUICurrentHpbar = new UI();
	lpUICurrentHpbar->Init(IMAGEMANAGER->FindImage("UI_HPbar"), { 179, 32 }, 0, 0);
	
	lpUICurrentWeapon = new UI();
	lpUICurrentWeapon->Init(IMAGEMANAGER->FindImage("UI_CurrentWeapon"), { 1090,85 }, 0, 0);

	lpUIInventory = GAMEDATA->GetRunTimeInventory();

	player = GAMEDATA->GetRunTimePlayer();

	hpBarReduceTimer = 0;
	return S_OK;
}

void BattleSceneUI::Release()
{
	lpUIbase->Release();
	lpUIFront->Release();
	lpUIGold->Release();
	lpUICurrentHpbar->Release();
	lpUIReduceHpbar->Release();
	lpUICurrentWeapon->Release();
}

void BattleSceneUI::Update()
{
	if(lpUIInventory->GetActive())
		lpUIInventory->Update();

	if (KEYMANAGER->IsOnceKeyDown('Z') && !player->GetIsAction())
	{
		imageSize = 2.0f;
		player->SwapWeapon();
		lpUIInventory->SwapWeapon();
		if (!player->GetIsEquipMainWeapon())
			lpUICurrentWeapon->SetFrameX(1);
		else
			lpUICurrentWeapon->SetFrameX(0);
	}

	imageSize -= DELTATIME;
	
	if (imageSize <= 1)
		imageSize = 1;

	lpUICurrentHpbar->SetCutX(153 * (1 - (float)player->GetCurrentHp() / (player->GetMaxHp() + player->GetAdditionalHp())));

	if (lpUIReduceHpbar->GetCutX() < lpUICurrentHpbar->GetCutX())
	{
		hpBarReduceTimer += DELTATIME;
		if (hpBarReduceTimer >= 0.05f)
		{
			hpBarReduceTimer -= 0.05f;
			lpUIReduceHpbar->SetCutX(lpUIReduceHpbar->GetCutX() + 1);
		}
	}
	else
		lpUIReduceHpbar->SetCutX(lpUICurrentHpbar->GetCutX());
}

void BattleSceneUI::Render(HDC hdc)
{
	lpUIbase->Render(hdc);
	lpUIFront->Render(hdc);
	lpUIGold->Render(hdc);
	lpUICurrentWeapon->Render(hdc);

	lpUIInventory->Render(hdc);
	lpUIReduceHpbar->Render(hdc);
	lpUICurrentHpbar->Render(hdc);

	if(player->GetCurrentWeaponImage())
		player->GetCurrentWeaponImage()->Render(hdc, 1205, 135, IMAGE_SIZE * imageSize, true);

	if (player->GetPotionImage())
	{
		player->GetPotionImage()->Render(hdc, WINSIZE_X - 35, 20, 1, true);
		FLOATINGFONT->Render(hdc, { WINSIZE_X - 35 + 10, 20 + 10 }, 18, to_string(player->GetPotionCount()).c_str(), RGB(255, 255, 255));
	}

	string hpText= "";
	hpText = to_string(player->GetCurrentHp()) + "/" + to_string(player->GetMaxHp() + player->GetAdditionalHp());
	FLOATINGFONT->Render(hdc, { 345,35 }, 24, hpText.c_str(), RGB(255, 255, 255));
	FLOATINGFONT->Render(hdc, { 50, 115 }, 24, to_string(player->GetGold()).c_str(), RGB(255, 255, 255));
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
	IMAGEMANAGER->AddImage("UI_Base", L"Image/UI/UI_base.png");
	IMAGEMANAGER->AddImage("UI_front", L"Image/UI/UI_front.png");
	IMAGEMANAGER->AddImage("UI_gold", L"Image/UI/UI_gold.png");
	IMAGEMANAGER->AddImage("UI_HPbar", L"Image/UI/UI_HPbar.png", 1 ,5);
	IMAGEMANAGER->AddImage("UI_CurrentWeapon", L"Image/UI/UI_CurrentWeapon.png", 2 ,1);
}
