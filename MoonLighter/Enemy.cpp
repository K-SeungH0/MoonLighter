#include "Enemy.h"
#include "Image.h"

HRESULT Enemy::Init()
{
	ImageLoad();
	return S_OK;
}

void Enemy::Release()
{

}

void Enemy::Update()
{
	frameTimer += DELTATIME;
	if (frameTimer > 0.1f)
	{
		frameTimer -= 0.1f;
		
		(++imageFrame) %= lpImage->GetMaxFrameX();
	}
	state = STATE::IDLE;
}

void Enemy::Render(HDC hdc)
{

}

void Enemy::Move()
{
	state = STATE::MOVING;
}

void Enemy::Attack()
{
	state = STATE::ATTACK;
}

void Enemy::ImageLoad()
{
	IMAGEMANAGER->AddImage("GolemMove", L"Image/Enemy/GolemMove.png", 8, 4);
	IMAGEMANAGER->AddImage("GolemAttack", L"Image/Enemy/GolemAttack.png", 13, 4);
}
