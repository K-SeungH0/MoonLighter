#include "Equipment.h"

HRESULT Equipment::Init()
{
	this->type = WEAPONTYPE::SHORTSWORD;
	ChangeType(type);
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
}

void Equipment::ChangeType(WEAPONTYPE type)
{
    this->type = type;
	switch (this->type)
	{
	case WEAPONTYPE::BIGSWORD:
		lpItemImage = IMAGEMANAGER->FindImage("BigSword2");
		break;
	case WEAPONTYPE::SHORTSWORD:
		lpItemImage = IMAGEMANAGER->FindImage("ShortSword2");
		break;
	case WEAPONTYPE::BOW:
		lpItemImage = IMAGEMANAGER->FindImage("Bow2");
		break;
	case WEAPONTYPE::GLOVES:
		lpItemImage = IMAGEMANAGER->FindImage("Gloves2");
		break;
	case WEAPONTYPE::SPEAR:
		lpItemImage = IMAGEMANAGER->FindImage("Spear2");
		break;
	}
}
