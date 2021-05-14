#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	// 이미지 추가
	AddImage("SaveButton", "Image/Save.bmp", 144, 72, 2, 1);
	AddImage("LoadButton", "Image/Load.bmp", 144, 72, 2, 1);
	AddImage("LeftButton", "Image/Left.bmp", 120, 60, 2, 1);
	AddImage("RightButton", "Image/Right.bmp", 120, 60, 2, 1);

	// TileMap
	AddImage("Dungeon Background", L"Image/Map/dungeon_background.png",
		1280, 720, BACKGROUND_TILE_X, BACKGROUND_TILE_Y, true, RGB(128, 128, 128));
	AddImage("Tile Set", L"Image/Map/TileMap.png",
		320, 96, TILE_SET_X, TILE_SET_Y, true, RGB(128, 128, 128));

	// Player
	AddImage("PlayerState", L"Image/Player/PlayerState.png",
		640, 832, 10, 13, true, RGB(128, 128, 128));
	AddImage("BigSwordMotion", L"Image/Player/Weapon/BigSwordMotion.png",
		2560, 256, 40, 4, true, RGB(128, 128, 128));
	AddImage("ShortSwordMotion", L"Image/Player/Weapon/ShortSwordMotion.png",
		1152, 256, 18, 4, true, RGB(128, 128, 128));
	AddImage("GlovesMotion", L"Image/Player/Weapon/GlovesMotion.png",
		1280, 256, 20, 4, true, RGB(128, 128, 128));
	AddImage("SpearMotion", L"Image/Player/Weapon/SpearMotion.png",
		1472, 256, 23, 4, true, RGB(128, 128, 128));
	AddImage("BowMotion", L"Image/Player/Weapon/BowMotion.png",
		448, 256, 7, 4, true, RGB(128, 128, 128));
	AddImage("PlayerShortSwordSpecial", L"Image/Player/Weapon/ShortSwordSpecial.png",
		512, 64, 8, 1, true, RGB(128, 128, 128));
	
	// Weapon
	AddImage("BigSword1", L"Image/Player/Weapon/BigSword/1.png",
		5120, 512, 40, 4, true, RGB(128, 128, 128));
	AddImage("BigSword2", L"Image/Player/Weapon/BigSword/2.png",
		5120, 512, 40, 4, true, RGB(128, 128, 128));
	
	AddImage("ShortSword1", L"Image/Player/Weapon/ShortSword/1.png",
		2304, 512, 18, 4, true, RGB(128, 128, 128));
	AddImage("ShortSword2", L"Image/Player/Weapon/ShortSword/2.png",
		1728, 384, 18, 4, true, RGB(128, 128, 128));
	
	AddImage("Bow1", L"Image/Player/Weapon/Bow/1.png",
		448, 256, 7, 4, true, RGB(128, 128, 128));
	AddImage("Bow2", L"Image/Player/Weapon/Bow/2.png",
		448, 256, 7, 4, true, RGB(128, 128, 128));
	
	AddImage("Gloves1", L"Image/Player/Weapon/Gloves/1.png",
		2560, 512, 20, 4, true, RGB(128, 128, 128));
	AddImage("Gloves2", L"Image/Player/Weapon/Gloves/2.png",
		2560, 512, 20, 4, true, RGB(128, 128, 128));
	
	AddImage("Spear1", L"Image/Player/Weapon/Spear/1.png",
		3680, 640, 23, 4, true, RGB(128, 128, 128));
	AddImage("Spear2", L"Image/Player/Weapon/Spear/2.png",
		3680, 640, 23, 4, true, RGB(128, 128, 128));

	return S_OK;
}

void ImageManager::Release()
{
	for (auto iter = mImageDatas.begin(); iter != mImageDatas.end(); iter++)
	{
		if (iter->second)
		{
			iter->second->Release();
			delete iter->second;
			iter->second = nullptr;
		}
	}
	mImageDatas.clear();

	ReleaseSingleton();
}

bool ImageManager::AddImage(string key, string fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	if (FindImage(key))
		return false;

	Image* image = new Image();
	if (FAILED(image->Init(fileName.c_str(), width, height, isTransparent, transColor)))
	{
		image->Release();
		delete image;
	}

	mImageDatas.insert(make_pair(key, image));
	return true;
}

bool ImageManager::AddImage(string key, string fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	if (FindImage(key))
		return false;

	Image* image = new Image();
	if (FAILED(image->Init(fileName.c_str(), width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
	{
		image->Release();
		delete image;
	}

	mImageDatas.insert(make_pair(key, image));
	return true;
}

bool ImageManager::AddImage(string key, const wchar_t* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	if (FindImage(key))
		return false;

	Image* image = new Image();
	if (FAILED(image->Init(fileName, width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
	{
		image->Release();
		delete image;
	}

	mImageDatas.insert(make_pair(key, image));
	return true;
}

bool ImageManager::DeleteImage(string key)
{
	if (!FindImage(key))
		return false;

	auto iter = mImageDatas.find(key);

	iter->second->Release();
	delete iter->second;
	iter->second = nullptr;
	mImageDatas.erase(iter);
}

Image* ImageManager::FindImage(string key)
{
	auto iter = mImageDatas.find(key);

	if (iter == mImageDatas.end())
		return nullptr;

	return iter->second;
}
