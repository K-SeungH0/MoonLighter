#include "Enemy.h"
#include "Image.h"
#include "Player.h"
#include "UI.h"
#include <math.h>
HRESULT Enemy::Init()
{
	return S_OK;
}

HRESULT Enemy::Init(POINT pos)
{
	lpImage = IMAGEMANAGER->FindImage("GolemMove");

	this->pos.x = pos.x;
	this->pos.y = pos.y;

	lpUICurrentHpbar = new UI();
	lpUICurrentHpbar->Init(IMAGEMANAGER->FindImage("UI_HPbar"), { pos.x - IMAGEMANAGER->FindImage("UI_HPbar")->GetWidth() /2 , pos.y - IMAGEMANAGER->FindImage("UI_HPbar")->GetHeight() /2 },0,0,0,20);

	lpUIReduceHpbar = new UI();
	lpUIReduceHpbar->Init(IMAGEMANAGER->FindImage("UI_HPbar"), { pos.x - IMAGEMANAGER->FindImage("UI_HPbar")->GetWidth() /2 , pos.y - IMAGEMANAGER->FindImage("UI_HPbar")->GetHeight() /2 } ,0, 1,0,20);

	dir = DIR::DOWN;
	objectType = OBJECTTYPE::UNIT;
	imageFrame = 0;
	frameTimer = 0;
	hpBarReduceTimer = 0;
	moveSpeed = 50;
	damage = 10;
	armor = 0;
	maxHp = 100;
	hp = maxHp;
	setHitTime = 0.1f;
	ResetCollider();
	isAstar = false;
	isAttack = false;
	isAlive = true;
	deadTimer = -1;
	return S_OK;
}

void Enemy::Release()
{
	SAFE_RELEASE(lpUICurrentHpbar);
	SAFE_RELEASE(lpUIReduceHpbar);
}

void Enemy::Update()
{
	if (deadTimer < 0)
	{
		if (hitTime >= 0)
			hitTime -= DELTATIME;

		frameTimer += DELTATIME;

		lpUICurrentHpbar->SetCutX(153 * (1 - (float)hp / maxHp));

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

		if (frameTimer > 0.1f)
		{
			frameTimer -= 0.1f;

			++imageFrame;

			if (imageFrame == 7)
			{
				// attack Collider <-> player Collider 충돌 체크
				if (COLLIDERMANAGER->RectInRectFloat(GAMEDATA->GetRunTimePlayer()->GetCollider(), attackRangeCollider))
					GAMEDATA->GetRunTimePlayer()->Hit(this, IMAGEMANAGER->FindImage("BigSwordEffect"));
			}
			if (isAttack && state == STATE::ATTACK && imageFrame == lpImage->GetMaxFrameX())
			{
				Move();
				isAttack = false;
			}

			imageFrame %= lpImage->GetMaxFrameX();
		}
		if (CheckAttack() != DIR::NONE && !isAttack)
			Attack();
		else if (!isAttack)
			Move();

		if (hp <= 0)
			Die();
	}
	else
	{
		deadTimer -= DELTATIME;
		if (deadTimer <= 0)
		{
			deadTimer = 0;
			isAlive = false;
		}
	}
}

void Enemy::Render(HDC hdc)
{
	if (deadTimer < 0)
	{
		Unit::Render(hdc);
		if (hitTime >= 0)
		{
			auto alpha = lpImage->GetBlendFunc();
			alpha->SourceConstantAlpha = (255 * cosf(10000 * (1 - hitTime)));
			lpImage->AlphaRender(hdc, pos.x, pos.y, imageFrame, (int)dir, 1, true);
		}
		else
			lpImage->FrameRender(hdc, pos.x, pos.y, imageFrame, (int)dir, 1, true);

		lpUIReduceHpbar->SetPos({ (LONG)pos.x - IMAGEMANAGER->FindImage("UI_HPbar")->GetWidth() / 2 , (LONG)pos.y - IMAGEMANAGER->FindImage("UI_HPbar")->GetHeight() / 2 });
		lpUIReduceHpbar->Render(hdc);
		lpUICurrentHpbar->SetPos({ (LONG)pos.x - IMAGEMANAGER->FindImage("UI_HPbar")->GetWidth() / 2 , (LONG)pos.y - IMAGEMANAGER->FindImage("UI_HPbar")->GetHeight() / 2 });
		lpUICurrentHpbar->Render(hdc);

		if (isDebugMode)
		{
			int i = 1;
			for (auto iter = vAstarPos.begin(); iter != vAstarPos.end(); iter++)
			{
				Rectangle(hdc, iter->x - 20, iter->y - 20, iter->x + 20, iter->y + 20);
				FLOATINGFONT->Render(hdc, *iter, 18, to_string(i).c_str(), RGB(0, 0, 0));
				i++;
			}
			HPEN pen, oldpen;
			HBRUSH brush, oldbrush;

			pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			brush = (HBRUSH)GetStockObject(NULL_BRUSH);

			oldpen = (HPEN)SelectObject(hdc, pen);
			oldbrush = (HBRUSH)SelectObject(hdc, brush);

			Rectangle(hdc, astarInteractCollider.left, astarInteractCollider.top, astarInteractCollider.right, astarInteractCollider.bottom);

			DeleteObject(SelectObject(hdc, oldpen));

			pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldpen = (HPEN)SelectObject(hdc, pen);
			Rectangle(hdc, attackRangeCollider.left, attackRangeCollider.top, attackRangeCollider.right, attackRangeCollider.bottom);

			DeleteObject(SelectObject(hdc, oldpen));
			DeleteObject(SelectObject(hdc, oldbrush));
		}
	}
	else
	{
		auto alpha = lpImage->GetBlendFunc();
		alpha->SourceConstantAlpha = (255 - 255 * (1 - deadTimer));
		lpImage->AlphaRender(hdc, pos.x, pos.y, imageFrame, (int)dir, 1, true);
	}
}

