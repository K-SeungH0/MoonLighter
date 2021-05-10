#include "BattleScene.h"
#include "Image.h"

HRESULT BattleScene::Init()
{
	backGroundImage = new Image();

	player = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	missile =
	{ 0,0,
		20,20
	};
	isFired = false;
	testSample = IMAGEMANAGER->FindImage("ª˘«√≈∏¿œ");
	for (int i = 0; i < 16; i++)
	{
		tileInfo[i].frameX = g_testTile[i].frameX;
		tileInfo[i].frameY = g_testTile[i].frameY;
		tileInfo[i].rcTile =
		{
			g_testTile[i].rcTile.left + 100,
			g_testTile[i].rcTile.top + 200,
			g_testTile[i].rcTile.right + 100,
			g_testTile[i].rcTile.bottom + 200
		};
	}
	return S_OK;
}

void BattleScene::Release()
{
	//SAFE_RELEASE(player);

	SAFE_RELEASE(backGroundImage);
}

void BattleScene::Update()
{
	//player->Update();

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		player.y -= 0.5f;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		player.y += 0.5f;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		player.x -= 0.5f;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		player.x += 0.5f;
	}

	if (KEYMANAGER->IsOnceKeyDown('A'))
	{
		missile.left = player.x;
		missile.top = player.y;
		missile.right = missile.left + 20;
		missile.bottom = missile.top + 20;
		isFired = true;
	}
	if (isFired)
	{
		missile.left -= 0.5f;
		missile.right -= 0.5f;
	}
	CheckCollision();
}

void BattleScene::Render(HDC hdc)
{
	if (backGroundImage)
		backGroundImage->Render(hdc);

	//if (player)
	//{
	//	Rectangle(hdc, player->GetPos().x, player->GetPos().y, player->GetPos().x + 54, player->GetPos().y + 64);
	//	player->Render(hdc);
	//}

	Ellipse(hdc, missile.left, missile.top, missile.right, missile.bottom);

	for (int i = 0; i < 16; i++)
	{
		testSample->FrameRender(hdc,
			tileInfo[i].rcTile.left,
			tileInfo[i].rcTile.top,
			tileInfo[i].frameX,
			tileInfo[i].frameY);
	}

}

void BattleScene::CheckCollision()
{

}
