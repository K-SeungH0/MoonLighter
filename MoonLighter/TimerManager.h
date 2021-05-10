#pragma once
#include "Singleton.h"
#include <Windows.h>
class Timer;
class TimerManager : public Singleton<TimerManager>
{
private:
	Timer* timer;
	char szText[128];

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetDeltaTime();
};

