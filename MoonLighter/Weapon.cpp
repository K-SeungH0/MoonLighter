#include "Weapon.h"
#include "Player.h"
#include "Image.h"
#include "Block.h"
#include "Projectile.h"

HRESULT Weapon::Init()
{
	if (!imageLoaded)
		ImageLoad();
	weaponType = WEAPONTYPE::NONE;		
	lpEffectImage = IMAGEMANAGER->FindImage("GlovesEffect");

	this->damage = 1;
	this->lpPlayer = GAMEDATA->GetRunTimePlayer();

	this->itemData.count = 0;
	this->itemData.isEquipment = false;
	this->itemData.itemCode = 0;
	this->itemData.lpItemImage = nullptr;
	this->itemData.slotPos = { -1,-1 };

	lpProjectile = new Projectile();
	lpProjectile->Init();
	AttackInfoInit();

    return S_OK;
}

HRESULT Weapon::Init(GameData::ItemData itemData, ItemManager* lpItemManager)
{
	//Item::Init(itemData, lpItemManager);
	if(!imageLoaded)
		ImageLoad();

	this->itemData = itemData;
	this->lpItemManager = lpItemManager;

	ChangeType();
	this->lpPlayer = GAMEDATA->GetRunTimePlayer();
	AttackInfoInit();
	return S_OK;
}

void Weapon::Release()
{

}

void Weapon::Update()
{
	if(this->weaponType == WEAPONTYPE::BOW)
	lpProjectile->Update();
}

void Weapon::Render(HDC hdc)
{
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if(this->weaponType != WEAPONTYPE::NONE)
		lpImage->FrameRender(hdc, lpPlayer->GetPos().x, lpPlayer->GetPos().y, lpPlayer->GetImageFrame(), lpPlayer->GetStateFrame(), IMAGE_SIZE, true);

	if (lpProjectile->GetIsMove())
		lpProjectile->Render(hdc);
}

void Weapon::Attack()
{
	this->pos = lpPlayer->GetPos();
	DIR dir = lpPlayer->GetDir();
	if (weaponType != WEAPONTYPE::BOW)
	{
		AttackInfo attackInfo = attacks.find(make_pair(this->weaponType, lpPlayer->GetDir()))->second;

		collider.left = this->pos.x + attackInfo.pos.x - (attackInfo.sizeX / 2);
		collider.right = this->pos.x + attackInfo.pos.x + (attackInfo.sizeX / 2);
		collider.top = this->pos.y + attackInfo.pos.y - (attackInfo.sizeY / 2);
		collider.bottom = this->pos.y + attackInfo.pos.y + (attackInfo.sizeY / 2);

		auto collidedObjects = COLLIDERMANAGER->CheckCollider(this);

		for (auto iter = collidedObjects.begin(); iter != collidedObjects.end(); iter++)
		{
			((Block*)*iter)->Hit(lpPlayer, lpEffectImage);
		}
	}
	else
	{
		// TODO : Bow 공격 추가
		if(!lpProjectile->GetIsMove())
			lpProjectile->Shoot(lpPlayer->GetDir(), this->pos);
	}
}

void Weapon::ChangeType()
{
	switch (this->itemData.itemCode)
	{
	case 1000:
		this->weaponType = WEAPONTYPE::BIGSWORD;
		lpImage = IMAGEMANAGER->FindImage("BigSword1");
		lpEffectImage = IMAGEMANAGER->FindImage("BigSwordEffect");
		this->damage = 30;
		break;
	case 1001:
		this->weaponType = WEAPONTYPE::BIGSWORD;
		lpImage = IMAGEMANAGER->FindImage("BigSword2");
		lpEffectImage = IMAGEMANAGER->FindImage("BigSwordEffect");
		this->damage = 60;
		break;
	case 1010: 
		this->weaponType = WEAPONTYPE::SHORTSWORD;
		lpImage = IMAGEMANAGER->FindImage("ShortSword1");
		lpEffectImage = IMAGEMANAGER->FindImage("ShortSwordEffect");
		this->damage = 10;
		break;
	case 1011:
		this->weaponType = WEAPONTYPE::SHORTSWORD;
		lpImage = IMAGEMANAGER->FindImage("ShortSword2");
		lpEffectImage = IMAGEMANAGER->FindImage("ShortSwordEffect");
		this->damage = 30;
		break;
	case 1020: 
		this->weaponType = WEAPONTYPE::SPEAR;
		lpImage = IMAGEMANAGER->FindImage("Spear1");
		lpEffectImage = IMAGEMANAGER->FindImage("SpearEffect");
		this->damage = 15;
		break;
	case 1021:
		this->weaponType = WEAPONTYPE::SPEAR;
		lpImage = IMAGEMANAGER->FindImage("Spear2");
		lpEffectImage = IMAGEMANAGER->FindImage("SpearEffect");
		this->damage = 45;
		break;
	case 1030:
		this->weaponType = WEAPONTYPE::GLOVES;
		lpImage = IMAGEMANAGER->FindImage("Gloves1");
		lpEffectImage = IMAGEMANAGER->FindImage("GlovesEffect");
		this->damage = 10;
		break;
	case 1031:
		this->weaponType = WEAPONTYPE::GLOVES;
		lpImage = IMAGEMANAGER->FindImage("Gloves2");
		lpEffectImage = IMAGEMANAGER->FindImage("GlovesEffect");
		this->damage = 20;
		break;
	case 1040: 
		this->weaponType = WEAPONTYPE::BOW;
		lpImage = IMAGEMANAGER->FindImage("Bow1");
		lpProjectile->SetImage(IMAGEMANAGER->FindImage("Arrow1"));
		lpEffectImage = IMAGEMANAGER->FindImage("BowEffect");
		this->damage = 10;
		break;
	case 1041:
		this->weaponType = WEAPONTYPE::BOW;
		lpImage = IMAGEMANAGER->FindImage("Bow2");
		lpProjectile->SetImage(IMAGEMANAGER->FindImage("Arrow2"));
		lpEffectImage = IMAGEMANAGER->FindImage("BowEffect");
		this->damage = 30;
		break;
	}
}

