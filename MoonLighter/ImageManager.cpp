#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	// 이미지 추가
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
