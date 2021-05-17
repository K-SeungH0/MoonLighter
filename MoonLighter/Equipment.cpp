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