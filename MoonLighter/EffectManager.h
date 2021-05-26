#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>

using namespace std;

class Image;

class EffectManager : public Singleton<EffectManager>
{
public:
	struct EffectInfo
	{
		Image* lpImage;
		POINT pos;
		float timer;
		int frame;
		int dir;
	};
private:
	vector<EffectInfo> vEffectInfo;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void EffectRender(Image* lpImage, POINT pos, int dir);

	~EffectManager() {};
};

