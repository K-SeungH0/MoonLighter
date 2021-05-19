#include "Block.h"
#include "Image.h"
HRESULT Block::Init()
{
	return S_OK;
}

HRESULT Block::Init(TILE_INFO tile)
{
	this->pos.x = tile.rcTile.left;
	this->pos.y = tile.rcTile.top;

	this->collider.left = tile.rcTile.left;
	this->collider.top = tile.rcTile.top;
	this->collider.right = tile.rcTile.right;
	this->collider.bottom = tile.rcTile.bottom;
	
	this->type = OBJECTTYPE::STATIC;
	this->tileType = tile.type;
	
	this->frameX = tile.frameX;
	this->frameY = tile.frameY;

	this->lpImage = IMAGEMANAGER->FindImage("Tile Set");
	
	COLLIDERMANAGER->AddCollider(this);
	return S_OK;
}

HRESULT Block::Init(RECTFLOAT rc)
{
	// 배틀씬에서 외부 벽 초기화
	this->tileType = TILETYPE::WALL;
	this->lpImage = nullptr;
	this->frameX = 0;
	this->frameY = 0;

	this->collider.left = rc.left;
	this->collider.right = rc.right;
	this->collider.top = rc.top;
	this->collider.bottom = rc.bottom;

	COLLIDERMANAGER->AddCollider(this);
	return S_OK;
}

void Block::Release()
{
	delete this;
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

void Block::Hit()
{
	// TODO : 프레임에 따라 어떤 잔여물 인지 추가
	switch (tileType)
	{
	case TILETYPE::BREAKABLE:
		// 0 ~ 1 항아리
		// 2 ~ 7 해골
		// 8 ~ 9 의자
		switch (frameX)
		{
		case 0:
		case 1:
			lpImage = IMAGEMANAGER->FindImage("UrnRest");	
			Broken();
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			lpImage = IMAGEMANAGER->FindImage("SkullRest");
			Broken();
			break;
		case 8:
		case 9:
			lpImage = IMAGEMANAGER->FindImage("ChairRest");
			Broken();
			break;
		}
		break;
	}
}

void Block::Broken()
{
	frameX = 0;
	frameY = 0;
	tileType = TILETYPE::NONE;
	collider = { 0,0,0,0 };
}
