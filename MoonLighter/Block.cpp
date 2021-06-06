#include "Block.h"
#include "Player.h"
#include "Image.h"
HRESULT Block::Init()
{
	return S_OK;
}

HRESULT Block::Init(TILE_INFO tile, TILETYPE* from)
{
	this->pos.x = tile.rcTile.left;
	this->pos.y = tile.rcTile.top;

	this->collider.left = tile.rcTile.left;
	this->collider.top = tile.rcTile.top;
	this->collider.right = tile.rcTile.right;
	this->collider.bottom = tile.rcTile.bottom;
	
	this->objectType = OBJECTTYPE::BREAKABLE;
	this->tileType = tile.type;
	
	this->frameX = tile.frameX;
	this->frameY = tile.frameY;

	this->fromTileType = from;

	this->lpImage = IMAGEMANAGER->FindImage("DunGeon_TileSet");
	COLLIDERMANAGER->AddCollider(this);
	return S_OK;
}

void Block::Release()
{

}

void Block::Update()
{

}

void Block::Render(HDC hdc)
{
	if (isDebugMode)
		Rectangle(hdc, collider.left, collider.top, collider.right, collider.bottom);

	if(lpImage)
		lpImage->FrameRender(hdc, pos.x, pos.y, frameX, frameY, IMAGE_SIZE);
}

void Block::Hit(Object* attacker, Image* hitEffect)
{
	POINTFLOAT playerPos = GAMEDATA->GetRunTimePlayer()->GetPos();

	int damage = ((Unit*)attacker)->GetDamage();
	
	if(tileType == TILETYPE::BREAKABLE)
	{
		// 0 ~ 1 �׾Ƹ�
		// 2 ~ 7 �ذ�
		// 8 ~ 9 ����
		switch (frameX)
		{
		case 0:
		case 1:
			lpImage = IMAGEMANAGER->FindImage("UrnRest");
			EFFECTMANAGER->EffectRender(hitEffect, { (int)this->pos.x , (int)this->pos.y }, (int)GAMEDATA->GetRunTimePlayer()->GetDir());
			FLOATINGFONT->DamageRender({ (int)this->pos.x + this->lpImage->GetFrameWidth() , (int)this->pos.y }, damage, 0.75f);
			Broken();
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			lpImage = IMAGEMANAGER->FindImage("SkullRest");
			EFFECTMANAGER->EffectRender(hitEffect,{ (int)this->pos.x , (int)this->pos.y }, (int)GAMEDATA->GetRunTimePlayer()->GetDir());
			FLOATINGFONT->DamageRender({ (int)this->pos.x + this->lpImage->GetFrameWidth(), (int)this->pos.y }, damage, 0.75f);
			Broken();
			break;
		case 8:
		case 9:
			lpImage = IMAGEMANAGER->FindImage("ChairRest");
			EFFECTMANAGER->EffectRender(hitEffect, { (int)this->pos.x , (int)this->pos.y }, (int)GAMEDATA->GetRunTimePlayer()->GetDir());
			FLOATINGFONT->DamageRender({ (int)this->pos.x + this->lpImage->GetFrameWidth() , (int)this->pos.y }, damage, 0.75f);
			Broken();
			break;
		}
	}
}

void Block::Broken()
{
	frameX = 0;
	frameY = 0;
	*fromTileType = TILETYPE::NONE;
	tileType = TILETYPE::NONE;
	collider = { 0,0,0,0 };
}
