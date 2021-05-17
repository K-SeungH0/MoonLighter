#pragma once
#include "Singleton.h"
#include <map>
#include <string>
#include <windows.h>

using namespace std;
class Image;

class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mImageDatas;

public:
	HRESULT Init();
	void Release();

	bool AddImage(string key, string fileName,
		int width, int height, bool isTransparent = FALSE,
		COLORREF transColor = FALSE);
	bool AddImage(string key, string fileName,
		int width, int height, int maxFrameX, int maxFrameY, bool isTransparent = FALSE,
		COLORREF transColor = FALSE);	
	bool AddImage(string key, const wchar_t* fileName,
			int width, int height, int maxFrameX, int maxFrameY, bool isTransparent = FALSE,
			COLORREF transColor = FALSE);
	bool DeleteImage(string key);
	void DeleteAll();
	Image* FindImage(string key);


};