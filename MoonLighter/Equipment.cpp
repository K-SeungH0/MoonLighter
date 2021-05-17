#include "Equipment.h"
#include "Player.h"
#include "Image.h"
#include "Block.h"
HRESULT Equipment::Init()
{
    return S_OK;
}

HRESULT Equipment::Init(Player* player)
{
	ImageLoad();
	this->type = OBJECTTYPE::DYNAMIC;
	this->weaponType = WEAPONTYPE::SHORTSWORD;
	ChangeType(weaponType);
	this->player = player;
	AttackInfoInit();
	return S_OK;
}

void Equipment::Release()
{
    delete this;
}

void Equipment::Update()
{

}

void Equipment::Render(HDC hdc)
{
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	lpImage->FrameRender(hdc, player->GetPos().x, player->GetPos().y, player->GetImageFrame(), player->GetStateFrame(), IMAGE_SIZE, true);
}

void Equipment::Attack()
{
	this->pos = player->GetPos();
	DIR dir = player->GetDir();
	if (weaponType != WEAPONTYPE::BOW)
	{
		AttackInfo attackInfo = attacks.find(make_pair(this->weaponType, player->GetDir()))->second;

		collider.left = this->pos.x + attackInfo.pos.x - (attackInfo.sizeX / 2);
		collider.right = this->pos.x + attackInfo.pos.x + (attackInfo.sizeX / 2);
		collider.top = this->pos.y + attackInfo.pos.y - (attackInfo.sizeY / 2);
		collider.bottom = this->pos.y + attackInfo.pos.y + (attackInfo.sizeY / 2);
	}
	else
	{
		// TODO : Bow 공격 추가
	}

	auto collidedObjects = COLLIDERMANAGER->CheckCollider(this);

	for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); iter++)
	{
		((Block*)*iter)->Hit();
	}
}

void Equipment::ChangeType(WEAPONTYPE type)
{
    this->weaponType = type;
	switch (this->weaponType)
	{
	case WEAPONTYPE::BIGSWORD:
		lpImage = IMAGEMANAGER->FindImage("BigSword2");
		break;
	case WEAPONTYPE::SHORTSWORD:
		lpImage = IMAGEMANAGER->FindImage("ShortSword2");
		break;
	case WEAPONTYPE::BOW:
		lpImage = IMAGEMANAGER->FindImage("Bow2");
		break;
	case WEAPONTYPE::GLOVES:
		lpImage = IMAGEMANAGER->FindImage("Gloves2");
		break;
	case WEAPONTYPE::SPEAR:
		lpImage = IMAGEMANAGER->FindImage("Spear2");
		break;
	}
}

void Equipment::ResetAttackCollider()
{
	collider = { 0,0,0,0 };
}

void Equipment::ImageLoad()
{
	COLORREF color = RGB(128, 128, 128);

	IMAGEMANAGER->AddImage("BigSwordMotion", L"Image/Player/Weapon/BigSwordMotion.png",
		2560, 256, 40, 4, true, color);
	IMAGEMANAGER->AddImage("ShortSwordMotion", L"Image/Player/Weapon/ShortSwordMotion.png",
		1152, 256, 18, 4, true, color);
	IMAGEMANAGER->AddImage("GlovesMotion", L"Image/Player/Weapon/GlovesMotion.png",
		1280, 256, 20, 4, true, color);
	IMAGEMANAGER->AddImage("SpearMotion", L"Image/Player/Weapon/SpearMotion.png",
		1472, 256, 23, 4, true, color);
	IMAGEMANAGER->AddImage("BowMotion", L"Image/Player/Weapon/BowMotion.png",
		448, 256, 7, 4, true, color);
	IMAGEMANAGER->AddImage("ShortSwordSpecialMotion", L"Image/Player/Weapon/ShortSwordSpecial.png",
		512, 64, 8, 1, true, color);
	
	IMAGEMANAGER->AddImage("BigSword1", L"Image/Player/Weapon/BigSword/1.png",
		5120, 512, 40, 4, true, color);
	IMAGEMANAGER->AddImage("BigSword2", L"Image/Player/Weapon/BigSword/2.png",
		5120, 512, 40, 4, true, color);

	IMAGEMANAGER->AddImage("ShortSword1", L"Image/Player/Weapon/ShortSword/1.png",
		2304, 512, 18, 4, true, color);
	IMAGEMANAGER->AddImage("ShortSword2", L"Image/Player/Weapon/ShortSword/2.png",
		1728, 384, 18, 4, true, color);

	IMAGEMANAGER->AddImage("Bow1", L"Image/Player/Weapon/Bow/1.png",
		448, 256, 7, 4, true, color);
	IMAGEMANAGER->AddImage("Bow2", L"Image/Player/Weapon/Bow/2.png",
		448, 256, 7, 4, true, color);

	IMAGEMANAGER->AddImage("Gloves1", L"Image/Player/Weapon/Gloves/1.png",
		2560, 512, 20, 4, true, color);
	IMAGEMANAGER->AddImage("Gloves2", L"Image/Player/Weapon/Gloves/2.png",
		2560, 512, 20, 4, true, color);

	IMAGEMANAGER->AddImage("Spear1", L"Image/Player/Weapon/Spear/1.png",
		3680, 640, 23, 4, true, color);
	IMAGEMANAGER->AddImage("Spear2", L"Image/Player/Weapon/Spear/2.png",
		3680, 640, 23, 4, true, color);
}

void Equipment::AttackInfoInit()
{
	AttackInfo attackinfo;

	#pragma region ShortSword
	attackinfo.sizeX = 70;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = -50;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::LEFT), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 70;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = 50;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::DOWN), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = -50;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::UP), attackinfo));

	attackinfo.sizeX = 70;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = 50;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::RIGHT), attackinfo));
#pragma endregion
	#pragma region BigSword
	attackinfo.sizeX = 120;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = -75;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::BIGSWORD, DIR::LEFT), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 120;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = 75;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::BIGSWORD, DIR::DOWN), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = -75;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::BIGSWORD, DIR::UP), attackinfo));

	attackinfo.sizeX = 120;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = 75;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::BIGSWORD, DIR::RIGHT), attackinfo));
#pragma endregion
	#pragma region Gloves
	attackinfo.sizeX = 50;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = -60;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::GLOVES, DIR::LEFT), attackinfo));

	attackinfo.sizeX = 50;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = 60;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::GLOVES, DIR::DOWN), attackinfo));

	attackinfo.sizeX = 50;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = -60;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::GLOVES, DIR::UP), attackinfo));

	attackinfo.sizeX = 50;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 60;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::GLOVES, DIR::RIGHT), attackinfo));
#pragma endregion
	#pragma region Spear
	attackinfo.sizeX = 150;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = -75;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SPEAR, DIR::LEFT), attackinfo));

	attackinfo.sizeX = 50;
	attackinfo.sizeY = 150;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = 75;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SPEAR, DIR::DOWN), attackinfo));

	attackinfo.sizeX = 50;
	attackinfo.sizeY = 125;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = -75;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SPEAR, DIR::UP), attackinfo));

	attackinfo.sizeX = 150;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 75;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SPEAR, DIR::RIGHT), attackinfo));
#pragma endregion
}