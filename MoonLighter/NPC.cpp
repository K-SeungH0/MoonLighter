#include "NPC.h"

HRESULT NPC::Init()
{
	this->objectType = OBJECTTYPE::NPC;

	return S_OK;
}

HRESULT NPC::Init(POINTFLOAT pos)
{
	this->objectType = OBJECTTYPE::NPC;
	this->pos = pos;
	return S_OK;
}

void NPC::Release()
{
}

void NPC::Update()
{
}

void NPC::Render(HDC hdc)
{
}