void Enemy::Move()
{
	state = STATE::MOVING;
	lpImage = IMAGEMANAGER->FindImage("GolemMove");

	if (!vAstarPos.empty())
	{
		if ((int)pos.x > vAstarPos.front().x)
		{ 
			dir = DIR::LEFT;

			if(!isAttack)	pos.x -= moveSpeed * DELTATIME; 
		}
		else if ((int)pos.x < vAstarPos.front().x)
		{
			dir = DIR::RIGHT;
			
			if (!isAttack)	pos.x += moveSpeed * DELTATIME;
		}
		if ((int)pos.y > vAstarPos.front().y)
		{
			dir = DIR::UP;
			
			if (!isAttack)	pos.y -= moveSpeed * DELTATIME;
		}
		else if ((int)pos.y < vAstarPos.front().y)
		{ 
			dir = DIR::DOWN;
			
			if (!isAttack)	pos.y += moveSpeed * DELTATIME;
		}

		if ((int)pos.x == vAstarPos.front().x && (int)pos.y == vAstarPos.front().y)
		{
			if(!vAstarPos.empty())
				vAstarPos.erase(vAstarPos.begin());
		}
	}
	ResetCollider();
}

void Enemy::Attack()
{
	state = STATE::ATTACK;
	lpImage = IMAGEMANAGER->FindImage("GolemAttack");
	isAttack = true;
	imageFrame = 0;
}

void Enemy::Die()
{
	deadTimer = 1.0f;
}

DIR Enemy::CheckAttack()
{
	RECT temp;
	RECT playerCollider;
	playerCollider.left = GAMEDATA->GetRunTimePlayer()->GetCollider().left;
	playerCollider.right = GAMEDATA->GetRunTimePlayer()->GetCollider().right;
	playerCollider.top = GAMEDATA->GetRunTimePlayer()->GetCollider().top;
	playerCollider.bottom = GAMEDATA->GetRunTimePlayer()->GetCollider().bottom;

	RECT attackCollider;
	attackCollider.left = attackRangeCollider.left;
	attackCollider.right = attackRangeCollider.right;
	attackCollider.top = attackRangeCollider.top;
	attackCollider.bottom = attackRangeCollider.bottom;


	if (IntersectRect(&temp, &playerCollider, &attackCollider))
	{
		int left = abs(temp.left - attackCollider.left);
		int right = abs(temp.right - attackCollider.right);
		int top = abs(temp.top - attackCollider.top);
		int bottom = abs(temp.bottom - attackCollider.bottom);
		
		int _dir = min(left, min(right, min(top, bottom)));

		if (left == _dir)
		{
			if(!isAttack)
				dir = DIR::LEFT;
			return DIR::LEFT; 
		}
		if (right == _dir)
		{
			if (!isAttack)
				dir = DIR::RIGHT;
			return DIR::RIGHT;
		}
		if (top == _dir)
		{
			if (!isAttack)
				dir = DIR::UP;
			return DIR::UP;
		}
		if (bottom == _dir)
		{
			if (!isAttack)
				dir = DIR::DOWN;
			return DIR::DOWN;
		}

		return dir;
	}
	else	
		return DIR::NONE;
}

bool Enemy::CheckAstar()
{
	return COLLIDERMANAGER->RectInRectFloat(GAMEDATA->GetRunTimePlayer()->GetCollider(), astarInteractCollider);
}

void Enemy::ResetCollider()
{
	cameraCollider.left = pos.x - lpImage->GetFrameWidth() / 5;
	cameraCollider.top = pos.y - +lpImage->GetFrameHeight() / 4;
	cameraCollider.right = pos.x + lpImage->GetFrameWidth() / 5;
	cameraCollider.bottom = pos.y + lpImage->GetFrameHeight() / 4;	

	collider.left = pos.x - lpImage->GetFrameWidth() / 5;
	collider.top = pos.y - +lpImage->GetFrameHeight() / 4;
	collider.right = pos.x + lpImage->GetFrameWidth() / 5;
	collider.bottom = pos.y + lpImage->GetFrameHeight() / 4;

	astarInteractCollider.left = pos.x - lpImage->GetFrameWidth() * 1.5f;
	astarInteractCollider.top = pos.y - +lpImage->GetFrameHeight() * 1.5f;
	astarInteractCollider.right = pos.x + lpImage->GetFrameWidth() * 1.5f;
	astarInteractCollider.bottom = pos.y + lpImage->GetFrameHeight() * 1.5f;

	attackRangeCollider.left = pos.x - lpImage->GetFrameWidth() / 2;
	attackRangeCollider.top = pos.y - +lpImage->GetFrameHeight() / 2;
	attackRangeCollider.right = pos.x + lpImage->GetFrameWidth() / 2;
	attackRangeCollider.bottom = pos.y + lpImage->GetFrameHeight() / 2;
}

