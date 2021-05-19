#include "Item.h"

HRESULT Item::Init()
{
	return S_OK;
}

void Item::Release()
{
	delete this;
}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
}

void Item::Use()
{

}

void Item::PickUp()
{
	// TODO : 인벤토리 AddItem 추가

}
