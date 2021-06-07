#include "TownScene.h"
#include "Player.h"
#include "Image.h"
#include "Camera.h"
#include "LayerManager.h"
#include "Weapon.h"
#include "BattleSceneUI.h"

HRESULT TownScene::Init()
{
	ImageLoad();
	GAMEDATA->RunTimeDataInit();
	Load();
	
	lpBackGround = IMAGEMANAGER->FindImage("Town_BackGround");
	lpInteract = IMAGEMANAGER->FindImage("UI_Interact");
	
	lpPixelImage = new Image();
	lpPixelImage->Init(lpBackGround->GetWidth(), lpBackGround->GetHeight());

	lpPlayer = GAMEDATA->GetRunTimePlayer();
	lpPlayer->SetMoveArea({ 0,0, lpBackGround->GetWidth(), lpBackGround->GetHeight() });
	lpPlayer->SetPos({ 1940, 550 });

	lpCamera = new Camera();
	lpCamera->Init(lpBackGround, lpPlayer->GetpPos(), 350);
	lpPlayer->SetCamera(lpCamera);
	
	lpLayerManager = new LayerManager();
	lpLayerManager->Init();
	lpLayerManager->SetCamera(lpCamera);

	lpUI = new BattleSceneUI();
	lpUI->Init();
	lpUI->SetCamera(lpCamera);

	isEnterDunGeon = false;
	isEnterShop = false;
	timer = 0;
	MapLoad();
	return S_OK;
}

void TownScene::Release()
{
	if (lpUI) 
	{
		lpUI->Release(); 
		lpUI = nullptr;
	}
	if (lpCamera)
	{
		lpCamera->Release(); 
		lpCamera = nullptr;
	}

	SAFE_RELEASE(lpPixelImage);
	SAFE_RELEASE(lpLayerManager);
	vObjectsPixel.clear();
	COLLIDERMANAGER->RemovePixelCollider();
}

void TownScene::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('I'))
		lpUI->ToggleInven();

	if (!lpUI->GetInvenActive())
	{
		timer += DELTATIME;
		if (timer >= 0.1f)
		{
			timer -= 0.1f;
			IMAGEMANAGER->FindImage("Town_BigTree")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_BigTree")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_BigTree")->GetMaxFrameX());
			IMAGEMANAGER->FindImage("Town_Tree")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_Tree")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_Tree")->GetMaxFrameX());
			IMAGEMANAGER->FindImage("Town_Well")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_Well")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_Well")->GetMaxFrameX());
			IMAGEMANAGER->FindImage("Town_WillHome")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_WillHome")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_WillHome")->GetMaxFrameX());
			IMAGEMANAGER->FindImage("Town_House")->SetCurrentFrameX((IMAGEMANAGER->FindImage("Town_House")->GetCurrentFrameX() + 1) % IMAGEMANAGER->FindImage("Town_House")->GetMaxFrameX());
		}

		lpPlayer->Update();
		lpCamera->Update();

		if (lpPlayer->GetPos().x > 2000 && lpPlayer->GetPos().x < 2100 && lpPlayer->GetPos().y >700 && lpPlayer->GetpPos()->y < 750)
			isEnterDunGeon = true;
		else
			isEnterDunGeon = false;

		if (lpPlayer->GetPos().x > 1900 && lpPlayer->GetPos().x < 2000 && lpPlayer->GetPos().y > 450 && lpPlayer->GetpPos()->y < 500)
			isEnterShop = true;
		else
			isEnterShop = false;
	}
	lpUI->Update();
	if (isEnterDunGeon)
	{
		if (KEYMANAGER->IsOnceKeyDown('J'))
		{
			SCENEMANAGER->ChageScene("Battle");
			//GAMEDATA->FileSave();
		}
	}

	if (isEnterShop)
	{
		if (KEYMANAGER->IsOnceKeyDown('J'))
		{
			SCENEMANAGER->ChageScene("Shop", "LodingScene");
			//GAMEDATA->FileSave();
		}
	}
}