void Weapon::ResetAttackCollider()
{
	collider = { 0,0,0,0 };
}

void Weapon::ImageLoad()
{
	imageLoaded = true;

	IMAGEMANAGER->AddImage("BigSword1", L"Image/Player/Weapon/BigSword/1.png", 40, 4);
	IMAGEMANAGER->AddImage("BigSword2", L"Image/Player/Weapon/BigSword/2.png", 40, 4);
	IMAGEMANAGER->AddImage("BigSwordEffect", L"Image/Player/Weapon/BigSword/BigSword_Effect.png", 3, 4);

	IMAGEMANAGER->AddImage("ShortSword1", L"Image/Player/Weapon/ShortSword/1.png", 18, 4);
	IMAGEMANAGER->AddImage("ShortSword2", L"Image/Player/Weapon/ShortSword/2.png",18, 4);
	IMAGEMANAGER->AddImage("ShortSwordEffect", L"Image/Player/Weapon/ShortSword/ShortSword_Effect.png", 3, 4);

	IMAGEMANAGER->AddImage("Bow1", L"Image/Player/Weapon/Bow/1.png", 7, 4);
	IMAGEMANAGER->AddImage("Arrow1", L"Image/Player/Weapon/Bow/Arrow_1.png", 1, 4);
	IMAGEMANAGER->AddImage("Bow2", L"Image/Player/Weapon/Bow/2.png", 7, 4);
	IMAGEMANAGER->AddImage("Arrow2", L"Image/Player/Weapon/Bow/Arrow_2.png", 1, 4);
	IMAGEMANAGER->AddImage("BowEffect", L"Image/Player/Weapon/Bow/Bow_Effect.png", 3, 4);

	IMAGEMANAGER->AddImage("Gloves1", L"Image/Player/Weapon/Gloves/1.png",20, 4);
	IMAGEMANAGER->AddImage("Gloves2", L"Image/Player/Weapon/Gloves/2.png",20, 4);
	IMAGEMANAGER->AddImage("GlovesEffect", L"Image/Player/Weapon/Gloves/Gloves_Effect.png", 3, 4);

	IMAGEMANAGER->AddImage("Spear1", L"Image/Player/Weapon/Spear/1.png",23, 4);
	IMAGEMANAGER->AddImage("Spear2", L"Image/Player/Weapon/Spear/2.png",23, 4);
	IMAGEMANAGER->AddImage("SpearEffect", L"Image/Player/Weapon/Spear/Spear_Effect.png", 3, 4);
}

void Weapon::SetCamera(Camera* lpCamera)
{
	 Object::SetCamera(lpCamera); 
	 lpProjectile->SetCamera(this->lpCamera);
}

void Weapon::AttackInfoInit()
{
	AttackInfo attackinfo;

	#pragma region ShortSword
	attackinfo.sizeX = 70;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = -50;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::LEFT), attackinfo));
	attacks.insert(make_pair(make_pair(WEAPONTYPE::NONE, DIR::LEFT), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 70;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = 50;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::DOWN), attackinfo));
	attacks.insert(make_pair(make_pair(WEAPONTYPE::NONE, DIR::DOWN), attackinfo));

	attackinfo.sizeX = 100;
	attackinfo.sizeY = 50;
	attackinfo.pos.x = 0;
	attackinfo.pos.y = -50;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::UP), attackinfo));
	attacks.insert(make_pair(make_pair(WEAPONTYPE::NONE, DIR::UP), attackinfo));

	attackinfo.sizeX = 70;
	attackinfo.sizeY = 100;
	attackinfo.pos.x = 50;
	attackinfo.pos.y = 0;
	attacks.insert(make_pair(make_pair(WEAPONTYPE::SHORTSWORD, DIR::RIGHT), attackinfo));
	attacks.insert(make_pair(make_pair(WEAPONTYPE::NONE, DIR::RIGHT), attackinfo));
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