void TownScene::Render(HDC hdc)
{
	lpCamera->CameraRender(hdc, { 0, 0 }, lpBackGround);

	lpLayerManager->AddObject(make_pair(lpPlayer->GetImage(), lpPlayer->GetPos()));
	if(lpPlayer->GetState() == STATE::ATTACK)	lpLayerManager->AddObject(make_pair(lpPlayer->GetWeapon()->GetImage(), lpPlayer->GetPos()));
	
	lpLayerManager->Render(hdc);
	
	lpLayerManager->RemoveObject(make_pair(lpPlayer->GetImage(), lpPlayer->GetPos()));
	if (lpPlayer->GetState() == STATE::ATTACK)	lpLayerManager->RemoveObject(make_pair(lpPlayer->GetWeapon()->GetImage(), lpPlayer->GetPos()));

	if (isDebugMode)
	{
		for (auto iter = vObjectsPixel.begin(); iter != vObjectsPixel.end(); iter++)
		{
			Rectangle(hdc, lpPlayer->GetCameraCollider().left, lpPlayer->GetCameraCollider().top, lpPlayer->GetCameraCollider().right, lpPlayer->GetCameraCollider().bottom);

			lpCamera->CameraRender(hdc, { (LONG)iter->second.x, (LONG)iter->second.y }, iter->first, IMAGE_SIZE);
		}
	}

	if (isEnterDunGeon)
	{
		lpCamera->CameraRender(hdc, { (LONG)lpPlayer->GetPos().x - lpInteract->GetWidth() / 2, (LONG)lpPlayer->GetPos().y - 100 }, lpInteract);
		FLOATINGFONT->Render(hdc, { (LONG)lpPlayer->GetPos().x - (lpInteract->GetWidth() / 2) + 60 - (LONG)lpCamera->GetCameraPos().x, (LONG)lpPlayer->GetPos().y - 75 - 9 - (LONG)lpCamera->GetCameraPos().y}, 18, "키 눌러서 던전가기", RGB(0, 0, 0));
	}
	if (isEnterShop)
	{
		lpCamera->CameraRender(hdc, { (LONG)lpPlayer->GetPos().x - lpInteract->GetWidth() / 2, (LONG)lpPlayer->GetPos().y - 100 }, lpInteract);
		FLOATINGFONT->Render(hdc, { (LONG)lpPlayer->GetPos().x - (lpInteract->GetWidth() / 2) + 60 - (LONG)lpCamera->GetCameraPos().x, (LONG)lpPlayer->GetPos().y - 75 - 9 - (LONG)lpCamera->GetCameraPos().y }, 18, "키 눌러서 상점가기", RGB(0, 0, 0));
	}

	lpUI->Render(hdc);
}
void TownScene::Load()
{
	string saveName = "Save/SaveTownMapData.map";

	DWORD readBytes;

	HANDLE hFile = CreateFile(saveName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (ReadFile(hFile, tileMap, sizeof(TILE_INFO) * TOWN_TILE_X * TOWN_TILE_Y, &readBytes, NULL))
	{

	}
	else
	{
		MessageBox(g_hWnd, "로드 실패", "실패", MB_OK);
	}

	CloseHandle(hFile);
}

void TownScene::MapLoad()
{
	POINTFLOAT pos;
	int x, y;
	Image* image = nullptr;
	Image* pixelImage = nullptr;
	pixelDC = lpPixelImage->GetMemDC();
	lpPlayer->SetPixelHDC(&pixelDC);

	for (int i = 0; i < TOWN_TILE_X * TOWN_TILE_Y; i++)
	{
		x = tileMap[i].frameX;
		y = tileMap[i].frameY;
		if (!((x == 2 && y == 5) || (x == 3 && y == 5)))
		{
			if (x == 0 && y == 0) { image = IMAGEMANAGER->FindImage("Town_BigTree");		pixelImage = IMAGEMANAGER->FindImage("Town_BigTree_Pixel"); }
			if (x == 1 && y == 0) { image = IMAGEMANAGER->FindImage("Town_Tree");			pixelImage = IMAGEMANAGER->FindImage("Town_Tree_Pixel"); }
			if (x == 2 && y == 0) { image = IMAGEMANAGER->FindImage("Town_Well");			pixelImage = IMAGEMANAGER->FindImage("Town_Well_Pixel"); }
			if (x == 3 && y == 0) { image = IMAGEMANAGER->FindImage("Town_WillHome");		pixelImage = IMAGEMANAGER->FindImage("Town_WillHome_Pixel"); }
			if (x == 0 && y == 1) { image = IMAGEMANAGER->FindImage("Town_House_1");		pixelImage = IMAGEMANAGER->FindImage("Town_House_1_Pixel"); }
			if (x == 1 && y == 1) { image = IMAGEMANAGER->FindImage("Town_House_2");		pixelImage = IMAGEMANAGER->FindImage("Town_House_2_Pixel"); }
			if (x == 2 && y == 1) { image = IMAGEMANAGER->FindImage("Town_House");			pixelImage = IMAGEMANAGER->FindImage("Town_House_Pixel"); }
			if (x == 3 && y == 1) { image = IMAGEMANAGER->FindImage("Town_BigStone");		pixelImage = IMAGEMANAGER->FindImage("Town_BigStone_Pixel"); }
			if (x == 0 && y == 2) { image = IMAGEMANAGER->FindImage("Town_Sign_1");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 1 && y == 2) { image = IMAGEMANAGER->FindImage("Town_Sign_2");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 2 && y == 2) { image = IMAGEMANAGER->FindImage("Town_Sign_3");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 3 && y == 2) { image = IMAGEMANAGER->FindImage("Town_Sign_4");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 0 && y == 3) { image = IMAGEMANAGER->FindImage("Town_Sign_5");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 1 && y == 3) { image = IMAGEMANAGER->FindImage("Town_Sign_6");			pixelImage = IMAGEMANAGER->FindImage("Town_Sign_Pixel"); }
			if (x == 2 && y == 3) { image = IMAGEMANAGER->FindImage("Town_Post");			pixelImage = IMAGEMANAGER->FindImage("Town_Post_Pixel"); }
			if (x == 3 && y == 3) { image = IMAGEMANAGER->FindImage("Town_Board");			pixelImage = IMAGEMANAGER->FindImage("Town_Board_Pixel"); }
			if (x == 0 && y == 4) { image = IMAGEMANAGER->FindImage("Town_Barrel");			pixelImage = IMAGEMANAGER->FindImage("Town_Barrel_Pixel"); }
			if (x == 1 && y == 4) { image = IMAGEMANAGER->FindImage("Town_Bench_01");		pixelImage = IMAGEMANAGER->FindImage("Town_Bench_01_Pixel"); }
			if (x == 2 && y == 4) { image = IMAGEMANAGER->FindImage("Town_Bench_02");		pixelImage = IMAGEMANAGER->FindImage("Town_Bench_02_Pixel"); }
			if (x == 3 && y == 4) { image = IMAGEMANAGER->FindImage("Town_Bench_03");		pixelImage = IMAGEMANAGER->FindImage("Town_Bench_03_Pixel"); }
			if (x == 0 && y == 5) { image = IMAGEMANAGER->FindImage("Town_BlackSmithHouse");pixelImage = IMAGEMANAGER->FindImage("Town_BlackSmithHouse_Pixel"); }
			if (x == 1 && y == 5) { image = IMAGEMANAGER->FindImage("Town_WitchHouse");		pixelImage = IMAGEMANAGER->FindImage("Town_WitchHouse_Pixel"); }
			
			pos = { (float)tileMap[i].rcTile.left , (float)tileMap[i].rcTile.top};
			pixelImage->Render(pixelDC, pos.x, pos.y, IMAGE_SIZE);
			vObjectsPixel.push_back(make_pair(pixelImage, pos));
			COLLIDERMANAGER->AddPixelCollider(pixelImage, pos);

			pos = { (float)tileMap[i].rcTile.left + image->GetFrameWidth(), (float)tileMap[i].rcTile.top + image->GetFrameHeight() };
			vObjects.push_back(make_pair(image, pos));
			lpLayerManager->AddObject(make_pair(image, vObjects.back().second));

		}
	}
}

void TownScene::ImageLoad()
{
	IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");
	//IMAGEMANAGER->AddImage("Town_Test", L"Image/Map/Town_Test.png");
	IMAGEMANAGER->AddImage("UI_Interact", L"Image/UI/UI_Interact.png");

	IMAGEMANAGER->AddImage("Town_BackGround", L"Image/Map/Town_BackGround.png");

	IMAGEMANAGER->AddImage("Town_BigTree", L"Image/Object/Town/Town_BigTree.png", 11, 1);
	IMAGEMANAGER->AddImage("Town_BigTree_Pixel", L"Image/Object/Town/Town_BigTree_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Tree", L"Image/Object/Town/Town_Tree.png", 10, 1);
	IMAGEMANAGER->AddImage("Town_Tree_Pixel", L"Image/Object/Town/Town_Tree_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Well", L"Image/Object/Town/Town_Well.png", 8, 1);
	IMAGEMANAGER->AddImage("Town_Well_Pixel", L"Image/Object/Town/Town_Well_Pixel.png");

	IMAGEMANAGER->AddImage("Town_WillHome", L"Image/Object/Town/Town_WillHome.png", 13, 1);
	IMAGEMANAGER->AddImage("Town_WillHome_Pixel", L"Image/Object/Town/Town_WillHome_Pixel.png");
	IMAGEMANAGER->AddImage("Town_House", L"Image/Object/Town/Town_House.png", 12, 1);
	IMAGEMANAGER->AddImage("Town_House_Pixel", L"Image/Object/Town/Town_House_Pixel.png");
	IMAGEMANAGER->AddImage("Town_House_1", L"Image/Object/Town/Town_House_1.png");
	IMAGEMANAGER->AddImage("Town_House_1_Pixel", L"Image/Object/Town/Town_House_1_Pixel.png");
	IMAGEMANAGER->AddImage("Town_House_2", L"Image/Object/Town/Town_House_2.png");
	IMAGEMANAGER->AddImage("Town_House_2_Pixel", L"Image/Object/Town/Town_House_2_Pixel.png");

	IMAGEMANAGER->AddImage("Town_Barrel", L"Image/Object/Town/Town_Barrel.png");
	IMAGEMANAGER->AddImage("Town_Barrel_Pixel", L"Image/Object/Town/Town_Barrel_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Bench_01", L"Image/Object/Town/Town_Bench_01.png");
	IMAGEMANAGER->AddImage("Town_Bench_01_Pixel", L"Image/Object/Town/Town_Bench_01_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Bench_02", L"Image/Object/Town/Town_Bench_02.png");
	IMAGEMANAGER->AddImage("Town_Bench_02_Pixel", L"Image/Object/Town/Town_Bench_02_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Bench_03", L"Image/Object/Town/Town_Bench_03.png");
	IMAGEMANAGER->AddImage("Town_Bench_03_Pixel", L"Image/Object/Town/Town_Bench_03_Pixel.png");
	IMAGEMANAGER->AddImage("Town_BigStone", L"Image/Object/Town/Town_BigStone.png");
	IMAGEMANAGER->AddImage("Town_BigStone_Pixel", L"Image/Object/Town/Town_BigStone_Pixel.png");

	IMAGEMANAGER->AddImage("Town_Sign_1", L"Image/Object/Town/Town_Sign_1.png");
	IMAGEMANAGER->AddImage("Town_Sign_2", L"Image/Object/Town/Town_Sign_2.png");
	IMAGEMANAGER->AddImage("Town_Sign_3", L"Image/Object/Town/Town_Sign_3.png");
	IMAGEMANAGER->AddImage("Town_Sign_4", L"Image/Object/Town/Town_Sign_4.png");
	IMAGEMANAGER->AddImage("Town_Sign_5", L"Image/Object/Town/Town_Sign_5.png");
	IMAGEMANAGER->AddImage("Town_Sign_6", L"Image/Object/Town/Town_Sign_6.png");
	IMAGEMANAGER->AddImage("Town_Sign_Pixel", L"Image/Object/Town/Town_Sign_Pixel.png");

	IMAGEMANAGER->AddImage("Town_Post", L"Image/Object/Town/Town_Post.png");
	IMAGEMANAGER->AddImage("Town_Post_Pixel", L"Image/Object/Town/Town_Post_Pixel.png");
	IMAGEMANAGER->AddImage("Town_Board", L"Image/Object/Town/Town_Board.png");
	IMAGEMANAGER->AddImage("Town_Board_Pixel", L"Image/Object/Town/Town_Board_Pixel.png");

	IMAGEMANAGER->AddImage("Town_BlackSmithHouse", L"Image/Object/Town/Town_BlackSmithHouse.png");
	IMAGEMANAGER->AddImage("Town_BlackSmithHouse_Pixel", L"Image/Object/Town/Town_BlackSmithHouse_Pixel.png");
	IMAGEMANAGER->AddImage("Town_WitchHouse", L"Image/Object/Town/Town_WitchHouse.png");
	IMAGEMANAGER->AddImage("Town_WitchHouse_Pixel", L"Image/Object/Town/Town_WitchHouse_Pixel.png");
	
	IMAGEMANAGER->AddImage("BlackSmith_Idle_1", L"Image/NPC/BlackSmith_Idle_1.png");
	IMAGEMANAGER->AddImage("BlackSmith_Idle_1", L"Image/NPC/BlackSmith_Idle_1.png");


	IMAGEMANAGER->AddImage("Witch_Idle_1", L"Image/NPC/Witch_Idle_1.png");
	IMAGEMANAGER->AddImage("Witch_Idle_2", L"Image/NPC/Witch_Idle_2.png");
	IMAGEMANAGER->AddImage("Witch_Idle_3", L"Image/NPC/Witch_Idle_3.png");
}
